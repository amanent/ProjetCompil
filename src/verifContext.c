#include "verifContext.h"
#include "proj.h"
#include "proj_y.h"
#include "tree.h"
#include "stdlib.h"
#include "stdio.h"
#include "variable.h"
#include "class.h"
#include "symboles.h"


extern TreeP mainCode;
extern ClassListP classList;

typedef struct _context{
	FunctionP func;
	short prevOP;
	ArgListP arglst;
}Context;

Context context = {NULL, 0, NULL};
int local_offset = 0;


bool verif_nameResolution(){
	ClassListP currentCL = classList;

	while(currentCL != NULL){
//printf("salut %s 1\n", currentCL->current->IDClass);
		/* CHECK NON-STATIC CLASS FIELD TYPE*/
		ClassFieldListP currentCFL =currentCL->current->cfl;
		while(currentCFL != NULL){
			VarP currentVar = currentCFL->current;
			if(currentVar->type == NULL){
				currentVar->type = class_getClass(currentVar->typeName);
				if(currentVar->type == NULL) // si on a pas trouvé la classe.
					return FALSE;
			}
			currentCFL = currentCFL->next;
		}
//printf("salut %s 2\n", currentCL->current->IDClass);
		/* CHECK STATIC CLASS FIELD TYPE*/
		ClassFieldListP currentSCFL = currentCL->current->staticCfl;
		while(currentSCFL != NULL){
			VarP currentVar = currentSCFL->current;
			if(currentVar->type == NULL){
				currentVar->type = class_getClass(currentVar->typeName);
				if(currentVar->type == NULL) // si on a pas trouvé la classe.
					return FALSE;
			}
			currentSCFL = currentSCFL->next;
		}
//printf("salut %s 3\n", currentCL->current->IDClass);
		/* CHECK NON-STATIC CLASS METHOD */
		ClassMethodListP currentCML = currentCL->current->cml;
		while(currentCML != NULL){
			FunctionP currentFunc = currentCML->current;
			if(currentFunc->returnType == NULL && currentFunc->returnName[0] != '\0') { // pour tester les fonctions void
				currentFunc->returnType = class_getClass(currentFunc->returnName);
				if(currentFunc->returnType == NULL || verif_paramList(currentFunc) == FALSE) // si on a pas trouvé la classe.
					return FALSE;
				function_howManyArgs(currentFunc);
			}
			currentCML = currentCML->next;
		}
//printf("salut %s 4\n", currentCL->current->IDClass);
		/* CHECK STATIC CLASS METHOD */
		ClassMethodListP currentSCML = currentCL->current->cml;
		while(currentSCML != NULL){
			FunctionP currentSFunc = currentSCML->current;
			if(currentSFunc->returnType == NULL && currentSFunc->returnName[0] != '\0') {
				currentSFunc->returnType = class_getClass(currentSFunc->returnName);
				if(currentSFunc->returnType == NULL || verif_paramList(currentSFunc) == FALSE) // si on a pas trouvé la classe.
					return FALSE;
				function_howManyArgs(currentSFunc);
			}
			currentSCML = currentSCML->next;
		}
//printf("salut %s 5\n", currentCL->current->IDClass);
		/* CHECK CURRENT CLASS SUPER */
		if(currentCL->current->super == NULL && currentCL->current->superName != NULL) {
			currentCL->current->super = class_getClass(currentCL->current->superName);
			if(currentCL->current->super == NULL) // si on a pas trouvé la classe.
				return FALSE;
		}
//printf("salut %s 6\n", currentCL->current->IDClass);
		currentCL = currentCL->next;
	}
	return TRUE;
}

bool verif_paramList(FunctionP func){
	if(func == NULL)
		return FALSE;
	ParamsListP param = func->paramsList;
	while(param){
		if(!class_getClass(param->type))
			return FALSE;
		param = param->next;
	}
	return TRUE;
}

void verif_contructJumpTable(){
	ClassListP tmp = classList;
	while(tmp){
		class_generateJumpTable(tmp->current);
		tmp = tmp->next;
	}
}

bool verif_contextuelle(){ // need verif arg.
	bool verif = TRUE;
//printf("-- toto1\n");
	verif &= verif_nameResolution(); if(!verif) return FALSE;
//printf("-- toto2\n");
	verif_contructJumpTable();
//printf("-- toto3\n");	
	verif &= verif_allClassesCode(); if(!verif) return FALSE;
//printf("-- toto4\n");	
	verif &= verif_types(symTable_newTable(), mainCode, NULL, NULL); if(!verif) return FALSE;
//printf("-- toto5\n");
	return TRUE;
}

bool verif_allClassesCode(){
	ClassListP tmp = classList;
	while(tmp){
//printf("-- test %s 1\n", tmp->current->IDClass);
		if(!verif_classCode(tmp->current))
			return FALSE;
		tmp = tmp->next;
	}
	return TRUE;
}

int nbStaticVars = 0;
bool verif_classCode(ClassP c){
	SymbolesTableP table = symTable_newTable();
	SymbolesTableP statictable = symTable_newTable();

	fillSymTableClassVar(c->cfl, table);
	fillSymTableStaticVar(c->staticCfl, statictable);

	fillSymTableClassFunc(c->cml, table);
	fillSymTableClassFunc(c->staticCml, statictable);

	ClassMethodListP mtmp = c->cml;
	while(mtmp){
		if(!verif_func(table, mtmp->current, c))
			return FALSE;
		mtmp = mtmp->next;
	}

	mtmp = c->staticCml;
	while(mtmp){
		if(!verif_func(statictable, mtmp->current, c))
			return FALSE;
		mtmp = mtmp->next;
	}
	return TRUE;
}

int fillSymTableClassVar(ClassFieldListP cfl, SymbolesTableP st){
	int n = 0;
	if(!cfl)
		return 0;
	if(cfl->next){
		n = fillSymTableClassVar(cfl->next, st) + 1;
	}
	symTable_addLine(st, cfl->current, NONSTATIC);
	cfl->current->offset = n + 1;
	return n + 1;
}

void fillSymTableStaticVar(ClassFieldListP cfl, SymbolesTableP st){
	ClassFieldListP tmp = cfl;
	while(tmp){
		cfl->current->offset = nbStaticVars++;
		symTable_addLine(st, tmp->current, STATIC);
		tmp = tmp->next;
	}
}

int fillSymTableClassFunc(ClassMethodListP cml, SymbolesTableP st){
	int n = 0;
	if(!cml)
		return 0;
	if(cml->next)
		n = fillSymTableClassFunc(cml->next, st) + 1;
	cml->current->offset = n;
	return n;
}



/*
bool verif_class(ClassP c){
	//Instance
	SymbolesTableP table = symTable_newTable();
	ClassFieldListP ftmp = c->cfl;
	while(ftmp){
		symTable_addLine(table, ftmp->current, NONSTATIC);
		ftmp = ftmp->next;
	}
	ClassMethodListP mtmp = c->cml;
	while(mtmp){
		if(!verif_func(table, mtmp->current, c))
			return FALSE;
	}

	//Static
	table = symTable_newTable();
	ftmp = c->staticCfl;
	while(ftmp){
		symTable_addLine(table, ftmp->current, STATIC);
		ftmp = ftmp->next;
	}
	mtmp = c->staticCml;
	while(mtmp){
		if(!verif_func(table, mtmp->current, c))
			return FALSE;
	}

	return TRUE;
}
*/

bool verif_func(SymbolesTableP st, FunctionP func, ClassP c){
	symTable_enterFunction(st, func, c);
	local_offset = 0;
	bool res = verif_types(st, func->code, c, func);
	local_offset = 0;
	symTable_exitScope(st);
	return res;
}





bool verif_types(SymbolesTableP st, TreeP tree, ClassP c , FunctionP f) {
	int i = 0;
	
	if (tree == NULL){
		//fprintf(stderr, "Verif d'un arbre vide\n");
		return TRUE;
	}
	    
	short prevOP = context.prevOP;
	context.prevOP = tree->op;
	
	tree->cContext = c;
	tree->fContext = f;

//printf("--treating : %d\n", tree->op);
	switch (tree->op) {
		case STR: //return true, tree->type = String
			tree->type = class_getClass("String"); 
			return TRUE;
			
		case CST: //return true, tree->type = Integer
			tree->type = class_getClass("Integer"); 
			return TRUE;

/**/	case ID: //ajout dans la table
		{	
			if(prevOP == VAR){
				return TRUE;
			}
			else {
				tree->var = symTable_getVarFromName(st, tree->u.str);
				if(tree->var == NULL)
					return NULL;
				//printf("%s %x !\n", tree->u.str, tree->var);
				if(tree->var) {
					//printf("type : %s\n", tree->var->type->IDClass);
					tree->type = tree->var->type;
				}
				else if(!strcmp(tree->u.str, "result")) // si on voit result
					tree->type = tree->fContext->returnType;
			}
			return TRUE;
		}
			
		case EQ: //integer
		case NE:
		case GT:
		case GE:
		case LT:
		case LE:
		case ADD: // verif integer , type integer
		case SUB:
		case MUL:
		case DIV:
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f))
					return FALSE;
			if(		getChild(tree, 0)->type == class_getClass("Integer")
				&&	getChild(tree, 1)->type == class_getClass("Integer"))			
			{	
				tree->type = class_getClass("Integer");
				return TRUE;
			}
			return FALSE;


		case CONCAT: // string
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f))
					return FALSE;
			if(		getChild(tree, 0)->type == class_getClass("String")
				&&	getChild(tree, 1)->type == class_getClass("String"))			
			{	
				tree->type = class_getClass("String");
				return TRUE;
			}
			return FALSE;

		case UNARYSUB: //integer
		case UNARYADD: 
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f))
					return FALSE;
			if(		getChild(tree, 0)->type == class_getClass("Integer"))		
			{	
				tree->type = class_getClass("Integer");
				return TRUE;
			}
			return FALSE;

		case IF: /*IF Exp THEN Inst ELSE Inst*/
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f))
					return FALSE;
			return (getChild(tree, 0)->type == class_getClass("Integer"));


/**/	case DIRAFF: // Id AFF Exp ';'
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f))
					return FALSE;
			string idtxt = getChild(tree, 0)->u.str;

			if(!strcmp(idtxt, "this") || !strcmp(idtxt, "super"))
				return FALSE;

			return (	(getChild(tree, 1)->type == getChild(tree, 0)->type)||(class_isinheritedFrom(getChild(tree, 1)->type, getChild(tree, 0)->type)));

/**/	case CMPAFF: // l AFF Exp ';' //verif types
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f))
					return FALSE;

			return (	(getChild(tree, 1)->type == getChild(tree, 0)->type)||(class_isinheritedFrom(getChild(tree, 1)->type, getChild(tree, 0)->type)));
				

/**/	case SELECT: // Exp2 '.' Id //verif id est dans exp2
		{	

			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f))
					return FALSE;				
			ClassP c = getChild(tree, 0)->type;
			VarP v = getChild(tree, 0)->var;
			VarP vv = NULL;
			if(v)
			{
				vv = class_getInstanceFieldFromName(c, getChild(tree, 1)->u.str);
			}
			else 
			{
				vv = class_getStaticFieldFromName(c, getChild(tree, 1)->u.str);
			}
			if(vv){
				tree->var = vv;
				tree->type = vv->type;
				return TRUE;
			}
			return FALSE;
		}
/**/	case RET: //verif type de retour de la func

		case VAR: //VAR Id ':' Idcl AffectO	';' // add dans la table
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f))
					return FALSE;
			//ALLOCATION D'UNE NOUVELLE VARIABLE
			VarP v = NEW(1, Var);
			v->ID = getChild(tree, 0)->u.str;
			v->offset = local_offset++;
			if(symTable_isNameInUse(st, v->ID))
				return FALSE;
			symTable_addLine(st, v, LOCAL);
			getChild(tree, 0)->var = v;
			v->type = getChild(tree, 1)->type;
			v->typeName = getChild(tree, 0)->var->type->IDClass;
			getChild(tree, 0)->type = getChild(tree, 1)->type;
			//--------------------------------

			if(!getChild(tree, 2))
				return TRUE;
			return(	   getChild(tree, 1)->type == getChild(tree, 2)->type
					|| getChild(tree, 2)->type == NULL
					|| class_isinheritedFrom(getChild(tree, 2)->type, getChild(tree, 1)->type));
	
		case MSGSNTS: // voir a factoriser avec MSGSNT
/**/	case MSGSNT: // Exp2 '.' Id '(' ListArgO ')' //verif params && id dans les func de exp2
		{
			ArgListP arglist = context.arglst; // sauvegarde du contexte
			context.arglst = arglst_newList();

			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f)) {
					context.arglst = arglist;
					return FALSE;
				}

			ClassP exp2type = getChild(tree, 0)->type;
			if(!exp2type) {
				context.arglst = arglist;
				return FALSE;
			}
			FunctionP ff = NULL;

			if(getChild(tree, 0)->op != IDCL) {
				ff = class_getInstanceMethFromName(exp2type, getChild(tree, 1)->u.str);
			}
			else{
				ff = class_getStaticMethFromName(exp2type, getChild(tree, 1)->u.str);
			}
			//if(ff)
			//	printf("retType = %s\n", ff->returnName);
			if(ff && prmlst_goodCallArgs(ff, context.arglst))
			{
				tree->type = ff->returnType;
				tree->func = ff;
				context.arglst = arglist;
				return TRUE;
			}
			context.arglst = arglist; // restauration du contexte

			//FONCTIONS SPECIALES
//printf("caca ? %s_%s\n",(getChild(tree, 0)->op==ID?getChild(tree, 0)->u.str:""), getChild(tree, 1)->u.str);
			if(getChild(tree, 0)->type == class_getClass("Integer")){
				if(!strcmp("toString", getChild(tree, 1)->u.str)){
					tree->type = class_getClass("String");
					return TRUE;
				}
			}
			if(getChild(tree, 0)->type == class_getClass("String")){
				if(		!strcmp("println", getChild(tree, 1)->u.str)
					||	!strcmp("print", getChild(tree, 1)->u.str))
					return TRUE;
			}
//printf("caca !\n");
			return FALSE;
		}

		case CAST: //verification heritage, type = type du cast
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f))
					return FALSE;			
			tree->type = getChild(tree, 0)->type;
			return (class_canAffect(tree->type, getChild(tree, 1)->type));

		case IDCL: // verif tabledesclasses
		{
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f))
					return FALSE;

			ClassP c = class_getClass(tree->u.str);
			tree->type = c;
			return (c != NULL);
		}
/**/	case INSTA: // NEW Idcl '(' ListArgO ')' // verif de la liste d'args du const de idcl
		{
			ArgListP arglist = context.arglst;
			context.arglst = arglst_newList();

			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f)) {
					context.arglst = arglist;
					return FALSE;
				}	
			tree->type = class_getClass(getChild(tree, 0)->u.str);

			bool toto = prmlst_goodCallArgs(tree->type->constructor, context.arglst);
			//printf("%s : %s\n", getChild(tree, 0)->u.str, (toto?"vrai":"faux"));
			context.arglst = arglist;
			return toto; //prmlst_goodCallArgs(tree->type->constructor, context.arglst);
		}
		case INSTR: //gogo child0
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f))
					return FALSE;		
			tree->type = getChild(tree, 0)->type;
			tree->var = getChild(tree, 0)->var;
			tree->func = getChild(tree, 0)->func;
			return TRUE;
		case LSTARG:
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f))
					return FALSE;

			tree->type = getChild(tree, 0)->type;
			if(tree->type == NULL)
				return FALSE;
			tree->var  = getChild(tree, 0)->var;
			tree->func = getChild(tree, 0)->func;
			arglst_pushFront(context.arglst, tree->type);
			return TRUE;
		case BLCDECL:
			symTable_enterNewScope(st);
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f))
					return FALSE;
			symTable_exitScope(st);
			return TRUE;
		case DECL: 
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f))
					return FALSE;
				return TRUE;
		case LSTINST:
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i), c, f))
					return FALSE;
			return TRUE;


		default: //   (seulement géré a la verif context, va modifier directement l'offset)
		fprintf(stderr, "Erreur! pprint : etiquette d'operator inconnue: %d\n", tree->op);
		break; 
	}
	return TRUE;
}

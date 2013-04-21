#include <unistd.h>
#include <stdio.h>
#include "proj.h"
#include "proj_y.h"

extern void setError();
extern bool verbose;
extern bool noEval;
/*
void pprintVar(VarDeclP decl, TreeP tree) {
  if (! verbose) return;
  printf("%s := ", decl->name);
  pprint(tree);
  * utile au cas ou l'evaluation se passerait mal ! *
  fflush(NULL);
}


void pprintValueVar(VarDeclP decl) {
  if (! verbose) return;
  if (! noEval) {
    printf(" [Valeur: %d]\n", decl->val);
  } else printf("\n");
}
*/

/* Affichage d'une expression binaire */
void pprintTree2(TreeP tree, char *op) {
  //printf("(");
  ppprint(getChild(tree, 0));
  printf("%s", op);
  ppprint(getChild(tree, 1));
  //printf(")");
}

void pprintTree2full(TreeP tree, char *before, char*un, char* after) {
  printf("%s", before);
  ppprint(getChild(tree, 0));
  printf("%s", un);
  ppprint(getChild(tree, 1));
  printf("%s", after);
}

void pprintTree3(TreeP tree, char *before, char*un, char* deux, char* after) {
  printf("%s", before);
  ppprint(getChild(tree, 0));
  printf("%s", un);
  ppprint(getChild(tree, 1));
  printf("%s", deux);
  ppprint(getChild(tree, 2));
  printf("%s", after);
}

/* Affichage recursif d'un arbre representant une expression. */
void ppprint(TreeP tree) {
  //if (! verbose ) return;
  if (tree == NIL(Tree)) { 
    //printf("Unknown"); 
    return;
  }
  switch (tree->op) {
	case ID: case IDCL: case STR:
					printf("%s", tree->u.str); break;
	case CST:		printf("%d", tree->u.val); break;
	case EQ:		pprintTree2(tree, " = "); break;
	case NE:		pprintTree2(tree, " <> "); break;
	case GT:		pprintTree2(tree, " > "); break;
	case GE:		pprintTree2(tree, " >= "); break;
	case LT:		pprintTree2(tree, " < "); break;
	case LE:		pprintTree2(tree, " <= "); break;
	case ADD:		pprintTree2(tree, " + "); break;
	case SUB:		pprintTree2(tree, " - "); break;
	case MUL:		pprintTree2(tree, " * "); break;
	case DIV:		pprintTree2(tree, " / "); break;
	case CONCAT:	pprintTree2(tree, " . "); break;
	case BLCDECL: 	pprintTree2(tree, "\nis\n"); break;
	case DECL: 		pprintTree2(tree, "\n"); break;
	case LSTINST: 	pprintTree2(tree, "\n"); break;
	case VAR: 		pprintTree3(tree, "var ", " : ", " := ", ""); break;
	case MSGSNT: 
  case MSGSNTS:	pprintTree3(tree, "", ".", "(", ")"); break;
	case CAST: 		pprintTree2full(tree, "(as ", ": ", ")"); break;
	case INSTA: 		pprintTree2full(tree, "new ", "(", ")"); break;
  case INSTR:   ppprint(getChild(tree, 0)); printf(";"); break;
	case SELECT: 	pprintTree2(tree, "."); break;
	case UNARYSUB: 	printf("-"); ppprint(getChild(tree, 0)); break;
	case UNARYADD: 	printf("+"); ppprint(getChild(tree, 0)); break;
	case IF: 		pprintTree3(tree, "if ", " then ", " else ", ""); break;
	case AFF: 		pprintTree2full(tree, "", " := ", ";"); break; 
	case RET: 		printf("return;"); break;
	case LSTARG: 	pprintTree2(tree, ", "); break;
  default:
    /* On signale le probleme mais on ne quitte pas le programme pour autant
     * car ce n'est pas dramatique !
     */

    fprintf(stderr, "Erreur! pprint : etiquette d'operator inconnue: %d\n", 
	    tree->op);
    setError(UNEXPECTED);
  }
}

void pprintMain(TreeP tree) {
  //if (! verbose) return;
  printf("code : \n");
  ppprint(tree);
  printf("\n");
  fflush(NULL);
}

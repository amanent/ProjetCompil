
  switch (tree->op) {
	case ID: break;
	case IDCL: break; 
	case STR: break;
	case CST: break;		
	case EQ: break;	
	case NE: break;	
	case GT: break;	
	case GE: break;	
	case LT: break;	
	case LE: break;	
	case ADD: break;		
	case SUB: break;		
	case MUL: break;		
	case DIV: break;		
	case CONCAT: break;
	case BLCDECL: break; 	
	case DECL: break;		
	case LSTINST: break; 	
	case VAR: break; 		
	case MSGSNT: break; 	
	case CAST: break; 		
	case INST: break; 		
	case LAFFECT: break;
	case UNARYSUB: break;
	case UNARYADD: break;
	case IF: break;
	case AFF: break;
	case RET: break;
	case LSTARG: break;
  default:
    fprintf(stderr, "Erreur! pprint : etiquette d'operator inconnue: %d\n", tree->op);
  }
}
/*

ID
	PUSH? addrIdent
IDCL
	//rien normalement
STR
	PUSHS str
CST
	PUSHI cst	
EQ
	//empiler les deux paramètres
	EQUAL
NE 
	//empiler les deux paramètres
	EQUAL
	NOT
GT 
	//empiler les deux paramètres
	SUP
GE 
	//empiler les deux paramètres
	SUPEQ
LT 
	//empiler les deux paramètres
	INF
LE 
	//empiler les deux paramètres
	INFEQ
ADD 
	//empiler les deux valeurs
	ADD
SUB 
	//empiler les deux valeurs
	SUB
MUL 
	//empiler les deux valeurs
	MUL
DIV 
	//empiler les deux valeurs
	DIV
CONCAT
	//empiler les deux valeurs
	CONCAT
MSGSNT
	PUSHN 1 // pour la valeur de retour 
	//push des n arguments 
	
CAST
	// je vois pas trop, peut etre en empilant une copie de l'objet et changer sa table d'appels
INST
	ALLOC //taille de lobjet
	//initialisations
	//constructeur
	PUSHA //nom fonction
	CALL
	POP // nbParams 
SELECT
	PUSH //addr objet 
	// ??? 
UNARYSUB
	PUSHI 0
	PUSH //valeur du fils
	SUB
UNARYADD
	// nothing to do 
IF
	// Push prim expression 
	JZ else_...
	// code fils 1 
	JUMP suite_...
	else_...: // code fils 2 
	suite: NOP
	
AFF
	//adresse de la partie gauche deja pushée 
	PUSH // valeur 
	STORE // decalage du champ par rapport a la classe... comment est ce que je le retrouve moi ?) 
RET
LSTA
BLCDECL
DECL
LSTINST
VAR

*/
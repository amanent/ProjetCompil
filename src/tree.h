#ifndef _TREE_H_
#define _TREE_H_
	
	typedef struct _Tree Tree, *TreeP;

	#include "variable.h"
	#include "function.h"
	/* la structure d'un arbre (noeud ou feuille) */
	struct _Tree {
	  short op;         /* etiquette de l'operateur courant */
	  short nbChildren; /* nombre de sous-arbres */
	  union {
		char *str;      /* valeur de la feuille si op = ID, IDCL ou STR */
		int val;        /* valeur de la feuille si op = CST */
		struct _Tree **children; /* tableau des sous-arbres */
	  } u;
	  int nbVar;
	  VarP var;
	  FunctionP func; // ces deux derniers champs peuvent etre dans une union
	  ClassP type;

	  FunctionP fContext;
	  ClassP	cContext;
	};

	/* construction et accesseur pour les arbres */
	TreeP makeLeafStr(short op, char *str);
	TreeP makeLeafInt(short op, int val);
	TreeP makeTree(short op, int nbChildren, ...);
	TreeP getChild(TreeP tree, int rank);
	/* fonction d'affichage d'un arbre */
	void pprintMain(TreeP tree);
	void ppprint(TreeP tree);

#endif /* _TREE_H_ */

#ifndef _TREE_H_
#define _TREE_H_

	/* la structure d'un arbre (noeud ou feuille) */
	typedef struct _Tree {
	  short op;         /* etiquette de l'operateur courant */
	  short nbChildren; /* nombre de sous-arbres */
	  union {
		char *str;      /* valeur de la feuille si op = ID, IDCL ou STR */
		int val;        /* valeur de la feuille si op = CST */
		struct _Tree **children; /* tableau des sous-arbres */
	  } u;
	} Tree, *TreeP;

	/* construction et accesseur pour les arbres */
	TreeP makeLeafStr(short op, char *str);
	TreeP makeLeafInt(short op, int val);
	TreeP makeTree(short op, int nbChildren, ...);
	TreeP getChild(TreeP tree, int rank);

#endif /* _TREE_H_ */
#ifndef _VARIABLES_H_
#define _VARIABLES_H_

	typedef struct _Var Var, *VarP;
	typedef struct _ArgList ArgList, *ArgListP;

	#include "proj.h"
	#include "class.h"

	
	typedef enum 
	{
		STATIC, NONSTATIC, PARAM, LOCAL
	} e_nature;

	struct _Var{
		string typeName;
		ClassP type;
		string ID;	
		TreeP value;
		int offset;
		e_nature nature;
	};

	typedef struct _ArgListElem{
		ClassP current;
		struct _ArgListElem* next;
	}ArgListElem, *ArgListElemP;

	struct _ArgList{
		ArgListElemP top;
		ArgListElemP bottom;
	};


	/**
	 * Regarde si une variable est égale a une autre
	 * @param  v        variable a tester
	 * @param  varName  nom que la variable doit avoir
	 * @param  varClass type que la variable doit avoir
	 * @return          si la variable est bien égale
	 */
	bool var_areEquals(VarP v, string varName, string varClass);
	
	/**
	 * Creer une nouvelle liste d'arguments
	 * @return la liste d'arguments creee
	 */
	ArgListP arglst_newList();
	/**
	 * Creer un nouvel element de liste d'argument
	 * @param  c type de l'argument
	 * @return   le nouvel element
	 */
	ArgListElemP arglm_newElem(ClassP c);
	/**
	 * Push un element au debut de la liste
	 * @param list liste dans laquelle on doit ajouter l'element
	 * @param c    type de l'element a ajouter
	 */
	void arglst_pushFront(ArgListP list, ClassP c);
	/**
	 * Push un element a la fin de la liste
	 * @param list liste dans laquelle on doit ajouter l'element
	 * @param c    type de l'element a ajouter
	 */
	void arglst_pushBack(ArgListP list, ClassP c);
	/**
	 * Avoir la nature de la variable comme une string
	 * @param  n la nature a afficher
	 * @return   string contenant la nature
	 */
	string var_natToString(e_nature n);
	


#endif

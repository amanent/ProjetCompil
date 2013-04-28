#ifndef _FUNCTION_H_
#define _FUNCTION_H_

	typedef struct _ParamsList ParamsList, *ParamsListP;
	typedef struct _Function Function, *FunctionP;

	#include "tree.h"
	#include "class.h"
	#include "proj.h"
	#include "variable.h"

	struct _ParamsList {
		string type;
		string name;
		struct _ParamsList* next;
	};

	struct _Function {
		bool override;
		string ID;
		ParamsListP paramsList;
		TreeP code;
		ClassP returnType;
		string returnName;
		int nbParam;
		int offset;
		ClassP mother;
	};
	
/*
	void prmlst_addParam(ParamsListP list, string type, string name);
	ParamsListP prmlst_getLast (ParamsListP elem);
*/

	/**
	 * Compare deux listes de parametres
	 * @param  l  une liste de parametre
	 * @param  ll une autre liste de parametres
	 * @return    si les parametres ont respectivement les meme types
	 */
	bool prmlst_sameTypes (ParamsListP l, ParamsListP ll);
	/**
	 * Compare une liste d'arguments et la liste de parametre d'une fonction
	 * @param  f    la fonction a tester
	 * @param  args la liste d'arguments
	 * @return      si la liste est conforme aux parametres necessaires pour la fonction
	 */
	bool prmlst_goodCallArgs (FunctionP f, ArgListP args);
	/**
	 * Creer un element de liste de parametres
	 * @param  name le nom du parametre
	 * @param  type type du parametre
	 * @return      l'element cree
	 */
	ParamsListP function_makeParam(string name, string type);
	/**
	 * Affiche une description de la fonction
	 * @param  func fonction
	 * @return      la string contenant la description
	 */
	string function_printFunc(FunctionP func);
	/**
	 * Test si une fonction a un type de retour
	 * @param  func la fonction a tester
	 * @return      vrai si la fonction a un type
	 */
	bool function_hasReturnType(FunctionP func);
	/**
	 * Recherche le nombre de parametres de la fonction
	 * @param  func la fonction
	 * @return      le nombre de parametre
	 */
	int function_howManyArgs(FunctionP func);
#endif

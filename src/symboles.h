#ifndef _SYMBOLES_H_
#define _SYMBOLES_H_

	#include "variable.h"
	#include <string.h>


	typedef struct _Line
	{
		VarP v;
		unsigned int depth;
		e_nature n;
		unsigned int rang;
		struct _Line * next;
	}Line, *LineP;

	typedef struct _SymbolesTable{
		LineP 	current;
		int 	max_rank;
		int* 	nbVarAtRank;
		LineP*	sections;
	}SymbolesTable, *SymbolesTableP;


	/**
	 * Genere une nouvelle table vide
	 * @return la tables
	 */
	SymbolesTableP symTable_newTable();

	/**
	 * Ajoute une ligne a la table deja construite
	 * @param theTable la table
	 * @param l        la ligne
	 */
	void symTable_addLineFromLine(SymbolesTableP theTable, LineP l);

	/**
	 * Ajoute une ligne a la table qui sera construite la
	 * @param theTable la table
	 * @param var      la variable
	 * @param n        la nature de la variable
	 */
	void symTable_addLine(SymbolesTableP theTable, VarP var, e_nature n);


	/**
	 * Regarde si une variable est deja definie
	 * @param  t         la table
	 * @param  varName   le nom de la variable
	 * @param  className le nom de la classe de la variable
	 * @return           si la variable est dedans
	 */
	bool symTable_isVarDefined(SymbolesTableP t, string varName, string className);

	/**
	 * Regarde DANS LE SCOPE COURANT si n nom de variable est utilise
	 * @param  t       la table
	 * @param  varName le nom de variable
	 * @return         si le nom est deja utilise
	 */
	bool symTable_isNameInUse(SymbolesTableP t, string varName);

	/**
	 * Cherche une variable dans la table
	 * @param  t       la table
	 * @param  varName le nom de la variable
	 * @return         la premiere variable avec le nom qui correspond 
	 * (en parcourant a partir de la fin)
	 */
	VarP symTable_getVarFromName(SymbolesTableP t, string varName);


	/**
	 * Affiche l'etat de la table
	 * @param t la table
	 */
	void symTable_printTable(SymbolesTableP t);


	/**
	 * Entre dans un nouveau scope
	 * @param table la table
	 */
	void symTable_enterNewScope(SymbolesTableP table);

	/**
	 * Sortie de scope (le premier element de la liste redevient celui d'avant l'entree dans ce scope)
	 * @param table la table
	 */
	void symTable_exitScope(SymbolesTableP table);

	/**
	 * Est sensee etre utilisee pour nettoyer la memoire...pas utilisee ni iplementee
	 * @param t    la table
	 * @param sect le numero du scope a partir duquel il faut commencer a nettoyer
	 * @TODO
	 */
	void symTable_eraseSection(SymbolesTableP t, int sect);

	/**
	 * Entre dans une fonction, complete la table avec les parametres et optionnelement
	 * this et result
	 * ATTENTION : on entre dans 2 scopes avec cette fonction (PARAM + CODE)
	 * 				on doit donc utiliser deux fois exitScope apres une utilisation
	 * @param  t    table initiale
	 * @param  func la fonction dans laquelle on entre
	 * @param  c    la classe dans laquelle est la fonction
	 * @return      la table completee
	 */
	SymbolesTableP symTable_enterFunction(SymbolesTableP t, FunctionP func, ClassP c);

	/**
	 * Cree une nouvelle ligne dans la table
	 * @param  var la variable de cette ligne
	 * @param  n   sa nature
	 * @return     la ligne
	 */
	LineP symbLine_newLine(VarP var, e_nature n);


	/**
	 * Duplique une table des symboles a partir d'un certain rang
	 * @param  t     la table
	 * @param  depth le rang
	 * @return       la nouvelle table
	 */
	SymbolesTableP symTable_duplicate(SymbolesTableP t, unsigned int depth);

	/** NOT TESTED (NOT USED)*/
	LineP symTable_dupLine(LineP origin,SymbolesTableP receiver);
	LineP symLine_dupLine(LineP origin);

#endif

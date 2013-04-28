#ifndef _CLASS_H_
#define _CLASS_H_

	typedef struct _Class Class, *ClassP; /* pré déclaration afin d'éviter des problèmes d'inclusions croisées */

	#include "tree.h"
	#include "function.h"
	#include "variable.h"
	#include "proj.h"

	typedef struct _ClassFieldList{
	  VarP current;
	  struct _ClassFieldList * next;
	}ClassFieldList, *ClassFieldListP;

	typedef struct _ClassMethodList{
	  FunctionP current;
	  struct _ClassMethodList * next;
	}ClassMethodList, *ClassMethodListP;

	typedef struct _JumpTable
	{
		ClassMethodListP	methods;
		ClassFieldListP 	fields;
	}JumpTable, *JumpTableP;

	struct _Class{
	  string IDClass;
	  FunctionP constructor;
	  ClassFieldListP staticCfl;
	  ClassMethodListP staticCml;
	  ClassFieldListP cfl;
	  ClassMethodListP cml;
	  struct  _Class * super;
	  string superName;
	  TreeP superCallArgs;
	  int nbFields;
	  int nbFunc;
	  int offsetTV;

	  JumpTableP instance;
	  JumpTableP statics;

	};

	typedef struct _ClassList{
		ClassP current;
		int n;
		struct _ClassList * next;
	}ClassList, *ClassListP;

	/**
	 * Ajoute une classe dans la liste globale des classes
	 * @param c classe a ajouter
	 */
	void classList_addClass(ClassP c);
	
	/**
	 * Defini le nom d'une classe
	 * @param c    la classe a modifier
	 * @param name le nom de la classe
	 */
	void class_setName(ClassP c, string name);
	/**
	 * Ajoute un champ a la classe
	 * @param c        la classe
	 * @param isStatic si le champ est static
	 * @param decl     le code du champ
	 */
	void class_addField(ClassP c, bool isStatic, TreeP decl );
	/**
	 * Ajoute une methode a une classe
	 * @param c          la classe
	 * @param visi       spécificité de la methode (0 : normale, 1 : override, 2 : static)
	 * @param methodName nom de la methode
	 * @param returnType nom du type de retour
	 * @param paramList  la liste de parametres associee
	 * @param code       code de la fonction
	 */
	void class_addMethod(ClassP c, int visi, string methodName, string returnType, ParamsListP paramList, TreeP code);
	/**
	 * Affecte le constrcteur de la classe
	 * @param c    la classe
	 * @param pl   la liste de parametres associee
	 * @param code code de la fonction
	 */
	void class_setConstructor(ClassP c, ParamsListP pl, TreeP code);
	
	/**
	 * Retrouve une classe dans la liste globalegrace a som nom
	 * @param  className nom de la classe
	 * @return           la classe trouvee ou null
	 */
	ClassP class_getClass(string className);
	/**
	 * Retrouve la place de la classe dans la liste
	 * @param  c la classe
	 * @return   la place de la classe
	 */
	int class_getNb(ClassP c);
	/**
	 * Retrouve la place de la classe dans la liste
	 * @param  className le nom de la classe
	 * @return           la place de la classe
	 */
	int class_getNbFromName(string className);
	/**
	 * Set la super classe d'une classe
	 * @param c     classe fille
	 * @param super classe mere
	 * @param args  code de l'appel au constructeur
	 */
	void class_setSuper(ClassP c, string super, TreeP args);
	/**
	 * Affiche une description de toutes les classes
	 * @return la string contenant les descriptions
	 */
	string classList_print();
	/**
	 * Affiche une description d'une classe
	 * @param  class la classe a decrire
	 * @return       la desciption
	 */
	string class_print(ClassP class);

	/**
	 * Regarde si une classe herite d'une autre
	 * @param  c  fille
	 * @param  cc parent
	 * @return    si la classe fille herite de la mere
	 */
	bool class_isinheritedFrom(ClassP c, ClassP cc);
	/**
	 * Regarde si une variable d'une classe peut etre affectee a une variable d'une autre classe 
	 * @param  c  classe fille
	 * @param  cc parent
	 * @return    si on peut affecter
	 */
	bool class_canAffect(ClassP c, ClassP cc);

	/**
	 * Retourne la variable d'instance de la classe 
	 * @param  c       classe
	 * @param  varName nom de la variable
	 * @return         la variable
	 */
	VarP class_getInstanceFieldFromName(ClassP c, string varName);
	/**
	 * Retourne la variable statique de la classe 
	 * @param  c       classe
	 * @param  varName nom de la variable
	 * @return         la variable
	 */
	VarP class_getStaticFieldFromName(ClassP c, string varName);

	/**
	 * Retourne la methode d'instance de la classe 
	 * @param  c       classe
	 * @param  varName nom de la variable
	 * @return         la methode
	 */
	FunctionP class_getInstanceMethFromName(ClassP c, string funcName);
	/**
	 * Retourne la methode statique de la classe 
	 * @param  c       classe
	 * @param  varName nom de la variable
	 * @return         la methode
	 */
	FunctionP class_getStaticMethFromName(ClassP c, string funcName);

	/**
	 * Regarde le nombre de champs d'une classe
	 * @param  c la classe
	 * @return   le nombre de champs
	 */
	int class_getNbFields(ClassP c);

	/**
	 * Calcule l'offset d'un champ ou d'une methode d'instance d'une classe
	 * @deprecated
	 * @param  c       la classe
	 * @param  argName le nom de l'objet a trouver
	 * @return         l'offset
	 */
	int jtable_getOffsetStatic(ClassP c, string argName);
	/**
	 * Calcule l'offset d'un champ ou d'une methode statique d'une classe
	 * @deprecated
	 * @param  c       la classe
	 * @param  argName le nom de l'objet a trouver
	 * @return         l'offset
	 */
	int jtable_getOffsetInst(ClassP c, string argName);
	/**
	 * Duplique une table de sauts
	 * @param  j la table a dupliquer
	 * @return   la table dupliquee
	 */
	JumpTableP jtable_duplicate(JumpTableP j);
	/**
	 * Cherche le dernier element d'une liste
	 * @param  fl la liste
	 * @return    l'element
	 */
	ClassFieldListP fl_getLast(ClassFieldListP fl);
	/**
	 * Cherche le dernier element d'une liste
	 * @param  ml la liste
	 * @return    l'element
	 */
	ClassMethodListP ml_getLast(ClassMethodListP ml);
	/**
	 * Cherche si une methode doit etre override
	 * @param  orig liste dans laquelle on cherche
	 * @param  func la fonctionque l'on cherche a ajouter dans cette liste
	 * @return      l'element de la liste qui contient la methode a override ou null
	 *                        si la methode n'a pas a etre override
	 */
	ClassMethodListP override(ClassMethodListP orig, FunctionP func);
	/**
	 * Genere une table de saut pour une classe donnee
	 * @param  c la classe
	 * @return   si la geneation s'est bien deroulee
	 */
	bool class_generateJumpTable(ClassP c);




#endif

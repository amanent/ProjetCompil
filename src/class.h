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
	 * [class_addMethod description]
	 * @param c          [description]
	 * @param visi       [description]
	 * @param methodName [description]
	 * @param returnType [description]
	 * @param paramList  [description]
	 * @param code       [description]
	 */
	void class_addMethod(ClassP c, int visi, string methodName, string returnType, ParamsListP paramList, TreeP code);
	void class_setConstructor(ClassP c, ParamsListP pl, TreeP code);
	
	ClassP class_getClass(string super);
	int class_getNb(ClassP c);
	int class_getNbFromName(string className);
	void class_setSuper(ClassP c, string super, TreeP args);
	string classList_print();
	string class_print(ClassP class);
	bool class_isinheritedFrom(ClassP c, ClassP cc);
	bool class_canAffect(ClassP c, ClassP cc);

	VarP class_getInstanceFieldFromName(ClassP c, string varName);
	VarP class_getStaticFieldFromName(ClassP c, string varName);

	FunctionP class_getInstanceMethFromName(ClassP c, string funcName);
	FunctionP class_getStaticMethFromName(ClassP c, string funcName);

	int class_getNbFields(ClassP c);

	int jtable_getOffsetStatic(ClassP c, string argName);
	int jtable_getOffsetInst(ClassP c, string argName);
	JumpTableP jtable_duplicate(JumpTableP j);
	ClassFieldListP fl_getLast(ClassFieldListP fl);
	ClassMethodListP ml_getLast(ClassMethodListP ml);
	ClassMethodListP override(ClassMethodListP orig, FunctionP func);
	bool class_generateJumpTable(ClassP c);




#endif

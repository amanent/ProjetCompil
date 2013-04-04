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
	};

	typedef struct _ClassList{
		ClassP current;
		struct _ClassList * next;
	}ClassList, *ClassListP;


	void classList_addClass(ClassP c);
	void class_setName(ClassP c, string name);
	void class_addField(ClassP c, bool isStatic, TreeP decl );
	void class_addMethod(ClassP c, int visi, string methodName, string returnType, ParamsListP paramList, TreeP code);
	void class_setConstructor(ClassP c, ParamsListP pl, TreeP code);
	ClassP class_getClass(string super);
	void class_setSuper(ClassP c, string super, TreeP args);
	string classList_print();
	string class_print(ClassP class);
	bool class_isinheritedFrom(ClassP c, ClassP cc);

#endif

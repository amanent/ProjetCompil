#ifndef _CLASS_H_
#define _CLASS_H_

	typedef struct _Class Class, *ClassP; /* pré déclaration afin d'éviter des problèmes d'inclusions croisées */

	#include "tree.h"
	#include "function.h"
	#include "variable.h"
	#include "proj.h"

	typedef struct _ClassFieldList{
	  ClassFieldP current;
	  struct _ClassFieldList * next;
	}ClassFieldList, *ClassFieldListP;

	typedef struct _ClassMethodList{
	  ClassMethodP current;
	  struct _ClassMethodList * next;
	}ClassMethodList, *ClassMethodListP;

	struct _Class{
	  string IDClass;
	  ClassMethodP constructor;
	  ClassFieldList staticCfl;
	  ClassMethodList staticCml;
	  ClassFieldList cfl;
	  ClassMethodListP cml;
	  struct  _Class * super;
	  string superName;
	  TreeP superCallArgs;
	};

	typedef struct _ClassList{
		ClassP current;
		struct _ClassList * next;
	}ClassList, *ClassListP;


	void classList_addClass(string name);
	/* void class_addField(ClassP c, string type, string name, TreeP var ); */
	void class_addField(ClassP c, int isStaticp, TreeP decl );
	ClassMethodP class_addMethodByClass(ClassP c, string methodName, string type);
	/*ClassMethodP class_addMethod(string type, string c, string methodName, string returnType, ParamsListP paramList, TreeP code); */
	ClassMethodP class_addMethod(ClassP c, int visi, string methodName, string returnType, ParamsListP paramList, TreeP code); /* L'autre ne me convenait pas */
	void class_setConstructor(ClassP c, ParamsListP pl, TreeP code);
	bool class_setSuperClass(ClassP c, string super);
	void class_setSuperName(ClassP c, string super);
	void class_setParam(ClassMethodP meth, ParamsListP pl);
	void class_addParent(ClassP c, string super, TreeP args);

#endif
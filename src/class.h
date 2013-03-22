#ifndef _CLASS_H_
#define _CLASS_H_

#include "proj.h"
#include "function.h"
typedef struct _ClassField{
  int visibility;
  Var v;
}ClassField, *ClassFieldP;

typedef struct _ClassMethod{
  int visibility;
  string type;
  Function function;
}ClassMethod, *ClassMethodP;

typedef struct _ClassFieldList{
  ClassFieldP current;
  struct _ClassFieldList * next;
}ClassFieldList, *ClassFieldListP;

typedef struct _ClassMethodList{
  ClassMethodP current;
  struct _ClassMethodList * next;
}ClassMethodList, *ClassMethodListP;

typedef struct _Class{
  string IDClass;
  ClassMethod constructor;
  ClassFieldList staticCfl;
  ClassMethodList staticCml;
  ClassFieldList cfl;
  ClassMethodList cml;
  struct  _Class * super;
  string superName;
  TreeP superCallArgs;
}Class, *ClassP;

typedef struct _ClassList{
	ClassP current;
	struct _ClassList * next;
}ClassList, *ClassListP;

#endif

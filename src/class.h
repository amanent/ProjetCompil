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
  Function function;
}ClassMethod, *ClassMethodP;

typedef struct _ClassFieldList{
  ClassField * current;
  struct _ClassFieldList * next;
}ClassFieldList, *ClassFieldListP;

typedef struct _ClassMethodList{
  ClassMethod * current;
  struct _ClassMethodList * next;
}ClassMethodList, *ClassMethodListP;

typedef struct _Class{
  string IDClass;
  ClassFieldList cfl;
  ClassMethodList cml;
  struct  _Class * super;
}Class, *ClassP;

#endif

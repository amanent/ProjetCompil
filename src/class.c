#include "class.h"

ClassListP classList = (ClassListP)malloc(sizeof(ClassList));

void classList_addClass(string name){
	ClassP newClass = (ClassP)malloc(sizeof(Class));
	newClass.IDClass = (string)malloc(strlen(name)*sizeof(char));
	strcpy(newClass.IDClass,name);
	ClassListP newTop = (ClassListP)malloc(sizeof(ClassList));
	newTop.current = newClass;
	newTop.next = classList;
	classList = newTop;
}

void class_addField(ClassP c, string type, string name, TreeP var ){
	ClassFieldP newClassField = (ClassFieldP)malloc(sizeof(ClassField));
	newClassField.v.typeName = (string)malloc(strlen(type)*sizeof(char) + 1);
	newClassField.v.ID = (string)malloc(strlen(name)*sizeof(char) + 1);
	strcpy(newClassField.v.typeName,type);
	strcpy(newClassField.v.ID,name);
	newClassField.v.value = var;
	ClassFieldListP newCFL = (ClassFieldListP)malloc(sizeof(ClassFieldList));
	newCFL.current = newClassField;
	newCFL.next = c.cfl;
	c.cfl = newCFL;
}

ClassMethodP class_addMethod(ClassP c, string methodName, string type){
	ClassMethodP newMeth = (ClassMethodP)malloc(sizeof(ClassMethod));
	newMeth.function.ID = (string)malloc(strlen(methodName)*sizeof(char));
	newMeth.function.returnName = (string)malloc(strlen(type)*sizeof(char));
	strcpy(newMeth.function.ID,methodName);
	strcpy(newMeth.function.returnName,type);
	ClassMethodListP newCML = (ClassMethodListP)malloc(sizeof(ClassMethodList));
	newCML.current = newMeth;
	newCML.next = c.cml;
	c.cml = newCML;
	return newMeth;
}

void class_setConstructorParam(ClassMethodP constructor, ParamsListP pl){
	constructor.function.paramsList = pl;
}

void class_setSuper(ClassP c, string super){
	c.superName = (string)malloc(strlen(super)*sizeof(char));
}

void class_setParam(ClassMethodP meth, ParamsListP pl){
	meth.function.paramsList = pl;
}

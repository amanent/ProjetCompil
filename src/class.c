#include "class.h"

ClassListP classList = (ClassListP)malloc(sizeof(ClassList));

void classList_addClass(string name){
	ClassP newClass = (ClassP)malloc(sizeof(Class));
	strcpy(newClass.IDClass,name);
}

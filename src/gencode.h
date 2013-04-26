#ifndef _GENCODE_H_
#define _GENCODE_H_

	string writeCode(string prevCode, bool breakPoint, string label, string code, string arg, string comm);
	string strcatwalloc(string s1, string s2);
	string gencode(TreeP tree);
	string genCodeFunc(ClassP c, FunctionP func);
	string genCodeConst(ClassP c);
	string genBaseCode(ClassListP cl_par);
	string genBaseFuncCode();
	string genFieldInitCode(ClassFieldListP cfl);
	string genStaticFieldInitCode(ClassListP cl);
	string genTVCode(ClassListP cl);

#endif
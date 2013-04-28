/*
 * verifContext.h
 */

#ifndef VERIFCONTEXT_H_
#define VERIFCONTEXT_H_

#include "proj.h"
#include "class.h"
#include <string.h>
#include "symboles.h"
/**
 * Fonction qui va vérifier tout le code du programme
 * @return le code d'erreur si la vérification a rencontre une erreur
 */
int verif_contextuelle();


/**
 * Passe de résolution des noms
 * Toutes les classes sont vérifiées et on link les types de tous les 
 * champs/methodes aux bonnes classes
 * @return correct ?
 */
bool verif_nameResolution();

/**
 * Construction de la table de sauts de toutes les classes
 * @return correct ?
 */
bool verif_contructJumpTable();
/**
 * Verifie toutes les classes
 * @return correct ?
 */
bool verif_allClassesCode();

/**
 * Verifie le code d'une classe
 * @param  c la classe a verifier
 * @return   correct ?
 */
bool verif_classCode(ClassP c);

/**
 * Verifie si la liste de parametres d'une fonction est valide
 * @param  func la fonction sur laquelle porte la verification
 * @return      correct ?
 */
bool verif_paramList(FunctionP func);

/**
 * Verifie le constructeur d'une classe
 * @param  st la table des symboles associee a la classe
 * @param  c  la classe
 * @return    correct ?
 */
bool verif_constructor(SymbolesTableP st, ClassP c);
/**
 * Verifie le code d'une fonction
 * @param  st   la table des symboles associee a la classe
 * @param  func la methode
 * @param  c    la classe dans laquelle est definie cette methode
 * @return      correct ?
 */
bool verif_func(SymbolesTableP st, FunctionP func, ClassP c);
/**
 * Verifie un morceau de code
 * @param  st   table des symboles associee
 * @param  tree le code
 * @param  c    la classe dans laquelle se trouve ce code (NULL = main)
 * @param  f    la fontion dans laquelle se trouve ce code (NULL = main) 
 * @return      correct ?
 */
bool verif_types(SymbolesTableP st, TreeP tree, ClassP c, FunctionP f);

/**
 * Rempli la table des symboles d'une classe
 * @param  cfl la liste de champs a rentrer
 * @param  st  la table a remplir
 * @return     a l'origine les offset / @deprecated
 */
int fillSymTableClassVar(ClassFieldListP cfl, SymbolesTableP st);
/**
 * Rempli la table des symbole des variables statiques d'une classe
 * Genere les offsets generaux des variables statiques
 * @param cfl la liste a utiliser pour remplir
 * @param st  la table a remplir
 */
void fillSymTableStaticVar(ClassFieldListP cfl, SymbolesTableP st);



/**@deprecatd*/
int fillSymTableClassFunc(ClassMethodListP cml, SymbolesTableP st);


#endif /* VERIFCONTEXT_H_ */

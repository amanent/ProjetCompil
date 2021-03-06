#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "proj.h"
#include "proj_y.h"
#include "gencode.h"
#include "verifContext.h"

extern int yyparse();
extern TreeP mainCode;
extern ClassListP classList;

/* Niveau de 'verbosite'.
 * Par defaut, n'imprime que le resultat et les messages d'erreur
 */
bool verbose = FALSE;

/* Evaluation ou pas. Par defaut, on evalue les expressions (si on appelle
 * bien la fonction eval dont l'en-tete est ci-dessus et le squelette du
 * code en fin de fichier.
 */
bool noEval = FALSE;

/* code d'erreur a retourner */
int errorCode = NO_ERROR;

/* Descripteur de fichier pour la lecture des donnees par get */
FILE *fd = NIL(FILE), *out = NIL(FILE);


/* Appel:
 *   tp [-option]* programme.txt donnees.dat
 * Le fichier de donnees est obligatoire si le programme execute la
 * construction GET (pas de lecture au clavier), facultatif sinon.
 * Les options doivent apparaitre avant le nom du fichier du programme.
 * Options: -[eE] -[vV] -[hH?]
 */
int main(int argc, char **argv) {
	int fi;
	int i, res;
	string fileName = NULL;

	for(i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'v': case 'V':
				verbose = TRUE; continue;
			case 'e': case 'E':
				noEval = TRUE; continue;
			case 'o':
				if(argv[i+1]==NULL || argv[i+1][0]=='-') return -1;
				fileName = argv[++i]; continue;
			case '?': case 'h': case 'H':
				fprintf(stderr, "Command: tp -e -v program.txt data.dat\n");
				exit(USAGE_ERROR);
			default:
				fprintf(stderr, "Error: Unknown option: %c\n", argv[i][1]);
				exit(USAGE_ERROR);
			}
		} else break;
	}

	if (i == argc) {
		fprintf(stderr, "Error: Missing program file\n");
		exit(USAGE_ERROR);
	}

	if ((fi = open(argv[i++], O_RDONLY)) == -1) {
		fprintf(stderr, "Error: Cannot open %s\n", argv[i-1]);
		exit(USAGE_ERROR);
	}

	// redirige l'entree standard sur le fichier...
	close(0); dup(fi); close(fi);

	/*if (i < argc) { // fichier dans lequel lire les valeurs pour get()
		if ((fd = fopen(argv[i], "r")) == NULL) {
			fprintf(stderr, "Error: Cannot open %s\n", argv[i]);
			exit(USAGE_ERROR);
		}
	}*/

	if(fileName == NULL) {
		fileName = NEW(10, char);
		strcpy(fileName, "a.out");
	}

	/* Lance l'analyse syntaxique de tout le source, en appelant yylex au fur
	 * et a mesure. Execute les actions semantiques en parallele avec les
	 * reductions.
	 * yyparse renvoie 0 si le source est syntaxiquement correct, une valeur
	 * differente de 0 en cas d'erreur syntaxique (eventuellement causee par des
	 * erreurs lexicales).
	 * Comme l'interpretation globale est automatiquement lancee par les actions
	 * associees aux reductions, une fois que yyparse a termine il n'y
	 * a plus rien a faire (sauf fermer les fichiers)
	 * Si le code du programme contient une erreur, on bloque l'evaluation.
	 * S'il n y a que des erreurs contextuelles on essaye de ne pas s'arreter
	 * a la premiere mais de continuer l'analyse pour en trouver d'autres, quand
	 * c'est possible.
	 */

	fprintf(stderr, "--Compiling\n");
	res = yyparse();
	fprintf(stderr, "--A priori c'est bon :)\n");
	//printf("resultat:\n%s", classList_print());
	//pprintMain(mainCode);

	//*
	ClassP integer = NEW(1, Class), sstring = NEW(1, Class);
	class_setName(integer, "Integer");
	class_setName(sstring, "String");
	classList_addClass(integer);
	classList_addClass(sstring);

	fprintf(stderr, "--Fin des initialisation des classes de base\n");

	switch(verif_contextuelle()) {
		case 1: fprintf(stderr, "--Verif contextuelle : ok\n"); break;
		case -1: fprintf(stderr, "--Verif contextuelle : erreur a la résolution des noms\n"); return -1;
		case -2: fprintf(stderr, "--Verif contextuelle : erreur dans le code d'une classe\n"); return -2;
		case -3: fprintf(stderr, "--Verif contextuelle : erreur dans le code principal\n"); return -3;
		default: fprintf(stderr, "--Verif contextuelle : unknown error\n"); return -4;
	}
/*
	ClassListP cl = classList;
	while(cl!= NULL)
	{
		ClassMethodListP cml = cl->current->instance->methods;
		while(cml!=NULL)
		{
			fprintf(stderr, "%s : %s, %d\n", cl->current->IDClass, cml->current->ID, cml->current->offset);
			cml = cml->next;
		}
		cl=cl->next;
	}
*/
	string toto = NULL;
	toto = genBaseCode(classList->next->next); // les deux next servent a éviter les deux types primitifs
	//fprintf(stderr, "caca \n");
	toto = strcatwalloc(toto, gencode(mainCode));
	//fprintf(stderr, "caca2 \n");
	toto = writeCode(toto, TRUE, NULL, "STOP", NULL, NULL);

	// ici pour pas creer le fichier si pas besoin
	if ((out = fopen(fileName, "w")) == NULL) {
		fprintf(stderr, "Error: Cannot open %s\n", fileName);
		exit(USAGE_ERROR);
	}

	//printf("--code :\n%s\n", toto);
	fprintf(out, "--code :\n%s\n", toto);

	fprintf(stderr, "--Compilation : ok, in file : %s\n", fileName);

	if (fd != NIL(FILE)) fclose(fd);
	if (out != NIL(FILE)) fclose(out);
	return res ? SYNTAX_ERROR : errorCode;
}


void setError(int code) {
	errorCode = code;
	if (code != NO_ERROR) { noEval = TRUE; }
}

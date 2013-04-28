ProjetCompil
============

Mattieux Allié
Benjamin Blois
Dylan Darcy
Arnaud Manente


Présentation
------------
	Gaouc (gaou compiler) est un compilateur pour le micro langage mls vers le 
	pseudo assembleur simple.
	Toutes les spécificités du langage sont gérées, mis a part l'acces implicite 
	à des champs statiques ou l'appel implicite de méthodes statiques.
	
	Le programme, une fois compilé, se trouve dans le repertoire bin, avec tous
	les test cases.

Utilisation
-----------
	Il y a deux moyens d'utiliser gaouc :

	- Soit depuis le Makefile se trouvant dans le repertoire src, et prenant les 
		paramètres suivants :
		 - all : (ou make tout seul), compile tout le projet.
		 - testi : (où i est un nombre entre 1 et 5) compile le programme et 
		 	lance le test numéro i (détaillé après).
		 - clean : supprime tout les fichiers objets et temporaires.
		 - mrproper : comme clean,mais supprime également l'executable.
		 - redo : clean et recompile l'ensemble du programme.

	- Soit directement en ligne de commande, suivant cette syntaxe :
		gaouc [-o fichierDeSortie] fichierSource

		/!\, l'ordre des paramètres est important, si le -o est après le fichier
		source, il ne sera pas pris en compte.
		
		Si le fichier destination n'est pas fourni, par défaut, le programme 
		sera compilé dans a.out.

	En cas d'erreur dans le code source, un message d'erreur le plus clair 
	possible est affiché. Si cela ne permet pas de localiser l'erreur, il faut 
	malheureusement encore aller dans le code du programme, et décommenter les 
	lignes "fprintf(stderr, "--Treating : %s\n", tree->op)" dans les fonctions
	de parcours récursif (gencode@gencode.c et verif_types@verifContext.c).
	Ca reste actuellement le meilleur moyen de localiser une erreur de manière 
	précise.

Cas de tests
------------
Les différents cas de tests se trouvent dans le repertoire bin.

	test1 : verification de la compilation du code principal, avec une variable,
		une affectation et différents opérateurs.

	test2 : un code assez complèxe qui ne compile pas car il y a un acces
		implicite a un champ de classe (static).

	test3 : test avec plusieurs classes, contenant des champs homonymes (c'est 
		autorisé au sein de classes différentes), des champs statics ou non,
		des méthodes statiques ou non, et plusieurs variables/paramètres.
		L'enchaimement d'oppération est aussi testé, ainsi que les tables
		virtuelles.

	test4 : test de l'héritage, du passage de paramètres au constructeur père,
		acces aux variables de la classe mère dans la fille.
		On teste aussi l'utilisation de super et de this.
		On teste aussi les blocs imbriqués dans ce fichier.
		On reteste aussi le sens des opérations dans le constructeur.

	test 5 : Dans ce dernier cas de test, on travaille sur la redéfinition de 
		champs dans une classe fille et sur le cast pour y acceder.
		On reteste aussi le super.
/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 25 "proj.y"

#include <stdio.h>
#include "proj.h"
#include "class.h"
#include "function.h"

#define NOVERBOSE

extern int yylineno;
extern int yylex();	/* fournie par Flex */
extern TreeP mainCode;
ClassP current;


void yyerror(char *ignore) {
  printf("erreur de syntaxe: Ligne %d\n", yylineno);
}

void pprintf(char *c) {
#ifdef VERBOSE
	printf("%s", c);
#endif
}
void pprintfs(char* c, char* c2) {
#ifdef VERBOSE
	printf("%s %s\n", c, c2);
#endif
}
void pprintfi(char* c, int i) {
#ifdef VERBOSE
	printf("%s %i\n", c, i);
#endif
}
/* Méthodes utilisées : 
	classList_addClass($2);  (nom de la classe)
	class_setConstructor(classList->current, $4, $7);  (classe, paramètres constructeur, code du constructeur)
	function_makeParam($1, $3); (params: nomParam, typeParam)
	class_setSuper(classList->current, $2, $4); (params: classe, superType, arguments constructeur père)
	class_addVar(classList->current, $1, $2); (params: classe, isStatic, arbre de decl de la var)
	class_addMethod($1, $3, $7, $5, $9); (params: visibility, nom, type de retour,liste des paramètres, arbre du corps de la fonction)
*/



/* Line 268 of yacc.c  */
#line 116 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CLASS = 258,
     EXT = 259,
     IS = 260,
     DEF = 261,
     OVR = 262,
     STAT = 263,
     RET = 264,
     RETS = 265,
     AS = 266,
     VAR = 267,
     NEW = 268,
     IF = 269,
     THEN = 270,
     ELSE = 271,
     AFF = 272,
     ID = 273,
     IDCL = 274,
     CST = 275,
     STR = 276,
     RELOP = 277,
     ADD = 278,
     SUB = 279,
     MUL = 280,
     DIV = 281,
     CONCAT = 282,
     DECL = 283,
     LSTARG = 284,
     BLCDECL = 285,
     CAST = 286,
     INST = 287,
     MSGSNT = 288,
     LAFFECT = 289,
     LSTINST = 290,
     UNARYSUB = 291,
     UNARYADD = 292
   };
#endif
/* Tokens.  */
#define CLASS 258
#define EXT 259
#define IS 260
#define DEF 261
#define OVR 262
#define STAT 263
#define RET 264
#define RETS 265
#define AS 266
#define VAR 267
#define NEW 268
#define IF 269
#define THEN 270
#define ELSE 271
#define AFF 272
#define ID 273
#define IDCL 274
#define CST 275
#define STR 276
#define RELOP 277
#define ADD 278
#define SUB 279
#define MUL 280
#define DIV 281
#define CONCAT 282
#define DECL 283
#define LSTARG 284
#define BLCDECL 285
#define CAST 286
#define INST 287
#define MSGSNT 288
#define LAFFECT 289
#define LSTINST 290
#define UNARYSUB 291
#define UNARYADD 292




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 231 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  27
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   191

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNRULES -- Number of states.  */
#define YYNSTATES  131

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      38,    39,     2,     2,    42,     2,    45,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    43,    44,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    20,    22,    23,    25,    27,
      31,    35,    36,    42,    43,    46,    48,    50,    53,    54,
      56,    66,    67,    69,    71,    72,    75,    77,    80,    86,
      87,    91,    92,    94,    96,   100,   101,   103,   107,   113,
     114,   116,   118,   121,   124,   126,   129,   134,   141,   145,
     149,   153,   157,   161,   165,   168,   171,   173,   177,   184,
     190,   197,   199,   201,   203,   207,   209,   211,   213
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    67,    -1,    48,    47,    -1,    49,    75,
      38,    50,    39,    53,    66,     5,    40,    54,    41,    -1,
       3,    -1,    -1,    51,    -1,    52,    -1,    52,    42,    51,
      -1,    74,    43,    75,    -1,    -1,     4,    75,    38,    64,
      39,    -1,    -1,    55,    54,    -1,    56,    -1,    58,    -1,
      57,    62,    -1,    -1,     8,    -1,    59,     6,    74,    38,
      50,    39,    60,     5,    67,    -1,    -1,     7,    -1,     8,
      -1,    -1,    10,    75,    -1,    62,    -1,    62,    61,    -1,
      12,    74,    43,    75,    63,    -1,    -1,    17,    71,    44,
      -1,    -1,    65,    -1,    71,    -1,    71,    42,    65,    -1,
      -1,    67,    -1,    40,    68,    41,    -1,    40,    61,     5,
      69,    41,    -1,    -1,    69,    -1,    70,    -1,    70,    69,
      -1,    71,    44,    -1,    67,    -1,     9,    44,    -1,    73,
      17,    71,    44,    -1,    14,    71,    15,    70,    16,    70,
      -1,    71,    76,    71,    -1,    71,    27,    71,    -1,    71,
      23,    71,    -1,    71,    24,    71,    -1,    71,    25,    71,
      -1,    71,    26,    71,    -1,    23,    71,    -1,    24,    71,
      -1,    72,    -1,    38,    71,    39,    -1,    38,    11,    75,
      43,    71,    39,    -1,    13,    75,    38,    64,    39,    -1,
      72,    45,    74,    38,    64,    39,    -1,    73,    -1,    20,
      -1,    21,    -1,    72,    45,    74,    -1,    74,    -1,    18,
      -1,    19,    -1,    22,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    70,    70,    74,    77,    88,    90,    91,    94,    95,
     103,   106,   107,   110,   111,   114,   115,   118,   121,   122,
     125,   132,   133,   134,   137,   138,   143,   144,   147,   153,
     154,   157,   158,   161,   162,   165,   166,   169,   170,   173,
     174,   177,   178,   181,   182,   183,   184,   185,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   199,   200,   201,
     202,   203,   204,   205,   208,   209,   212,   215,   218
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS", "EXT", "IS", "DEF", "OVR",
  "STAT", "RET", "RETS", "AS", "VAR", "NEW", "IF", "THEN", "ELSE", "AFF",
  "ID", "IDCL", "CST", "STR", "RELOP", "ADD", "SUB", "MUL", "DIV",
  "CONCAT", "DECL", "LSTARG", "BLCDECL", "CAST", "INST", "MSGSNT",
  "LAFFECT", "LSTINST", "UNARYSUB", "UNARYADD", "'('", "')'", "'{'", "'}'",
  "','", "':'", "';'", "'.'", "$accept", "Program", "Class", "ClassAlloc",
  "ListParamO", "ListParam", "Param", "ExtendO", "ListDeclO", "Decl",
  "DeclField", "StaticO", "DeclMethod", "OvOrStatO", "ReturnO",
  "ListDeclV", "DeclV", "AffectO", "ListArgO", "ListArg", "BlocO", "Bloc",
  "ListInstO", "ListInst", "Inst", "Exp", "Exp2", "LeftAffect", "Id",
  "Idcl", "Relop", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,    40,    41,
     123,   125,    44,    58,    59,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    47,    48,    49,    50,    50,    51,    51,
      52,    53,    53,    54,    54,    55,    55,    56,    57,    57,
      58,    59,    59,    59,    60,    60,    61,    61,    62,    63,
      63,    64,    64,    65,    65,    66,    66,    67,    67,    68,
      68,    69,    69,    70,    70,    70,    70,    70,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    72,    72,    72,
      72,    72,    72,    72,    73,    73,    74,    75,    76
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,    11,     1,     0,     1,     1,     3,
       3,     0,     5,     0,     2,     1,     1,     2,     0,     1,
       9,     0,     1,     1,     0,     2,     1,     2,     5,     0,
       3,     0,     1,     1,     3,     0,     1,     3,     5,     0,
       1,     1,     2,     2,     1,     2,     4,     6,     3,     3,
       3,     3,     3,     3,     2,     2,     1,     3,     6,     5,
       6,     1,     1,     1,     3,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     5,    39,     0,     0,     0,     2,     0,     0,     0,
       0,    66,    62,    63,     0,     0,     0,     0,    26,    44,
       0,    40,    41,     0,    56,    61,    65,     1,     3,    67,
       0,    45,     0,     0,     0,    61,    54,    55,     0,     0,
       0,    27,    37,    42,    68,     0,     0,     0,     0,     0,
      43,     0,     0,     0,     6,     0,    31,     0,     0,    57,
       0,    50,    51,    52,    53,    49,    48,    64,     0,     0,
       7,     8,     0,    29,     0,    32,    33,     0,     0,    38,
      31,    46,    11,     0,     0,     0,    28,    59,     0,     0,
       0,     0,     0,    35,     9,    10,     0,    34,    47,    58,
      60,     0,     0,    36,    30,    31,     0,     0,    13,    12,
      22,    19,     0,    13,    15,     0,    16,     0,     4,    14,
      17,     0,     0,     6,     0,    24,     0,     0,    25,     0,
      20
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    69,    70,    71,    93,   112,   113,
     114,   115,   116,   117,   127,    17,    18,    86,    74,    75,
     102,    19,    20,    21,    22,    23,    24,    35,    26,    30,
      51
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -72
static const yytype_int16 yypact[] =
{
       2,   -72,    87,    20,     2,     6,   -72,   -30,     8,     6,
      48,   -72,   -72,   -72,    48,    48,    -5,    19,    31,   -72,
     -10,   -72,   110,   113,   -13,    27,   -72,   -72,   -72,   -72,
      11,   -72,    16,    12,    14,   -72,   -72,   -72,     6,   142,
     110,   -72,   -72,   -72,   -72,    48,    48,    48,    48,    48,
     -72,    48,     8,    48,     8,     6,    48,   110,    21,   -72,
      10,   -14,   -14,   -72,   -72,   160,   160,    29,   119,    18,
     -72,    23,    30,    53,    35,   -72,    56,    59,    48,   -72,
      48,   -72,    84,     8,     6,    48,   -72,   -72,    48,   110,
     152,    50,     6,    51,   -72,   -72,   129,   -72,   -72,   -72,
     -72,    52,    92,   -72,   -72,    48,    62,    64,   114,   -72,
     -72,    98,    65,   114,   -72,    31,   -72,   103,   -72,   -72,
     -72,     8,    75,     8,    77,   104,     6,   127,   -72,    51,
     -72
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   143,   -72,   -72,    26,    76,   -72,   -72,    45,   -72,
     -72,   -72,   -72,   -72,   -72,   144,    46,   -72,   -71,    72,
     -72,     0,   -72,   -12,   -54,     7,   -72,     5,    -6,    -8,
     -72
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -24
static const yytype_int16 yytable[] =
{
       6,    33,    32,    77,     6,     1,    38,    25,     9,    91,
      43,    47,    48,    11,    31,    12,    13,    34,    14,    15,
      27,    36,    37,    39,    40,    29,    11,    25,    60,    57,
      58,    42,    52,    16,   107,    98,    44,    45,    46,    47,
      48,    49,     2,     8,    53,    25,    67,    73,    72,    54,
      56,    79,    61,    62,    63,    64,    65,    82,    66,    55,
      68,     9,    25,    76,    78,    83,    11,    80,    12,    13,
      85,    14,    15,    84,    87,    89,    95,    72,    44,    45,
      46,    47,    48,    49,   101,    90,    16,    76,    92,   100,
     105,     2,    96,   103,    25,    76,     7,   106,    88,     8,
       9,    10,   108,   109,   -23,    11,   118,    12,    13,   121,
      14,    15,    76,   123,   126,   122,   125,    72,   128,     7,
     -21,   110,   111,     9,    10,    16,   -18,     2,    11,   130,
      12,    13,   129,    14,    15,    44,    45,    46,    47,    48,
      49,    44,    45,    46,    47,    48,    49,    28,    16,   124,
       2,    44,    45,    46,    47,    48,    49,    50,   119,    94,
      97,   120,    41,    81,    44,    45,    46,    47,    48,    49,
       0,     0,     0,   104,    44,    45,    46,    47,    48,    49,
       0,    59,   -24,    45,    46,    47,    48,   -24,     0,     0,
       0,    99
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-72))

#define yytable_value_is_error(yytable_value) \
  ((yytable_value) == (-24))

static const yytype_int16 yycheck[] =
{
       0,     9,     8,    57,     4,     3,    11,     2,    13,    80,
      22,    25,    26,    18,    44,    20,    21,    10,    23,    24,
       0,    14,    15,    16,     5,    19,    18,    22,    40,    15,
      38,    41,    45,    38,   105,    89,    22,    23,    24,    25,
      26,    27,    40,    12,    17,    40,    52,    55,    54,    38,
      38,    41,    45,    46,    47,    48,    49,    39,    51,    43,
      53,    13,    57,    56,    43,    42,    18,    38,    20,    21,
      17,    23,    24,    43,    39,    16,    84,    83,    22,    23,
      24,    25,    26,    27,    92,    78,    38,    80,     4,    39,
      38,    40,    85,    93,    89,    88,     9,     5,    42,    12,
      13,    14,    40,    39,     6,    18,    41,    20,    21,     6,
      23,    24,   105,    38,    10,   121,    39,   123,   126,     9,
       6,     7,     8,    13,    14,    38,    12,    40,    18,   129,
      20,    21,     5,    23,    24,    22,    23,    24,    25,    26,
      27,    22,    23,    24,    25,    26,    27,     4,    38,   123,
      40,    22,    23,    24,    25,    26,    27,    44,   113,    83,
      88,   115,    18,    44,    22,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    44,    22,    23,    24,    25,    26,    27,
      -1,    39,    22,    23,    24,    25,    26,    27,    -1,    -1,
      -1,    39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    40,    47,    48,    49,    67,     9,    12,    13,
      14,    18,    20,    21,    23,    24,    38,    61,    62,    67,
      68,    69,    70,    71,    72,    73,    74,     0,    47,    19,
      75,    44,    74,    75,    71,    73,    71,    71,    11,    71,
       5,    61,    41,    69,    22,    23,    24,    25,    26,    27,
      44,    76,    45,    17,    38,    43,    38,    15,    75,    39,
      69,    71,    71,    71,    71,    71,    71,    74,    71,    50,
      51,    52,    74,    75,    64,    65,    71,    70,    43,    41,
      38,    44,    39,    42,    43,    17,    63,    39,    42,    16,
      71,    64,     4,    53,    51,    75,    71,    65,    70,    39,
      39,    75,    66,    67,    44,    38,     5,    64,    40,    39,
       7,     8,    54,    55,    56,    57,    58,    59,    41,    54,
      62,     6,    74,    38,    50,    39,    10,    60,    75,     5,
      67
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 70 "proj.y"
    {	pprintf("prog bloc\n");
																mainCode = (yyvsp[(1) - (1)].T);
																/*lancer la verif contextuelle */ 
															}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 74 "proj.y"
    { pprintf("prog class\n"); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 77 "proj.y"
    {
																pprintf("class\n");
																class_setName(current, (yyvsp[(2) - (11)].S)); /*param: nom de la classe */
																class_setConstructor(current, (yyvsp[(4) - (11)].P), (yyvsp[(7) - (11)].T)); 
																/*params: classe, paramètres constructeur, code du constructeur */
																/* superclasse gérée dans ExtendO */
																/* declarations gérées dans ListDeclO */
																classList_addClass(current);
															}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 88 "proj.y"
    { pprintf("class alloc\n"); current = NEW(1, Classs); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 90 "proj.y"
    { pprintf("listparamo null\n"); (yyval.P) = NULL; }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 91 "proj.y"
    { pprintf("listparamo non null\n"); (yyval.P) = (yyvsp[(1) - (1)].P); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 94 "proj.y"
    { pprintf("listparam final\n"); (yyval.P) = (yyvsp[(1) - (1)].P); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 95 "proj.y"
    {
																pprintf("listparam continue\n"); 
																ParamsListP tmp = (yyvsp[(1) - (3)].P);
																tmp->next = (yyvsp[(3) - (3)].P);
																(yyval.P)=tmp;
															}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 103 "proj.y"
    { pprintf("param\n"); (yyval.P) = function_makeParam((yyvsp[(1) - (3)].S), (yyvsp[(3) - (3)].S)); /*params: nomParam, typeParam */ }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 106 "proj.y"
    { pprintf("extendo null\n");}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 107 "proj.y"
    { pprintf("extendo non null\n"); class_setSuper(current, (yyvsp[(2) - (5)].S), (yyvsp[(4) - (5)].T)); /*params: classe, superType, arguments constructeur père */ }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 110 "proj.y"
    { pprintf("listdeclo null\n");}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 111 "proj.y"
    { pprintf("listdeclo non null\n");}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 114 "proj.y"
    { pprintf("decl field\n");}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 115 "proj.y"
    { pprintf("decl method\n");}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 118 "proj.y"
    { pprintf("declField\n"); class_addField(current, (yyvsp[(1) - (2)].I), (yyvsp[(2) - (2)].T)); /*params: classe, isStatic, arbre de decl de la var */ }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 121 "proj.y"
    { pprintf("statico null\n"); (yyval.I) = 0; }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 122 "proj.y"
    { pprintf("statico non null\n"); (yyval.I) = 1; }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 125 "proj.y"
    {
																pprintf("declmethod\n"); 
																class_addMethod(current, (yyvsp[(1) - (9)].I), (yyvsp[(3) - (9)].S), (yyvsp[(7) - (9)].S), (yyvsp[(5) - (9)].P), (yyvsp[(9) - (9)].T));
																/*params: classe, visibility, nom, type de retour,liste des paramètres, arbre du corps de la fonction */
															}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 132 "proj.y"
    { pprintf("ovorstat null\n"); (yyval.I) = 0; }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 133 "proj.y"
    { pprintf("ovorstat ovr\n"); (yyval.I) = 1; }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 134 "proj.y"
    { pprintf("ovorstat stat\n"); (yyval.I) = 2; }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 137 "proj.y"
    { pprintf("returno null\n"); (yyval.S) = NULL;}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 138 "proj.y"
    { pprintf("returno non null\n"); (yyval.S) = (yyvsp[(2) - (2)].S);}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 143 "proj.y"
    { pprintf("listdeclv final\n"); (yyval.T) = (yyvsp[(1) - (1)].T); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 144 "proj.y"
    { pprintf("listdeclv continue\n"); (yyval.T) = makeTree(DECL, 2, (yyvsp[(1) - (2)].T), (yyvsp[(2) - (2)].T)); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 147 "proj.y"
    {	pprintf("declv\n");
																(yyval.T) = makeTree(VAR, 3, makeLeafStr(ID, (yyvsp[(2) - (5)].S)), makeLeafStr(IDCL, (yyvsp[(4) - (5)].S)), (yyvsp[(5) - (5)].T));
																/* voir a pas ajouter un autre type "variable" aux feuilles de l'arbre */
															}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 153 "proj.y"
    { pprintf("affect null\n"); (yyval.T) = NULL; }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 154 "proj.y"
    { pprintf("affect non null\n"); (yyval.T) = (yyvsp[(2) - (3)].T); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 157 "proj.y"
    { pprintf("listargo null\n"); (yyval.T) = NULL; }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 158 "proj.y"
    { pprintf("listargo non null\n"); (yyval.T) = (yyvsp[(1) - (1)].T); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 161 "proj.y"
    { pprintf("list arg final\n"); (yyval.T) = (yyvsp[(1) - (1)].T); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 162 "proj.y"
    { pprintf("list arg continue\n"); (yyval.T) = makeTree(LSTARG, 2, (yyvsp[(1) - (3)].T), (yyvsp[(3) - (3)].T)); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 165 "proj.y"
    { pprintf("bloco null\n"); (yyval.T) = NULL; }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 166 "proj.y"
    { pprintf("bloco non null\n"); (yyval.T) = (yyvsp[(1) - (1)].T); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 169 "proj.y"
    { pprintf("bloc final\n"); (yyval.T) = (yyvsp[(2) - (3)].T); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 170 "proj.y"
    { pprintf("bloc continue\n"); (yyval.T) = makeTree(BLCDECL, 2, (yyvsp[(2) - (5)].T), (yyvsp[(4) - (5)].T)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 173 "proj.y"
    { pprintf("listinstO null\n"); (yyval.T) = NULL; }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 174 "proj.y"
    { pprintf("listinstO non null\n"); (yyval.T) = (yyvsp[(1) - (1)].T); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 177 "proj.y"
    { pprintf("listinst final\n"); (yyval.T) = (yyvsp[(1) - (1)].T); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 178 "proj.y"
    { pprintf("listinst continue\n"); (yyval.T) = makeTree(LSTINST, 2,  (yyvsp[(1) - (2)].T), (yyvsp[(2) - (2)].T)); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 181 "proj.y"
    { pprintf("inst1\n"); (yyval.T) = (yyvsp[(1) - (2)].T); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 182 "proj.y"
    { pprintf("inst2\n"); (yyval.T) = (yyvsp[(1) - (1)].T); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 183 "proj.y"
    { pprintf("inst3\n"); (yyval.T) = makeLeafInt(RET, 0); /* 0 a defaut de savoir quoi mettre*/ }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 184 "proj.y"
    { pprintf("inst4\n"); (yyval.T) = makeTree(AFF, 2, (yyvsp[(1) - (4)].T), (yyvsp[(3) - (4)].T)); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 185 "proj.y"
    { pprintf("inst5\n"); (yyval.T) = makeTree(IF, 3, (yyvsp[(2) - (6)].T), (yyvsp[(4) - (6)].T), (yyvsp[(6) - (6)].T)); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 188 "proj.y"
    { pprintf("exp1\n"); (yyval.T) = makeTree((yyvsp[(2) - (3)].I), 2, (yyvsp[(1) - (3)].T), (yyvsp[(3) - (3)].T)); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 189 "proj.y"
    { pprintf("exp2\n"); (yyval.T) = makeTree(CONCAT, 2, (yyvsp[(1) - (3)].T), (yyvsp[(3) - (3)].T)); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 190 "proj.y"
    { pprintf("exp3\n"); (yyval.T) = makeTree(ADD, 2, (yyvsp[(1) - (3)].T), (yyvsp[(3) - (3)].T)); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 191 "proj.y"
    { pprintf("exp4\n"); (yyval.T) = makeTree(SUB, 2, (yyvsp[(1) - (3)].T), (yyvsp[(3) - (3)].T)); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 192 "proj.y"
    { pprintf("exp5\n"); (yyval.T) = makeTree(MUL, 2, (yyvsp[(1) - (3)].T), (yyvsp[(3) - (3)].T)); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 193 "proj.y"
    { pprintf("exp6\n"); (yyval.T) = makeTree(DIV, 2, (yyvsp[(1) - (3)].T), (yyvsp[(3) - (3)].T)); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 194 "proj.y"
    { pprintf("exp7\n"); (yyval.T) = makeTree(UNARYADD, 1, (yyvsp[(2) - (2)].T)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 195 "proj.y"
    { pprintf("exp8\n"); (yyval.T) = makeTree(UNARYSUB, 1, (yyvsp[(2) - (2)].T)); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 196 "proj.y"
    { pprintf("exp9\n"); (yyval.T) = (yyvsp[(1) - (1)].T); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 199 "proj.y"
    { pprintf("exp21\n"); (yyval.T) = (yyvsp[(2) - (3)].T); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 200 "proj.y"
    { pprintf("exp22\n"); (yyval.T) = makeTree(CAST, 2, makeLeafStr(IDCL, (yyvsp[(3) - (6)].S)), (yyvsp[(5) - (6)].T)); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 201 "proj.y"
    { pprintf("exp23\n"); (yyval.T) = makeTree(INST, 2, makeLeafStr(IDCL, (yyvsp[(2) - (5)].S)), (yyvsp[(4) - (5)].T)); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 202 "proj.y"
    { pprintf("exp24\n"); (yyval.T) = makeTree(MSGSNT, 3, (yyvsp[(1) - (6)].T), makeLeafStr(ID, (yyvsp[(3) - (6)].S)), (yyvsp[(5) - (6)].T)); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 203 "proj.y"
    { pprintf("exp25\n"); (yyval.T) = (yyvsp[(1) - (1)].T); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 204 "proj.y"
    { pprintf("exp26\n"); (yyval.T) = makeLeafInt(CST, yyval.I); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 205 "proj.y"
    { pprintf("exp27\n"); (yyval.T) = makeLeafStr(STR, yyval.S); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 208 "proj.y"
    { pprintf("left affect\n"); (yyval.T) = makeTree(LAFFECT, 2, (yyvsp[(1) - (3)].T), makeLeafStr(ID, (yyvsp[(3) - (3)].S))); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 209 "proj.y"
    { pprintf("left affect2\n"); (yyval.T) = makeLeafStr(ID, (yyvsp[(1) - (1)].S)); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 212 "proj.y"
    { pprintfs("id", yyval.S); (yyval.S) = yyval.S; }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 215 "proj.y"
    { pprintfs("idcl", yyval.S); (yyval.S) = yyval.S; }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 218 "proj.y"
    { pprintfi("relop", yyval.I); (yyval.I) = yyval.I; }
    break;



/* Line 1806 of yacc.c  */
#line 2077 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}




#define FOR 257
#define INT 258
#define VOID 259
#define RETURN 260
#define CONST 261
#define ADD_ASSIGN 262
#define INC 263
#define STRING 264
#define NAME 265
#define NUMBER 266
#define SEPARATE 267
#define UMINUS 268
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	int intv;
	char *strv;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

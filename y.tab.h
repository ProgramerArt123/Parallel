#define FOR 257
#define INT 258
#define VOID 259
#define RETURN 260
#define ADD_ASSIGN 261
#define INC 262
#define STRING 263
#define NAME 264
#define NUMBER 265
#define SEPARATE 266
#define UMINUS 267
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

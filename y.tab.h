#define FOR 257
#define INT 258
#define VOID 259
#define RETURN 260
#define ADD_ASSIGN 261
#define STRING 262
#define NAME 263
#define NUMBER 264
#define SEPARATE 265
#define UMINUS 266
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

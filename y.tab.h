#define FOR 257
#define INT 258
#define VOID 259
#define RETURN 260
#define STRING 261
#define NAME 262
#define NUMBER 263
#define SEPARATE 264
#define UMINUS 265
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

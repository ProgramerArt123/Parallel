#define FOR 257
#define INT 258
#define RETURN 259
#define STRING 260
#define NAME 261
#define NUMBER 262
#define SEPARATE 263
#define UMINUS 264
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

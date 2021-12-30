#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20130304

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "Parallel.y"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
void PushStatement();
void PushReturn();
void PushAssignmentStatement(const char *variable);
void DecalreVariable(const char *variable, bool isConst);
void PushAddAssign(const char *variable);
void PushAdd();
void PushSub();
void PushMul();
void PushDiv();
void PushMod();
void PushInc(const char *variable, bool isBack);
void PushBlock();
void PushString(const char *itera);
void PushNumber(int number);
void PushVariable(const char *name);
void AddArgment(uint64_t argment);
void PushLoopEnter();
void PushLoopExit();
void PushProcDefEnter(const char *name, bool isConst);
void PushProcDefExit();
void AddParam(const char *param, bool isConst);
void PushProcCallEnter(const char *name);
void PushProcCallExit();
void PushType(const char *type);

#line 32 "Parallel.y"
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
#line 60 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

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
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    2,    2,    2,    2,    2,    2,    2,    2,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    3,    7,   11,    8,    9,
   10,    4,   12,   12,   14,   15,   16,   13,   13,   13,
   13,   13,   13,   13,    6,   17,   19,   18,   18,   18,
    5,    5,
};
static const short yylen[] = {                            2,
    2,    3,    1,    1,    2,    5,    5,    4,    2,    1,
    3,    3,    3,    3,    3,    3,    3,    2,    2,    2,
    3,    1,    1,    1,    1,    5,    2,    2,    1,    1,
    1,    6,    4,    3,    1,    1,    1,    3,    3,    2,
    5,    5,    4,    0,    3,    2,    1,    1,    3,    0,
    1,    1,
};
static const short yydefred[] = {                         0,
    0,   51,   52,    0,    0,    0,   22,    0,   23,    0,
    0,    0,    0,    0,    3,    4,    0,   24,    0,    0,
    0,    0,   28,    0,    0,   18,    0,   19,    0,   46,
   20,    0,    0,    0,    0,    0,    0,    0,    1,    0,
    0,   29,    0,   27,    0,    0,    0,   48,    0,    0,
    0,    0,   21,    2,    0,    0,   15,   16,   17,    0,
    0,   34,   30,    0,    0,    0,   40,    0,   35,    0,
    0,   47,   45,    0,   33,    0,    0,    0,   38,   39,
    0,    0,   36,    0,   49,    0,    0,   31,   26,    0,
    0,   43,    0,   41,   42,   37,   32,
};
static const short yydgoto[] = {                         12,
   13,   14,   15,   16,   17,   18,   19,   43,   64,   89,
   20,   21,   47,   70,   84,   97,   22,   49,   73,
};
static const short yysindex[] = {                       -16,
  -31,    0,    0,  -12, -233, -244,    0,   13,    0,  -12,
  -12,  -16,   66, -240,    0,    0, -250,    0,  -18, -211,
 -207,  -16,    0,   66, -208,    0,  -12,    0,  -12,    0,
    0,   59, -206,  -12,  -12,  -12,  -12,  -12,    0, -200,
    9,    0,  -64,    0, -233, -249,  -21,    0,  -10,   10,
   66,   66,    0,    0,   21,   21,    0,    0,    0,   17,
  -12,    0,    0,  -16, -185, -184,    0, -186,    0,  -44,
  -16,    0,    0,  -12,    0,  -12,   66,  -38,    0,    0,
 -233, -243,    0,  -16,    0,   66,   66,    0,    0, -183,
 -179,    0,  -26,    0,    0,    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,  -37,    0,    0,
    0,    0,   -5,    0,    0,    0,    0,    0,    0,    0,
   -3,   -1,    0,    1,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    2,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    3,    4,    0,    0,  -11,   -6,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    5,    0,    0,    0,
    0,    0,    0,    0,    0,    6,    7,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,
};
static const short yygindex[] = {                        -8,
   56,   -9,    0,    0,   -4,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 276
static const short yytable[] = {                         25,
   25,   11,   33,   25,   25,   25,   10,   25,   23,   25,
   40,   66,   48,   11,   41,   67,   46,   91,   10,   69,
   26,   92,   42,   11,    2,    3,   39,   11,   10,   14,
   72,   14,   10,   14,   13,   10,   13,   44,   13,   50,
   65,    5,    9,   12,   11,    8,    6,    7,   62,   75,
    2,    3,   30,   45,   44,   78,   50,   38,   63,   24,
   54,   85,   36,   82,   60,   31,   32,   37,   33,   61,
   74,    2,    3,   29,   81,   93,   90,   76,   83,   79,
   80,   94,   51,   33,   52,   95,   88,    0,    0,   55,
   56,   57,   58,   59,    0,   38,    0,    0,   96,   53,
   36,   35,   38,   34,    0,   37,    0,   36,   35,    0,
   34,    0,   37,    0,    0,    0,   77,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   86,
    0,   87,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    1,    2,
    3,    4,    5,    0,    6,    7,    8,    9,    0,   25,
    1,    2,    3,    4,    5,    0,    6,    7,    8,    9,
    1,    2,    3,    4,    5,   68,    6,    7,    8,    9,
    6,    7,    8,    9,    0,   14,   71,    0,    0,    0,
   13,   10,    0,   44,    0,   50,    0,    5,    9,   12,
   11,    8,    6,    7,   27,   28,
};
static const short yycheck[] = {                         37,
    5,   40,   12,   41,   42,   43,   45,   45,   40,   47,
  261,  261,   22,   40,  265,  265,   21,  261,   45,   41,
  265,  265,   41,   40,  258,  259,  267,   40,   45,   41,
   41,   43,   45,   45,   41,   41,   43,   41,   45,   41,
   45,   41,   41,   41,   41,   41,   41,   41,   40,   40,
  258,  259,   40,  261,  266,   64,  265,   37,  123,    4,
  267,   71,   42,   68,  265,   10,   11,   47,   78,   61,
   61,  258,  259,   61,  261,   84,   81,   61,  123,  265,
  265,  265,   27,   93,   29,  265,  125,   -1,   -1,   34,
   35,   36,   37,   38,   -1,   37,   -1,   -1,  125,   41,
   42,   43,   37,   45,   -1,   47,   -1,   42,   43,   -1,
   45,   -1,   47,   -1,   -1,   -1,   61,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   74,
   -1,   76,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,
  259,  260,  261,   -1,  263,  264,  265,  266,   -1,  267,
  257,  258,  259,  260,  261,   -1,  263,  264,  265,  266,
  257,  258,  259,  260,  261,  267,  263,  264,  265,  266,
  263,  264,  265,  266,   -1,  267,  267,   -1,   -1,   -1,
  267,  267,   -1,  267,   -1,  267,   -1,  267,  267,  267,
  267,  267,  267,  267,  262,  263,
};
#define YYFINAL 12
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 268
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'%'",0,0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,0,
0,"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"FOR","INT","VOID","RETURN","CONST","ADD_ASSIGN","INC","STRING","NAME",
"NUMBER","SEPARATE","UMINUS",
};
static const char *yyrule[] = {
"$accept : statements",
"statements : statement SEPARATE",
"statements : statements statement SEPARATE",
"statement : loop",
"statement : proc_def",
"statement : RETURN expression",
"statement : CONST type NAME '=' expression",
"statement : type CONST NAME '=' expression",
"statement : type NAME '=' expression",
"statement : type NAME",
"statement : expression",
"expression : NAME '=' expression",
"expression : NAME ADD_ASSIGN expression",
"expression : expression '+' expression",
"expression : expression '-' expression",
"expression : expression '*' expression",
"expression : expression '/' expression",
"expression : expression '%' expression",
"expression : INC NAME",
"expression : NAME INC",
"expression : '-' expression",
"expression : '(' expression ')'",
"expression : STRING",
"expression : NUMBER",
"expression : proc_call",
"expression : NAME",
"loop : loop_head loop_block_exit loop_scope_enter statements loop_scope_exit",
"loop_head : loop_block_enter NUMBER",
"loop_block_enter : FOR '('",
"loop_block_exit : ')'",
"loop_scope_enter : '{'",
"loop_scope_exit : '}'",
"proc_def : proc_def_block_enter parameters proc_def_block_exit proc_def_scope_enter statements proc_def_scope_exit",
"proc_def_block_enter : CONST type NAME '('",
"proc_def_block_enter : type NAME '('",
"proc_def_block_exit : ')'",
"proc_def_scope_enter : '{'",
"proc_def_scope_exit : '}'",
"parameters : CONST type NAME",
"parameters : type CONST NAME",
"parameters : type NAME",
"parameters : parameters SEPARATE CONST type NAME",
"parameters : parameters SEPARATE type CONST NAME",
"parameters : parameters SEPARATE type NAME",
"parameters :",
"proc_call : proc_call_block_enter arguments proc_call_block_exit",
"proc_call_block_enter : NAME '('",
"proc_call_block_exit : ')'",
"arguments : statement",
"arguments : arguments SEPARATE statement",
"arguments :",
"type : INT",
"type : VOID",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 3:
#line 61 "Parallel.y"
	{ PushStatement();}
break;
case 4:
#line 62 "Parallel.y"
	{ PushStatement();}
break;
case 5:
#line 63 "Parallel.y"
	{ PushReturn();}
break;
case 6:
#line 64 "Parallel.y"
	{ DecalreVariable(yystack.l_mark[-2].strv, true);PushAssignmentStatement(yystack.l_mark[-2].strv); PushStatement();}
break;
case 7:
#line 65 "Parallel.y"
	{ DecalreVariable(yystack.l_mark[-2].strv, true);PushAssignmentStatement(yystack.l_mark[-2].strv); PushStatement();}
break;
case 8:
#line 66 "Parallel.y"
	{ DecalreVariable(yystack.l_mark[-2].strv, false);PushAssignmentStatement(yystack.l_mark[-2].strv); PushStatement();}
break;
case 9:
#line 67 "Parallel.y"
	{ DecalreVariable(yystack.l_mark[0].strv, false);}
break;
case 10:
#line 68 "Parallel.y"
	{ PushStatement();}
break;
case 11:
#line 71 "Parallel.y"
	{ PushAssignmentStatement(yystack.l_mark[-2].strv);}
break;
case 12:
#line 72 "Parallel.y"
	{ PushAddAssign(yystack.l_mark[-2].strv);}
break;
case 13:
#line 73 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv + yystack.l_mark[0].intv; PushAdd();}
break;
case 14:
#line 74 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv - yystack.l_mark[0].intv; PushSub();}
break;
case 15:
#line 75 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv * yystack.l_mark[0].intv; PushMul();}
break;
case 16:
#line 76 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv / yystack.l_mark[0].intv; PushDiv();}
break;
case 17:
#line 77 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv % yystack.l_mark[0].intv; PushMod();}
break;
case 18:
#line 78 "Parallel.y"
	{ PushInc(yystack.l_mark[0].strv, false);}
break;
case 19:
#line 79 "Parallel.y"
	{ PushInc(yystack.l_mark[-1].strv, true);}
break;
case 20:
#line 80 "Parallel.y"
	{ yyval.intv = -yystack.l_mark[0].intv; printf("---%d\n", yyval.intv);}
break;
case 21:
#line 81 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-1].intv; PushBlock();}
break;
case 22:
#line 82 "Parallel.y"
	{ PushString(yystack.l_mark[0].strv);}
break;
case 23:
#line 83 "Parallel.y"
	{ PushNumber(yystack.l_mark[0].intv);}
break;
case 24:
#line 84 "Parallel.y"
	{ }
break;
case 25:
#line 85 "Parallel.y"
	{ PushVariable(yystack.l_mark[0].strv);}
break;
case 27:
#line 92 "Parallel.y"
	{AddArgment(yystack.l_mark[0].intv);}
break;
case 28:
#line 95 "Parallel.y"
	{ PushLoopEnter(); }
break;
case 31:
#line 104 "Parallel.y"
	{ PushLoopExit(); }
break;
case 33:
#line 110 "Parallel.y"
	{ PushProcDefEnter(yystack.l_mark[-1].strv, true); }
break;
case 34:
#line 111 "Parallel.y"
	{ PushProcDefEnter(yystack.l_mark[-1].strv, false); }
break;
case 37:
#line 120 "Parallel.y"
	{ PushProcDefExit(); }
break;
case 38:
#line 123 "Parallel.y"
	{ AddParam(yystack.l_mark[0].strv, true); }
break;
case 39:
#line 124 "Parallel.y"
	{ AddParam(yystack.l_mark[0].strv, true); }
break;
case 40:
#line 125 "Parallel.y"
	{ AddParam(yystack.l_mark[0].strv, false); }
break;
case 41:
#line 126 "Parallel.y"
	{ AddParam(yystack.l_mark[0].strv, true); }
break;
case 42:
#line 127 "Parallel.y"
	{ AddParam(yystack.l_mark[0].strv, true); }
break;
case 43:
#line 128 "Parallel.y"
	{ AddParam(yystack.l_mark[0].strv, false); }
break;
case 46:
#line 135 "Parallel.y"
	{ printf("NAME=%s\n", yystack.l_mark[-1].strv); PushProcCallEnter(yystack.l_mark[-1].strv); }
break;
case 47:
#line 138 "Parallel.y"
	{ PushProcCallExit();  }
break;
case 51:
#line 146 "Parallel.y"
	{ PushType("int");}
break;
case 52:
#line 147 "Parallel.y"
	{ PushType("void");}
break;
#line 697 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}

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
void DecalreVariable(const char *variable);
void PushAddAssign(const char *variable);
void PushAdd();
void PushSub();
void PushMul();
void PushDiv();
void PushMod();
void PushInc(const char *variable, bool isRight);
void PushBlock();
void PushString(const char *itera);
void PushNumber(int number);
void PushVariable(const char *name);
void AddArgment(uint64_t argment);
void PushLoopEnter();
void PushLoopExit();
void PushProcDefEnter(const char *name);
void PushProcDefExit();
void AddParam(const char *param);
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
#define ADD_ASSIGN 261
#define INC 262
#define STRING 263
#define NAME 264
#define NUMBER 265
#define SEPARATE 266
#define UMINUS 267
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    2,    2,    2,    2,    2,    2,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    3,    7,   11,    8,    9,   10,    4,
   12,   14,   15,   16,   13,   13,   13,    6,   17,   19,
   18,   18,   18,    5,    5,
};
static const short yylen[] = {                            2,
    2,    3,    1,    1,    2,    4,    2,    1,    3,    3,
    3,    3,    3,    3,    3,    2,    2,    2,    3,    1,
    1,    1,    1,    5,    2,    2,    1,    1,    1,    6,
    3,    1,    1,    1,    2,    4,    0,    3,    2,    1,
    1,    3,    0,    1,    1,
};
static const short yydefred[] = {                         0,
    0,   44,   45,    0,    0,   20,    0,   21,    0,    0,
    0,    0,    0,    3,    4,    0,   22,    0,    0,    0,
    0,   26,    0,   16,    0,   17,    0,   39,   18,    0,
    0,    0,    0,    0,    0,    0,    1,    0,   27,    0,
   25,    0,    0,   41,    0,    0,    0,   19,    2,    0,
    0,   13,   14,   15,    0,   31,   28,    0,   35,    0,
   32,    0,    0,   40,   38,    0,    0,    0,   33,    0,
   42,   29,   24,   36,    0,   34,   30,
};
static const short yydgoto[] = {                         11,
   12,   13,   14,   15,   16,   17,   18,   40,   58,   73,
   19,   20,   43,   62,   70,   77,   21,   45,   65,
};
static const short yysindex[] = {                       -18,
  -28,    0,    0,  -14, -245,    0,    9,    0,  -14,  -14,
  -18,   52, -243,    0,    0, -240,    0,  -16, -244, -242,
  -18,    0,   52,    0,  -14,    0,  -14,    0,    0,   43,
 -220,  -14,  -14,  -14,  -14,  -14,    0,  -20,    0,  -76,
    0, -216,  -32,    0,  -12,   52,   52,    0,    0,   22,
   22,    0,    0,    0,  -14,    0,    0,  -18,    0, -242,
    0,  -71,  -18,    0,    0,   52,  -38, -209,    0,  -18,
    0,    0,    0,    0,  -27,    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,  -37,    0,    0,    0,
    0,   -7,    0,    0,    0,    0,    0,    0,    0,   -5,
   -3,    0,   -2,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   -1,    0,    0,
    0,    0,    0,    0,    0,    1,    2,    0,    0,  -13,
   -8,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    3,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,
};
static const short yygindex[] = {                       -55,
   41,  -10,    0,    0,   -6,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 271
static const short yytable[] = {                         23,
   31,   10,   67,   23,   23,   23,    9,   23,   61,   23,
   44,   22,   10,   42,   75,    2,    3,    9,   24,   56,
   41,   10,   37,   38,   39,   10,    9,   12,   64,   12,
    9,   12,   11,    8,   11,   37,   11,   43,    5,    7,
   55,   10,    9,    6,   23,   49,   57,   59,   28,   29,
   30,   69,   71,   68,   74,    0,   31,    0,   36,    0,
    0,    0,    0,   34,   31,   46,    0,   47,   35,   27,
    0,    0,   50,   51,   52,   53,   54,    0,    0,   36,
    0,    0,    0,   48,   34,   33,   72,   32,   36,   35,
    0,    0,    0,   34,   33,   66,   32,   76,   35,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    1,    2,
    3,    4,    0,    5,    6,    7,    8,    0,   23,    1,
    2,    3,    4,   60,    5,    6,    7,    8,    1,    2,
    3,    4,    0,    5,    6,    7,    8,    5,    6,    7,
    8,    0,   12,   63,    0,    0,    0,   11,    8,    0,
   37,    0,   43,    5,    7,    0,   10,    9,    6,   25,
   26,
};
static const short yycheck[] = {                         37,
   11,   40,   58,   41,   42,   43,   45,   45,   41,   47,
   21,   40,   40,   20,   70,  258,  259,   45,  264,   40,
  265,   40,  266,  264,   41,   40,   45,   41,   41,   43,
   45,   45,   41,   41,   43,   41,   45,   41,   41,   41,
   61,   41,   41,   41,    4,  266,  123,  264,   40,    9,
   10,  123,   63,   60,  264,   -1,   67,   -1,   37,   -1,
   -1,   -1,   -1,   42,   75,   25,   -1,   27,   47,   61,
   -1,   -1,   32,   33,   34,   35,   36,   -1,   -1,   37,
   -1,   -1,   -1,   41,   42,   43,  125,   45,   37,   47,
   -1,   -1,   -1,   42,   43,   55,   45,  125,   47,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,
  259,  260,   -1,  262,  263,  264,  265,   -1,  266,  257,
  258,  259,  260,  266,  262,  263,  264,  265,  257,  258,
  259,  260,   -1,  262,  263,  264,  265,  262,  263,  264,
  265,   -1,  266,  266,   -1,   -1,   -1,  266,  266,   -1,
  266,   -1,  266,  266,  266,   -1,  266,  266,  266,  261,
  262,
};
#define YYFINAL 11
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 267
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'%'",0,0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,0,
0,"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"FOR","INT","VOID","RETURN","ADD_ASSIGN","INC","STRING","NAME","NUMBER",
"SEPARATE","UMINUS",
};
static const char *yyrule[] = {
"$accept : statements",
"statements : statement SEPARATE",
"statements : statements statement SEPARATE",
"statement : loop",
"statement : proc_def",
"statement : RETURN expression",
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
"proc_def_block_enter : type NAME '('",
"proc_def_block_exit : ')'",
"proc_def_scope_enter : '{'",
"proc_def_scope_exit : '}'",
"parameters : type NAME",
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
#line 60 "Parallel.y"
	{ PushStatement();}
break;
case 4:
#line 61 "Parallel.y"
	{ PushStatement();}
break;
case 5:
#line 62 "Parallel.y"
	{ PushReturn();}
break;
case 6:
#line 63 "Parallel.y"
	{ DecalreVariable(yystack.l_mark[-2].strv);PushAssignmentStatement(yystack.l_mark[-2].strv); PushStatement();}
break;
case 7:
#line 64 "Parallel.y"
	{ DecalreVariable(yystack.l_mark[0].strv);}
break;
case 8:
#line 65 "Parallel.y"
	{ PushStatement();}
break;
case 9:
#line 68 "Parallel.y"
	{ PushAssignmentStatement(yystack.l_mark[-2].strv);}
break;
case 10:
#line 69 "Parallel.y"
	{ PushAddAssign(yystack.l_mark[-2].strv);}
break;
case 11:
#line 70 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv + yystack.l_mark[0].intv; PushAdd();}
break;
case 12:
#line 71 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv - yystack.l_mark[0].intv; PushSub();}
break;
case 13:
#line 72 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv * yystack.l_mark[0].intv; PushMul();}
break;
case 14:
#line 73 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv / yystack.l_mark[0].intv; PushDiv();}
break;
case 15:
#line 74 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv % yystack.l_mark[0].intv; PushMod();}
break;
case 16:
#line 75 "Parallel.y"
	{ PushInc(yystack.l_mark[-1].strv, false);}
break;
case 17:
#line 76 "Parallel.y"
	{ PushInc(yystack.l_mark[-1].strv, true);}
break;
case 18:
#line 77 "Parallel.y"
	{ yyval.intv = -yystack.l_mark[0].intv; printf("---%d\n", yyval.intv);}
break;
case 19:
#line 78 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-1].intv; PushBlock();}
break;
case 20:
#line 79 "Parallel.y"
	{ PushString(yystack.l_mark[0].strv);}
break;
case 21:
#line 80 "Parallel.y"
	{ PushNumber(yystack.l_mark[0].intv);}
break;
case 22:
#line 81 "Parallel.y"
	{ }
break;
case 23:
#line 82 "Parallel.y"
	{ PushVariable(yystack.l_mark[0].strv);}
break;
case 25:
#line 89 "Parallel.y"
	{AddArgment(yystack.l_mark[0].intv);}
break;
case 26:
#line 92 "Parallel.y"
	{ PushLoopEnter(); }
break;
case 29:
#line 101 "Parallel.y"
	{ PushLoopExit(); }
break;
case 31:
#line 107 "Parallel.y"
	{ PushProcDefEnter(yystack.l_mark[-1].strv); }
break;
case 34:
#line 116 "Parallel.y"
	{ PushProcDefExit(); }
break;
case 35:
#line 119 "Parallel.y"
	{ AddParam(yystack.l_mark[0].strv); }
break;
case 36:
#line 120 "Parallel.y"
	{ AddParam(yystack.l_mark[0].strv); }
break;
case 39:
#line 127 "Parallel.y"
	{ printf("NAME=%s\n", yystack.l_mark[-1].strv); PushProcCallEnter(yystack.l_mark[-1].strv); }
break;
case 40:
#line 130 "Parallel.y"
	{ PushProcCallExit();  }
break;
case 44:
#line 138 "Parallel.y"
	{ PushType("int");}
break;
case 45:
#line 139 "Parallel.y"
	{ PushType("void");}
break;
#line 653 "y.tab.c"
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

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
void PushAdd();
void PushSub();
void PushMul();
void PushDiv();
void PushMod();
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
#line 29 "Parallel.y"
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
#line 57 "y.tab.c"

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
#define STRING 261
#define NAME 262
#define NUMBER 263
#define SEPARATE 264
#define UMINUS 265
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    2,    2,    2,    2,    2,    2,    2,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    3,    7,   11,    8,    9,   10,    4,   12,   14,   15,
   16,   13,   13,   13,    6,   17,   19,   18,   18,   18,
    5,    5,
};
static const short yylen[] = {                            2,
    2,    3,    1,    1,    2,    4,    3,    2,    1,    3,
    3,    3,    3,    3,    2,    3,    1,    1,    1,    1,
    5,    2,    2,    1,    1,    1,    6,    3,    1,    1,
    1,    2,    4,    0,    3,    2,    1,    1,    3,    0,
    1,    1,
};
static const short yydefred[] = {                         0,
    0,   41,   42,    0,   17,    0,   18,    0,    0,    0,
    0,    0,    3,    4,    0,   19,    0,    0,    0,    0,
   23,    0,    0,    0,   36,   15,    0,    0,    0,    0,
    0,    0,    0,    1,    0,   24,    0,   22,    0,    0,
   38,    0,    0,   16,    2,    0,    0,   12,   13,   14,
    0,   28,   25,    0,   32,    0,   29,    0,    0,   37,
   35,    0,    0,    0,   30,    0,   39,   26,   21,   33,
    0,   31,   27,
};
static const short yydgoto[] = {                         10,
   11,   12,   13,   14,   15,   16,   17,   37,   54,   69,
   18,   19,   40,   58,   66,   73,   20,   42,   61,
};
static const short yysindex[] = {                       -22,
  -26,    0,    0,  -19,    0,  -39,    0,  -19,  -19,  -22,
   22, -247,    0,    0, -222,    0,    3, -218, -246,  -22,
    0,    7,   22,  -19,    0,    0,   39, -223,  -19,  -19,
  -19,  -19,  -19,    0,    2,    0,  -74,    0, -210,  -17,
    0,  -10,   22,    0,    0,    6,    6,    0,    0,    0,
  -19,    0,    0,  -22,    0, -246,    0,  -69,  -22,    0,
    0,   22,  -38, -207,    0,  -22,    0,    0,    0,    0,
  -29,    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,  -37,    0,    0,    0,    0,
   -8,    0,    0,    0,    0,    0,    0,    0,   -7,   -6,
    0,  -37,   -5,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   -4,    0,    0,    0,    0,    0,
    0,    0,   -3,    0,    0,  -16,  -13,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   -2,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,
};
static const short yygindex[] = {                       -51,
   42,   -1,    0,    0,    1,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 262
static const short yytable[] = {                         20,
   25,    9,   63,   20,   20,   20,    8,   20,   28,   20,
    9,    2,    3,   21,   71,    8,   34,    9,   41,   39,
    9,   24,    8,   57,   11,    8,   11,   10,   11,   10,
   60,   10,    9,   34,   40,    5,    8,    7,    6,   35,
   45,   52,   33,   36,   38,   23,   25,   31,   53,   26,
   27,   55,   32,   65,   70,    0,   64,   67,   33,    0,
    0,   28,   51,   31,   30,   43,   29,    0,   32,   28,
   46,   47,   48,   49,   50,   33,    0,    0,    0,   44,
   31,   30,    0,   29,    0,   32,   68,    0,    0,    0,
    0,    0,   62,    0,    0,   72,    0,    0,    0,    0,
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
    3,    4,    5,    6,    7,    0,   20,    1,    2,    3,
    4,    5,    6,    7,    1,    2,    3,    4,    5,    6,
    7,    5,   22,    7,    0,    0,   56,   11,    0,    0,
   10,    0,    0,   59,    0,    9,   34,   40,    5,    8,
    7,    6,
};
static const short yycheck[] = {                         37,
   40,   40,   54,   41,   42,   43,   45,   45,   10,   47,
   40,  258,  259,   40,   66,   45,  264,   40,   20,   19,
   40,   61,   45,   41,   41,   45,   43,   41,   45,   43,
   41,   45,   41,   41,   41,   41,   41,   41,   41,  262,
  264,   40,   37,   41,  263,    4,   40,   42,  123,    8,
    9,  262,   47,  123,  262,   -1,   56,   59,   37,   -1,
   -1,   63,   61,   42,   43,   24,   45,   -1,   47,   71,
   29,   30,   31,   32,   33,   37,   -1,   -1,   -1,   41,
   42,   43,   -1,   45,   -1,   47,  125,   -1,   -1,   -1,
   -1,   -1,   51,   -1,   -1,  125,   -1,   -1,   -1,   -1,
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
  259,  260,  261,  262,  263,   -1,  264,  257,  258,  259,
  260,  261,  262,  263,  257,  258,  259,  260,  261,  262,
  263,  261,  262,  263,   -1,   -1,  264,  264,   -1,   -1,
  264,   -1,   -1,  264,   -1,  264,  264,  264,  264,  264,
  264,  264,
};
#define YYFINAL 10
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 265
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'%'",0,0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,0,
0,"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"FOR","INT","VOID","RETURN","STRING","NAME","NUMBER","SEPARATE","UMINUS",
};
static const char *yyrule[] = {
"$accept : statements",
"statements : statement SEPARATE",
"statements : statements statement SEPARATE",
"statement : loop",
"statement : proc_def",
"statement : RETURN expression",
"statement : type NAME '=' expression",
"statement : NAME '=' expression",
"statement : type NAME",
"statement : expression",
"expression : expression '+' expression",
"expression : expression '-' expression",
"expression : expression '*' expression",
"expression : expression '/' expression",
"expression : expression '%' expression",
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
#line 52 "Parallel.y"
	{ PushStatement();}
break;
case 4:
#line 53 "Parallel.y"
	{ PushStatement();}
break;
case 5:
#line 54 "Parallel.y"
	{ PushReturn();}
break;
case 6:
#line 55 "Parallel.y"
	{ DecalreVariable(yystack.l_mark[-2].strv);PushAssignmentStatement(yystack.l_mark[-2].strv);}
break;
case 7:
#line 56 "Parallel.y"
	{ PushAssignmentStatement(yystack.l_mark[-2].strv);}
break;
case 8:
#line 57 "Parallel.y"
	{ DecalreVariable(yystack.l_mark[0].strv);}
break;
case 9:
#line 58 "Parallel.y"
	{ PushStatement();}
break;
case 10:
#line 61 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv + yystack.l_mark[0].intv; PushAdd();}
break;
case 11:
#line 62 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv - yystack.l_mark[0].intv; PushSub();}
break;
case 12:
#line 63 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv * yystack.l_mark[0].intv; PushMul();}
break;
case 13:
#line 64 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv / yystack.l_mark[0].intv; PushDiv();}
break;
case 14:
#line 65 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv % yystack.l_mark[0].intv; PushMod();}
break;
case 15:
#line 66 "Parallel.y"
	{ yyval.intv = -yystack.l_mark[0].intv; printf("---%d\n", yyval.intv);}
break;
case 16:
#line 67 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-1].intv; PushBlock();}
break;
case 17:
#line 68 "Parallel.y"
	{ PushString(yystack.l_mark[0].strv);}
break;
case 18:
#line 69 "Parallel.y"
	{ PushNumber(yystack.l_mark[0].intv);}
break;
case 19:
#line 70 "Parallel.y"
	{ }
break;
case 20:
#line 71 "Parallel.y"
	{ PushVariable(yystack.l_mark[0].strv);}
break;
case 22:
#line 78 "Parallel.y"
	{AddArgment(yystack.l_mark[0].intv);}
break;
case 23:
#line 81 "Parallel.y"
	{ PushLoopEnter(); }
break;
case 26:
#line 90 "Parallel.y"
	{ PushLoopExit(); }
break;
case 28:
#line 96 "Parallel.y"
	{ PushProcDefEnter(yystack.l_mark[-1].strv); }
break;
case 31:
#line 105 "Parallel.y"
	{ PushProcDefExit(); }
break;
case 32:
#line 108 "Parallel.y"
	{ AddParam(yystack.l_mark[0].strv); }
break;
case 33:
#line 109 "Parallel.y"
	{ AddParam(yystack.l_mark[0].strv); }
break;
case 36:
#line 116 "Parallel.y"
	{ printf("NAME=%s\n", yystack.l_mark[-1].strv); PushProcCallEnter(yystack.l_mark[-1].strv); }
break;
case 37:
#line 119 "Parallel.y"
	{ PushProcCallExit();  }
break;
case 41:
#line 127 "Parallel.y"
	{ PushType("int");}
break;
case 42:
#line 128 "Parallel.y"
	{ PushType("void");}
break;
#line 630 "y.tab.c"
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

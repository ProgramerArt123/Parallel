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
#line 30 "Parallel.y"
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
#line 58 "y.tab.c"

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
#define STRING 262
#define NAME 263
#define NUMBER 264
#define SEPARATE 265
#define UMINUS 266
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    2,    2,    2,    2,    2,    2,    2,    2,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    3,    7,   11,    8,    9,   10,    4,   12,   14,
   15,   16,   13,   13,   13,    6,   17,   19,   18,   18,
   18,    5,    5,
};
static const short yylen[] = {                            2,
    2,    3,    1,    1,    2,    4,    3,    3,    2,    1,
    3,    3,    3,    3,    3,    2,    3,    1,    1,    1,
    1,    5,    2,    2,    1,    1,    1,    6,    3,    1,
    1,    1,    2,    4,    0,    3,    2,    1,    1,    3,
    0,    1,    1,
};
static const short yydefred[] = {                         0,
    0,   42,   43,    0,   18,    0,   19,    0,    0,    0,
    0,    0,    3,    4,    0,   20,    0,    0,    0,    0,
   24,    0,    0,    0,    0,   37,   16,    0,    0,    0,
    0,    0,    0,    0,    1,    0,   25,    0,   23,    0,
    0,   39,    0,    0,    0,   17,    2,    0,    0,   13,
   14,   15,    0,   29,   26,    0,   33,    0,   30,    0,
    0,   38,   36,    0,    0,    0,   31,    0,   40,   27,
   22,   34,    0,   32,   28,
};
static const short yydgoto[] = {                         10,
   11,   12,   13,   14,   15,   16,   17,   38,   56,   71,
   18,   19,   41,   60,   68,   75,   20,   43,   63,
};
static const short yysindex[] = {                       -20,
  -24,    0,    0,  -17,    0,    3,    0,  -17,  -17,  -20,
   41, -243,    0,    0, -222,    0,    6, -220, -240,  -20,
    0,    5,   41,  -17,  -17,    0,    0,   11, -216,  -17,
  -17,  -17,  -17,  -17,    0,  -19,    0,  -68,    0, -206,
  -15,    0,  -11,   41,   41,    0,    0,   43,   43,    0,
    0,    0,  -17,    0,    0,  -20,    0, -240,    0,  -64,
  -20,    0,    0,   41,  -38, -203,    0,  -20,    0,    0,
    0,    0,  -28,    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,  -37,    0,    0,    0,    0,
   -9,    0,    0,    0,    0,    0,    0,    0,   -8,   -7,
    0,  -37,   -6,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   -5,    0,    0,    0,    0,
    0,    0,    0,   -4,   -3,    0,    0,  -32,  -14,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   -2,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
};
static const short yygindex[] = {                       -53,
   42,    4,    0,    0,  -18,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 264
static const short yytable[] = {                         21,
   40,    9,   65,   21,   21,   21,    8,   21,   12,   21,
   12,    9,   12,   29,   73,   21,    8,    2,    3,    9,
   54,   35,    9,   42,    8,   59,   11,    8,   11,   62,
   11,   10,   35,   41,    5,    9,    8,    7,    6,   66,
   36,   53,   26,   39,   26,   23,   37,   34,   47,   27,
   28,   46,   32,   31,   55,   30,   57,   33,   67,   72,
    0,    0,    0,   25,   69,   44,   45,    0,   29,    0,
    0,   48,   49,   50,   51,   52,   29,   34,    0,   34,
    0,    0,   32,   31,   32,   30,   70,   33,    0,   33,
    0,    0,    0,    0,   64,    0,   74,    0,    0,    0,
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
    3,    4,    0,    5,    6,    7,    0,   21,    1,    2,
    3,    4,   12,    5,    6,    7,    1,    2,    3,    4,
    0,    5,    6,    7,    5,   22,    7,    0,    0,   58,
   11,    0,    0,   61,    0,   10,   35,   41,    5,    9,
    8,    7,    6,   24,
};
static const short yycheck[] = {                         37,
   19,   40,   56,   41,   42,   43,   45,   45,   41,   47,
   43,   40,   45,   10,   68,   40,   45,  258,  259,   40,
   40,  265,   40,   20,   45,   41,   41,   45,   43,   41,
   45,   41,   41,   41,   41,   41,   41,   41,   41,   58,
  263,   61,   40,  264,   40,    4,   41,   37,  265,    8,
    9,   41,   42,   43,  123,   45,  263,   47,  123,  263,
   -1,   -1,   -1,   61,   61,   24,   25,   -1,   65,   -1,
   -1,   30,   31,   32,   33,   34,   73,   37,   -1,   37,
   -1,   -1,   42,   43,   42,   45,  125,   47,   -1,   47,
   -1,   -1,   -1,   -1,   53,   -1,  125,   -1,   -1,   -1,
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
  259,  260,   -1,  262,  263,  264,   -1,  265,  257,  258,
  259,  260,  265,  262,  263,  264,  257,  258,  259,  260,
   -1,  262,  263,  264,  262,  263,  264,   -1,   -1,  265,
  265,   -1,   -1,  265,   -1,  265,  265,  265,  265,  265,
  265,  265,  265,  261,
};
#define YYFINAL 10
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 266
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'%'",0,0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,0,
0,"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"FOR","INT","VOID","RETURN","ADD_ASSIGN","STRING","NAME","NUMBER",
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
"statement : NAME '=' expression",
"statement : NAME ADD_ASSIGN expression",
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
#line 55 "Parallel.y"
	{ PushStatement();}
break;
case 4:
#line 56 "Parallel.y"
	{ PushStatement();}
break;
case 5:
#line 57 "Parallel.y"
	{ PushReturn();}
break;
case 6:
#line 58 "Parallel.y"
	{ DecalreVariable(yystack.l_mark[-2].strv);PushAssignmentStatement(yystack.l_mark[-2].strv);}
break;
case 7:
#line 59 "Parallel.y"
	{ PushAssignmentStatement(yystack.l_mark[-2].strv);}
break;
case 8:
#line 60 "Parallel.y"
	{ PushAddAssign(yystack.l_mark[-2].strv);}
break;
case 9:
#line 61 "Parallel.y"
	{ DecalreVariable(yystack.l_mark[0].strv);}
break;
case 10:
#line 62 "Parallel.y"
	{ PushStatement();}
break;
case 11:
#line 65 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv + yystack.l_mark[0].intv; PushAdd();}
break;
case 12:
#line 66 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv - yystack.l_mark[0].intv; PushSub();}
break;
case 13:
#line 67 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv * yystack.l_mark[0].intv; PushMul();}
break;
case 14:
#line 68 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv / yystack.l_mark[0].intv; PushDiv();}
break;
case 15:
#line 69 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-2].intv % yystack.l_mark[0].intv; PushMod();}
break;
case 16:
#line 70 "Parallel.y"
	{ yyval.intv = -yystack.l_mark[0].intv; printf("---%d\n", yyval.intv);}
break;
case 17:
#line 71 "Parallel.y"
	{ yyval.intv = yystack.l_mark[-1].intv; PushBlock();}
break;
case 18:
#line 72 "Parallel.y"
	{ PushString(yystack.l_mark[0].strv);}
break;
case 19:
#line 73 "Parallel.y"
	{ PushNumber(yystack.l_mark[0].intv);}
break;
case 20:
#line 74 "Parallel.y"
	{ }
break;
case 21:
#line 75 "Parallel.y"
	{ PushVariable(yystack.l_mark[0].strv);}
break;
case 23:
#line 82 "Parallel.y"
	{AddArgment(yystack.l_mark[0].intv);}
break;
case 24:
#line 85 "Parallel.y"
	{ PushLoopEnter(); }
break;
case 27:
#line 94 "Parallel.y"
	{ PushLoopExit(); }
break;
case 29:
#line 100 "Parallel.y"
	{ PushProcDefEnter(yystack.l_mark[-1].strv); }
break;
case 32:
#line 109 "Parallel.y"
	{ PushProcDefExit(); }
break;
case 33:
#line 112 "Parallel.y"
	{ AddParam(yystack.l_mark[0].strv); }
break;
case 34:
#line 113 "Parallel.y"
	{ AddParam(yystack.l_mark[0].strv); }
break;
case 37:
#line 120 "Parallel.y"
	{ printf("NAME=%s\n", yystack.l_mark[-1].strv); PushProcCallEnter(yystack.l_mark[-1].strv); }
break;
case 38:
#line 123 "Parallel.y"
	{ PushProcCallExit();  }
break;
case 42:
#line 131 "Parallel.y"
	{ PushType("int");}
break;
case 43:
#line 132 "Parallel.y"
	{ PushType("void");}
break;
#line 638 "y.tab.c"
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

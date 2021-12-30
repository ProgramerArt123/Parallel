%{
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
void PushStatement();
void PushReturn();
void PushAssignmentStatement(const char *variable);
void PushInitStatement(const char *variable);
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

%}

%union {
	int intv;
	char *strv;
}
%token <strv> FOR
%token <strv> INT
%token <strv> VOID
%token <strv> RETURN
%token <strv> CONST
%token <strv> ADD_ASSIGN
%token <strv> INC
%token <strv> STRING
%token <strv> NAME
%token <intv> NUMBER
%token SEPARATE
%right '='
%right ADD_ASSIGN
%left '-' '+'
%left '*' '/' '%'
%nonassoc UMINUS
%nonassoc INC

%type <intv> expression

%%
statements:	statement SEPARATE
	|	statements statement SEPARATE
	;

statement:	loop			{ PushStatement();}
	|	proc_def			{ PushStatement();}
	|	RETURN expression	{ PushReturn();}
	|	CONST type NAME '=' expression	{ DecalreVariable($3, true);PushInitStatement($3); PushStatement();}
	|	type CONST NAME '=' expression	{ DecalreVariable($3, true);PushInitStatement($3); PushStatement();}
	|	type NAME '=' expression	{ DecalreVariable($2, false);PushInitStatement($2); PushStatement();}
	|	type NAME			{ DecalreVariable($2, false);}
	|	expression			{ PushStatement();}
	;

expression: NAME '=' expression			{ PushAssignmentStatement($1);} 
	|	NAME ADD_ASSIGN expression		{ PushAddAssign($1);}	
	|	expression '+' expression		{ $$ = $1 + $3; PushAdd();}
	|	expression '-' expression 		{ $$ = $1 - $3; PushSub();}
	|	expression '*' expression 		{ $$ = $1 * $3; PushMul();}
	|	expression '/' expression 		{ $$ = $1 / $3; PushDiv();}
	|	expression '%' expression 		{ $$ = $1 % $3; PushMod();}
	|	INC NAME %prec UMINUS 			{ PushInc($2, false);}
	|	NAME INC						{ PushInc($1, true);}
	|   '-' expression %prec UMINUS  	{ $$ = -$2; printf("---%d\n", $$);} 
	|	'(' expression ')'				{ $$ = $2; PushBlock();}
	|	STRING							{ PushString($1);}
	|	NUMBER							{ PushNumber($1);}
	|	proc_call						{ }
	|	NAME							{ PushVariable($1);}
	;


loop : loop_head loop_block_exit loop_scope_enter statements loop_scope_exit
	;

loop_head : loop_block_enter NUMBER {AddArgment($2);}
	;

loop_block_enter: FOR '(' { PushLoopEnter(); }
	;

loop_block_exit: ')'
	;

loop_scope_enter: '{'
	;

loop_scope_exit: '}'		{ PushLoopExit(); }
	;

proc_def:  proc_def_block_enter parameters proc_def_block_exit proc_def_scope_enter statements proc_def_scope_exit	
	;

proc_def_block_enter: CONST type NAME '(' { PushProcDefEnter($3, true); }
	|	type NAME '(' { PushProcDefEnter($2, false); }
	;

proc_def_block_exit: ')'
	;

proc_def_scope_enter: '{'
	;

proc_def_scope_exit: '}'		{ PushProcDefExit(); }
	;

parameters:	CONST type NAME				{ AddParam($3, true); }
	|	type CONST NAME					{ AddParam($3, true); }
	|	type NAME						{ AddParam($2, false); }
	|	parameters SEPARATE CONST type NAME	{ AddParam($5, true); }	
	|	parameters SEPARATE type CONST NAME	{ AddParam($5, true); }	
	|	parameters SEPARATE type NAME	{ AddParam($4, false); }							
	|													
	;

proc_call:	proc_call_block_enter arguments proc_call_block_exit
	;

proc_call_block_enter: NAME '(' { printf("NAME=%s\n", $1); PushProcCallEnter($1); }
	;

proc_call_block_exit: ')'		{ PushProcCallExit();  }
	;

arguments:	statement
	|	arguments SEPARATE statement
	|
	;

type:	INT		{ PushType("int");}
	|	VOID	{ PushType("void");}
	;


%%

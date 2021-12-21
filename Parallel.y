%{
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
void PushStatement();
void PushReturn();
void PushAssignmentStatement(const char *variable);
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
%}

%union {
	int intv;
	char *strv;
}
%token <strv> FOR
%token <strv> INT
%token <strv> RETURN
%token <strv> STRING
%token <strv> NAME
%token <intv> NUMBER
%token SEPARATE
%left '-' '+'
%left '*' '/' '%'
%nonassoc UMINUS

%type <intv> expression

%%
statements:	statement SEPARATE
	|	statements statement SEPARATE
	;

statement:	loop			{ PushStatement();}
	|	proc_def			{ PushStatement();}
	|	RETURN expression	{ PushReturn();}
	|	NAME '=' expression	{ PushAssignmentStatement($1);}
	|	expression			{ PushStatement();}
	;

expression:	expression '+' expression 	{ $$ = $1 + $3; PushAdd();}
	|	expression '-' expression 		{ $$ = $1 - $3; PushSub();}
	|	expression '*' expression 		{ $$ = $1 * $3; PushMul();}
	|	expression '/' expression 		{ $$ = $1 / $3; PushDiv();}
	|	expression '%' expression 		{ $$ = 0; PushMod();}
	|   '-' expression %prec UMINUS  	{ $$ = -$2; printf("---%d\n", $$);} 
	|	'(' expression ')'				{ $$ = $2; PushBlock();}
	|	STRING							{ $$ = 0;PushString($1);}
	|	NUMBER							{ $$ = $1;PushNumber($1);}
	|	proc_call						{ $$ = 0;}
	|	NAME							{ $$ = 0;PushVariable($1);}
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

proc_def_block_enter: INT NAME '(' { PushProcDefEnter($2); }
	;

proc_def_block_exit: ')'
	;

proc_def_scope_enter: '{'
	;

proc_def_scope_exit: '}'		{ PushProcDefExit(); }
	;

parameters:	NAME					{ AddParam($1); }							
	|	parameters SEPARATE NAME	{ AddParam($3); }							
	|													
	;

proc_call:	proc_call_block_enter arguments proc_call_block_exit
	;

proc_call_block_enter: NAME '(' { PushProcCallEnter($1); }
	;

proc_call_block_exit: ')'		{ PushProcCallExit();  }
	;

arguments:	statement
	|	arguments SEPARATE statement
	|
	;

%%

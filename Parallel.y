%{
#include <stdlib.h>
#include <stdio.h>
#include "common.h"
%}

%union {
	int intv;
	char *strv;
}
%token <strv> FOR
%token <strv> DEF
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

statement:	loop			{ scopes.top()->PushStatement();}
	|	proc_def			{ scopes.top()->PushStatement();}
	|	RETURN expression	{ scopes.top()->PushReturn();}
	|	NAME '=' expression	{ scopes.top()->PushAssignmentStatement($1);}
	|	expression			{ scopes.top()->PushStatement();}
	;

expression:	expression '+' expression 	{ $$ = $1 + $3; scopes.top()->PushAdd();}
	|	expression '-' expression 		{ $$ = $1 - $3; scopes.top()->PushSub();}
	|	expression '*' expression 		{ $$ = $1 * $3; scopes.top()->PushMul();}
	|	expression '/' expression 		{ $$ = $1 / $3; scopes.top()->PushDiv();}
	|	expression '%' expression 		{ $$ = $1 % $3; scopes.top()->PushMod();}
	|   '-' expression %prec UMINUS  	{ $$ = -$2; printf("---%d\n", $$);} 
	|	'(' expression ')'				{ $$ = $2; scopes.top()->PushBlock();}
	|	STRING							{ scopes.top()->PushString($1);}
	|	NUMBER							{ scopes.top()->PushNumber($1);}
	|	proc_call						
	|	NAME							{ scopes.top()->PushVariable($1);}
	;


loop : loop_head loop_block_exit loop_scope_enter statements loop_scope_exit
	;

loop_head : loop_block_enter NUMBER {scopes.top()->AddArgment($2);}
	;

loop_block_enter: FOR '(' { scopes.push(scopes.top()->PushLoopEnter()); }
	;

loop_block_exit: ')'
	;

loop_scope_enter: '{'
	;

loop_scope_exit: '}'		{ scopes.pop(); scopes.top()->PushLoopExit(); }
	;

proc_def:  proc_def_block_enter parameters proc_def_block_exit proc_def_scope_enter statements proc_def_scope_exit	
	;

proc_def_block_enter: DEF NAME '(' { scopes.push(scopes.top()->PushProcDefEnter($2)); }
	;

proc_def_block_exit: ')'
	;

proc_def_scope_enter: '{'
	;

proc_def_scope_exit: '}'		{ scopes.pop(); scopes.top()->PushProcDefExit(); }
	;

parameters:	NAME					{ scopes.top()->AddParam($1); }							
	|	parameters SEPARATE NAME	{ scopes.top()->AddParam($3); }							
	|													
	;

proc_call:	proc_call_block_enter arguments proc_call_block_exit
	;

proc_call_block_enter: NAME '(' { scopes.top()->PushProcCallEnter($1); }
	;

proc_call_block_exit: ')'		{ scopes.top()->PushProcCallExit();  }
	;

arguments:	statement
	|	arguments SEPARATE statement
	|
	;

%%

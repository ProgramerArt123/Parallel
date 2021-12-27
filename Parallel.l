%{
#include "y.tab.h"
%}

%%
for						{ return FOR; }
int						{ return INT; }
void					{ return VOID; }
return					{ return RETURN; }
\+\=					{ return ADD_ASSIGN;}
\"[^\"]*\"				{ yylval.strv = strdup(yytext); return STRING; }
[_a-zA-Z][a-zA-Z0-9]*	{ yylval.strv = strdup(yytext); return NAME; }
[0-9]+			{ yylval.intv = atoi(yytext); return NUMBER; }
[,;]			{ return SEPARATE; }
\n				yylineno++;
[ \t\r]+		;
"//".*$			;
.			return yytext[0];
%%

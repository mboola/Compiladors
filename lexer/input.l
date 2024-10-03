%{
	
#include "helper_functions.h"

%}

%option yylineno
%option noyywrap
%option noinput
%option nounput

DIGIT	[0-9]
ID		[a-zA-Z][a-zA-Z0-9]+

%%

{ID}+	{ printf("This is an ID\n"); }

{DIGIT} { printf("This is a DIGIT\n"); }

.       { printf("What is this\n"); }

%%


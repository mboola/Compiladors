%{
	#include "helper_functions.h"
%}

%option yylineno
%option noyywrap
%option noinput
%option nounput

/* Definitions Section */
ID				[a-zA-Z][a-zA-Z0-9]*
DIGIT			[0-9]
WHITESPACE		[ \t]+

%%

{DIGIT}+		{ if (verbose) printf("Number: %s\n", yytext); }
{ID}+			{ if (verbose) printf("Word: %s\n", yytext); }
{WHITESPACE}	{}
\n				{ if (verbose) printf("Newline detected.\n"); }
":="			{ if (verbose) printf("Asignation detected\n"); }

.				{ if (verbose) printf("What is this: %s\n", yytext); }

<<EOF>>			{ return 0; }

%%

%{
	#include "helper_functions.h"
	#include "input.tab.h"
%}

%option yylineno
%option noyywrap
%option noinput
%option nounput

/* Definitions Section */
WHITESPACE		[ \t]+
ID				[a-zA-Z][a-zA-Z0-9]*
COMENTARI		"//".*|"#".*
COMENTARI_MULT	"/*"([^*]|\*+[^*/])*"*/"
CADENA			"\""{ID}*"\""
DIGIT			[0-9]+
INTEGER			\-?{DIGIT}
FLOAT			({INTEGER}\.{DIGIT})(e{INTEGER})?

%%

{INTEGER}		{
					if (verbose) printf("Integer: %s\n", yytext);
					yylval.integer = atoi(yytext);
					return INTEGER;
				}

{FLOAT}			{
					// Not sure if atof converts everything correctly
					if (verbose) printf("Float: %s\n", yytext);
					yylval.floatp = atof(yytext);
					return FLOAT;
				}
"True"			{ if (verbose) printf("Boolean: %s\n", yytext); }
"False"			{ if (verbose) printf("Boolean: %s\n", yytext); }
{ID}			{ if (verbose) printf("ID: %s\n", yytext); }
{COMENTARI}		{ if (verbose) printf("COMENTARI: %s\n", yytext); }
{COMENTARI_MULT} { if (verbose) printf("COMENTARI_MULT: %s\n", yytext); }
{CADENA}		{ if (verbose) printf("Cadena: %s\n", yytext); }
{WHITESPACE}	{ /* Ignorem espais en blanc */ }
\n				{ if (verbose) printf("Newline detected.\n"); }
":="			{ if (verbose) printf("Asignation detected\n"); }
"+"				{ if (verbose) printf("ADDITION detected\n"); }
"-"				{ if (verbose) printf("SUBSTRACTION detected\n"); }
"**"			{ if (verbose) printf("POWER detected\n"); }
"*"				{ if (verbose) printf("MULTIPLICATION detected\n"); }
"/"				{ if (verbose) printf("DIVISION detected\n"); }
"%"				{ if (verbose) printf("MOD detected\n"); }
"<="			{ if (verbose) printf("LESEQ detected\n"); }
">="			{ if (verbose) printf("BIGEQ detected\n"); }
"<>"			{ if (verbose) printf("NOTEQ detected\n"); }
"<"				{ if (verbose) printf("LESSER detected\n"); }
">"				{ if (verbose) printf("BIGGER detected\n"); }
"="				{ if (verbose) printf("EQUAl detected\n"); }

.				{ if (verbose) printf("What is this: %s\n", yytext); }

<<EOF>>			{ return 0; }

%%

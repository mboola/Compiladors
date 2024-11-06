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
					//yylval.integer = atoi(yytext);
					return INTEGER;
				}

{FLOAT}			{
					// Not sure if atof converts everything correctly
					if (verbose) printf("Float: %s\n", yytext);
					//yylval.floatp = atof(yytext);
					return FLOAT;
				}
"True"			{ if (verbose) printf("Boolean: %s\n", yytext); return TRUE; }
"False"			{ if (verbose) printf("Boolean: %s\n", yytext); return FALSE; }
{ID}			{ if (verbose) printf("ID: %s\n", yytext); return ID; }
{COMENTARI}		{ if (verbose) printf("COMENTARI: %s\n", yytext); }
{COMENTARI_MULT} { if (verbose) printf("COMENTARI_MULT: %s\n", yytext); }
{CADENA}		{ if (verbose) printf("Cadena: %s\n", yytext); return CADENA; }
{WHITESPACE}	{ /* Ignorem espais en blanc */ }
\n				{ if (verbose) printf("Newline detected.\n"); return NEWLINE; }
":="			{ if (verbose) printf("Asignation detected\n"); return ASSIGN; }
"+"				{ if (verbose) printf("ADDITION detected\n"); return ADDITION; }
"-"				{ if (verbose) printf("SUBSTRACTION detected\n"); return SUBSTRACTION; }
"**"			{ if (verbose) printf("POWER detected\n"); return POWER; }
"*"				{ if (verbose) printf("MULTIPLICATION detected\n"); return MULTIPLICATION; }
"/"				{ if (verbose) printf("DIVISION detected\n"); return DIVISION; }
"%"				{ if (verbose) printf("MOD detected\n"); return MOD; }
"<="			{ if (verbose) printf("LESEQ detected\n"); return LESEQ; }
">="			{ if (verbose) printf("BIGEQ detected\n"); return BIGEQ; }
"<>"			{ if (verbose) printf("NOTEQ detected\n"); return NOTEQ; }
"<"				{ if (verbose) printf("LESSER detected\n"); return LESSER; }
">"				{ if (verbose) printf("BIGGER detected\n"); return BIGGER; }
"="				{ if (verbose) printf("EQUAL detected\n"); return EQUAL; }

.				{ if (verbose) printf("What is this: %s\n", yytext); //TODO : exit??}

<<EOF>>			{ return 0; }

%%

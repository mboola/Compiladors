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
COMENT			"//".*|"#".*
COMENT_MULT		"/*"([^*]|\*+[^*/])*"*/"
STRING			"\""{ID}*"\""
DIGIT			[0-9]+
INTEGER			\-?{DIGIT}
FLOAT			({INTEGER}\.{DIGIT})(e{INTEGER})?

%%

{INTEGER}	{
	if (verbose) printf("Integer: %s\n", yytext);
	return INTEGER_TKN;
}
{FLOAT}		{
	if (verbose) printf("Float: %s\n", yytext);
	return FLOAT_TKN;
}
"True"		{
	if (verbose) printf("Boolean: %s\n", yytext);
	return TRUE;
}
"False"		{
	if (verbose) printf("Boolean: %s\n", yytext);
	return FALSE;
}
"not"	{
	if (verbose) printf("NOT detected\n");
	return NOT;
}
"and"	{
	if (verbose) printf("AND detected\n");
	return AND;
}
"or"	{
	if (verbose) printf("OR detected\n");
	return OR;
}
{ID}		{
	if (verbose) printf("ID: %s\n", yytext);
	return ID_TKN;
}
{COMENT}	{
	if (verbose) printf("COMENTARI: %s\n", yytext);
}
{COMENT_MULT} {
	if (verbose) printf("COMENTARI_MULT: %s\n", yytext);
}
{STRING}	{
	if (verbose) printf("Cadena: %s\n", yytext);
	return STRING_TKN;
}
{WHITESPACE} { /* Ignorem espais en blanc */ }

\n		{
	if (verbose) printf("Newline detected.\n");
	return NEWLINE;
}
":="	{
	if (verbose) printf("Assignation detected\n");
	return ASSIGN;
}
"("		{
	if (verbose) printf("Open parenthesis detected");
	return OPENPAR;
}
")"		{
	if (verbose) printf("Closed parenthesis detected");
	return CLOSEDPAR;
}
"+"		{
	if (verbose) printf("ADDITION detected\n");
	return ADDITION;
}
"-"		{
	if (verbose) printf("SUBSTRACTION detected\n");
	return SUBSTRACTION;
}
"**"	{
	if (verbose) printf("POWER detected\n");
	return POWER;
	}
"*"		{
	if (verbose) printf("MULTIPLICATION detected\n");
	return MULTIPLICATION;
}
"/"		{
	if (verbose) printf("DIVISION detected\n");
	return DIVISION;
}
"%"		{
	if (verbose) printf("MOD detected\n");
	return MOD;
}
"<="	{
	if (verbose) printf("LESEQ detected\n");
	return OPREL;
}
">="	{
	if (verbose) printf("BIGEQ detected\n");
	return OPREL;
}
"<>"	{
	if (verbose) printf("NOTEQ detected\n");
	return OPREL;
}
"<"		{
	if (verbose) printf("LESSER detected\n");
	return OPREL;
}
">"		{
	if (verbose) printf("BIGGER detected\n");
	return OPREL;
}
"="		{
	if (verbose) printf("EQUAL detected\n");
	return OPREL;
}

.				{ if (verbose) printf("What is this: %s\n", yytext); }

<<EOF>>			{ return 0; }

%%

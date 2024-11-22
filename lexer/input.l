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
NEWLINE			"\n"
STRING			"\""{ID}*"\""
DIGIT			[0-9]+
INTEGER			\-?{DIGIT}
FLOAT			({INTEGER}\.{DIGIT})(e{INTEGER})?

%%

{INTEGER}	{
	if (verbose) printf("Integer: %s\n", yytext);
	yylval.integer = malloc(sizeof(int));
	if (yylval.integer == NULL)
		exit(1);
	*(yylval.integer) = atoi(yytext);
	return INTEGER_TKN;
}
{FLOAT}		{
	if (verbose) printf("Float: %s\n", yytext);
	yylval.real = malloc(sizeof(float));
	if (yylval.real == NULL)
		exit(1);
	*(yylval.real) = atof(yytext);
	return FLOAT_TKN;
}
"True"		{
	if (verbose) printf("Boolean: %s\n", yytext);
	yylval.boolean = malloc(sizeof(char));
	if (yylval.boolean == NULL)
		exit(1);
	*(yylval.boolean) = 1;
	return TRUE;
}
"False"		{
	if (verbose) printf("Boolean: %s\n", yytext);
	yylval.boolean = malloc(sizeof(char));
	if (yylval.boolean == NULL)
		exit(1);
	*(yylval.boolean) = 0;
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
	initialize_id(&yylval.id, yytext);
	return ID_TKN;
}
{COMENT}{NEWLINE}	{
	if (verbose) printf("COMENTARI: %s", yytext);
}
{COMENT_MULT}{NEWLINE} {
	if (verbose) printf("COMENTARI_MULT: %s", yytext);
}
{STRING}	{
	if (verbose) printf("Cadena: %s\n", yytext);
	yylval.string = strdup(yytext);
	return STRING_TKN;
}
{WHITESPACE} { /* Ignorem espais en blanc */ }

{NEWLINE}	{
	if (verbose) printf("Newline detected.\n");
	return NEWLINE_TKN;
}
":="	{
	if (verbose) printf("Assignation detected.\n");
	return ASSIGN;
}
"("		{
	if (verbose) printf("Open parenthesis detected.\n");
	return OPENPAR;
}
")"		{
	if (verbose) printf("Closed parenthesis detected.\n");
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
	yylval.oprel.type = LESEQ;
	return OPREL;
}
">="	{
	if (verbose) printf("BIGEQ detected\n");
	yylval.oprel.type = BIGEQ;
	return OPREL;
}
"<>"	{
	if (verbose) printf("NOTEQ detected\n");
	yylval.oprel.type = NOTEQ;
	return OPREL;
}
"<"		{
	if (verbose) printf("LESSER detected\n");
	yylval.oprel.type = LESSER;
	return OPREL;
}
">"		{
	if (verbose) printf("BIGGER detected\n");
	yylval.oprel.type = BIGGER;
	return OPREL;
}
"="		{
	if (verbose) printf("EQUAL detected\n");
	yylval.oprel.type = EQUAL;
	return OPREL;
}

.				{ if (verbose) printf("What is this: %s\n", yytext); }

<<EOF>>			{ return 0; }

%%

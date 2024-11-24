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
	if (lexer_verbose) printf("Integer: %s\n", yytext);
	yylval.integer = yymalloc(sizeof(int));
	*(yylval.integer) = atoi(yytext);
	return INTEGER_TKN;
}
{FLOAT}		{
	if (lexer_verbose) printf("Float: %s\n", yytext);
	yylval.real = yymalloc(sizeof(float));
	*(yylval.real) = atof(yytext);
	return FLOAT_TKN;
}
"True"		{
	if (lexer_verbose) printf("Boolean: %s\n", yytext);
	yylval.boolean = yymalloc(sizeof(char));
	*(yylval.boolean) = 1;
	return TRUE;
}
"False"		{
	if (lexer_verbose) printf("Boolean: %s\n", yytext);
	yylval.boolean = yymalloc(sizeof(char));
	*(yylval.boolean) = 0;
	return FALSE;
}
"not"	{
	if (lexer_verbose) printf("NOT detected\n");
	return NOT;
}
"and"	{
	if (lexer_verbose) printf("AND detected\n");
	return AND;
}
"or"	{
	if (lexer_verbose) printf("OR detected\n");
	return OR;
}
"sin"	{
	if (lexer_verbose) printf("SIN detected\n");
	return SIN;
}
"cos"	{
	if (lexer_verbose) printf("COS detected\n");
	return COS;
}
"tan"	{
	if (lexer_verbose) printf("TAN detected\n");
	return TAN;
}
"LEN"	{
	if (lexer_verbose) printf("LEN detected\n");
	return LEN;
}
"SUBSTR"	{
	if (lexer_verbose) printf("SUBSTR detected\n");
	return SUBSTR;
}
"PI"	{
	if (lexer_verbose) printf("PI detected\n");
	yylval.real = yymalloc(sizeof(float));
	*(yylval.real) = PI_CONST;
	return FLOAT_TKN;
}
"E"	{
	if (lexer_verbose) printf("E detected\n");
	yylval.real = yymalloc(sizeof(float));
	*(yylval.real) = E_CONST;
	return FLOAT_TKN;
}
"OCT"	{
	if (lexer_verbose) printf("OCT detected\n");
	return OCT;
}
"BIN"	{
	if (lexer_verbose) printf("BIN detected\n");
	return BIN;
}
"HEX"	{
	if (lexer_verbose) printf("HEX detected\n");
	return HEX;
}
"DEC"	{
	if (lexer_verbose) printf("DEC detected\n");
	return DEC;
}
{ID}		{
	if (lexer_verbose) printf("ID: %s\n", yytext);
	initialize_id(&yylval.id, yytext);
	return ID_TKN;
}
{COMENT}{NEWLINE}	{
	if (lexer_verbose) printf("COMENTARI: %s", yytext);
}
{COMENT_MULT}{NEWLINE} {
	if (lexer_verbose) printf("COMENTARI_MULT: %s", yytext);
}
{STRING}	{
	if (lexer_verbose) printf("Cadena: %s\n", yytext);
	yylval.string = str_convert(yytext);
	return STRING_TKN;
}
{WHITESPACE} { /* Ignorem espais en blanc */ }

{NEWLINE}	{
	if (lexer_verbose) printf("Newline detected.\n");
	return NEWLINE_TKN;
}
":="	{
	if (lexer_verbose) printf("Assignation detected.\n");
	return ASSIGN;
}
"("		{
	if (lexer_verbose) printf("Open parenthesis detected.\n");
	return OPENPAR;
}
")"		{
	if (lexer_verbose) printf("Closed parenthesis detected.\n");
	return CLOSEDPAR;
}
"+"		{
	if (lexer_verbose) printf("ADDITION detected\n");
	return ADDITION;
}
"-"		{
	if (lexer_verbose) printf("SUBSTRACTION detected\n");
	return SUBSTRACTION;
}
"**"	{
	if (lexer_verbose) printf("POWER detected\n");
	return POWER;
	}
"*"		{
	if (lexer_verbose) printf("MULTIPLICATION detected\n");
	return MULTIPLICATION;
}
"/"		{
	if (lexer_verbose) printf("DIVISION detected\n");
	return DIVISION;
}
"%"		{
	if (lexer_verbose) printf("MOD detected\n");
	return MOD;
}
"<="	{
	if (lexer_verbose) printf("LESEQ detected\n");
	yylval.oprel.type = LESEQ;
	return OPREL;
}
">="	{
	if (lexer_verbose) printf("BIGEQ detected\n");
	yylval.oprel.type = BIGEQ;
	return OPREL;
}
"<>"	{
	if (lexer_verbose) printf("NOTEQ detected\n");
	yylval.oprel.type = NOTEQ;
	return OPREL;
}
"<"		{
	if (lexer_verbose) printf("LESSER detected\n");
	yylval.oprel.type = LESSER;
	return OPREL;
}
">"		{
	if (lexer_verbose) printf("BIGGER detected\n");
	yylval.oprel.type = BIGGER;
	return OPREL;
}
"="		{
	if (lexer_verbose) printf("EQUAL detected\n");
	yylval.oprel.type = EQUAL;
	return OPREL;
}

.				{ if (lexer_verbose) printf("What is this: %s\n", yytext); }

<<EOF>>			{ return 0; }

%%

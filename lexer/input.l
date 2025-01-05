%{
	#include "const_definitions.h"
	#include "yyfunctions.h"
	#include "helper_functions.h"
	#include "str_functions.h"
	#include "input.tab.h"
	#include "compiler_flags.h"
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
INTEGER			{DIGIT}
FLOAT			({INTEGER}\.{DIGIT})(e{INTEGER})?

%%

{INTEGER}	{
	yylexer_output("Integer: %s", yytext);
	yylval.integer = yymalloc(sizeof(int));
	*(yylval.integer) = atoi(yytext);
	return INTEGER_TKN;
}
{FLOAT}		{
	yylexer_output("Float: %s", yytext);
	yylval.real = yymalloc(sizeof(float));
	*(yylval.real) = atof(yytext);
	return FLOAT_TKN;
}
"true"		{
	yylexer_output("Boolean: %s", yytext);
	yylexer_p2_error();
}
"false"		{
	yylexer_output("Boolean: %s", yytext);
	yylexer_p2_error();
}
"not"	{
	yylexer_output("NOT detected");
	yylexer_p2_error();
}
"and"	{
	yylexer_output("AND detected");
	yylexer_p2_error();
}
"or"	{
	yylexer_output("OR detected");
	yylexer_p2_error();
}
"sin"	{
	yylexer_output("SIN detected");
	return SIN;
}
"cos"	{
	yylexer_output("COS detected");
	return COS;
}
"tan"	{
	yylexer_output("TAN detected");
	return TAN;
}
"LEN"	{
	yylexer_output("LEN detected");
	yylexer_p2_error();
}
"SUBSTR"	{
	yylexer_output("SUBSTR detected");
	yylexer_p2_error();
}
"repeat"	{
	yylexer_output("REPEAT detected");
	return REPEAT;
}
"do"		{
	yylexer_output("DO detected");
	return DO;
}
"done"		{
	yylexer_output("DONE detected");
	return DONE;
}
"PI"	{
	yylexer_output("PI detected");
	yylval.real = yymalloc(sizeof(float));
	*(yylval.real) = PI_CONST;
	return FLOAT_TKN;
}
"E"	{
	yylexer_output("E detected");
	yylval.real = yymalloc(sizeof(float));
	*(yylval.real) = E_CONST;
	return FLOAT_TKN;
}
"OCT"	{
	yylexer_output("OCT detected");
	return OCT;
}
"BIN"	{
	yylexer_output("BIN detected");
	return BIN;
}
"HEX"	{
	yylexer_output("HEX detected");
	return HEX;
}
"DEC"	{
	yylexer_output("DEC detected");
	return DEC;
}
"RICARDO"	{
	yylexer_output("RICARDO detected");
	return RIC;
}
{ID}		{
	yylexer_output("ID: %s", yytext);
	initialize_id(&yylval.id, yytext);
	return ID_TKN;
}
{COMENT}{NEWLINE}	{
	yylexer_output("COMENTARI: %s", yytext);
	yycol = 0;
}
{COMENT_MULT}{NEWLINE} {
	yylexer_output("COMENTARI_MULT: %s", yytext);
	yycol = 0;
}
{STRING}	{
	yylexer_output("Cadena: %s", yytext);
	yylexer_p2_error();
}
{WHITESPACE} { update_yycol(); /* Ignorem espais en blanc */ }

{NEWLINE}	{
	yylexer_output("NEWLINE_TKN detected");
	yycol = 0;
	return NEWLINE_TKN;
}
":="	{
	yylexer_output("ASSIGN detected");
	return ASSIGN;
}
"("		{
	yylexer_output("OPENPAR detected");
	return OPENPAR;
}
")"		{
	yylexer_output("CLOSEDPAR detected");
	return CLOSEDPAR;
}
"+"		{
	yylexer_output("ADDITION detected");
	return ADDITION;
}
"-"		{
	yylexer_output("SUBSTRACTION detected");
	return SUBSTRACTION;
}
"**"	{
	yylexer_output("POWER detected");
	return POWER;
}
"*"		{
	yylexer_output("MULTIPLICATION detected");
	return MULTIPLICATION;
}
"/"		{
	yylexer_output("DIVISION detected");
	return DIVISION;
}
"%"		{
	yylexer_output("MOD detected");
	return MOD;
}
"<="	{
	yylexer_output("LESEQ detected");
	yylexer_p2_error();
}
">="	{
	yylexer_output("BIGEQ detected");
	yylexer_p2_error();
}
"<>"	{
	yylexer_output("NOTEQ detected");
	yylexer_p2_error();
}
"<"		{
	yylexer_output("LESSER detected");
	yylexer_p2_error();
}
">"		{
	yylexer_output("BIGGER detected");
	yylexer_p2_error();
}
"="		{
	yylexer_output("EQUAL detected");
	yylexer_p2_error();
}

.		{
	yylexer_error();
}


<<EOF>>	{ return 0; }

%%

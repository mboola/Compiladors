%{
	#include "const_definitions.h"
	#include "yyfunctions.h"
	#include "helper_functions.h"
	#include "str_functions.h"
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
"True"		{
	yylexer_output("Boolean: %s", yytext);
	yylval.boolean = yymalloc(sizeof(char));
	*(yylval.boolean) = 1;
	return TRUE;
}
"False"		{
	yylexer_output("Boolean: %s", yytext);
	yylval.boolean = yymalloc(sizeof(char));
	*(yylval.boolean) = 0;
	return FALSE;
}
"not"	{
	yylexer_output("NOT detected");
	return NOT;
}
"and"	{
	yylexer_output("AND detected");
	return AND;
}
"or"	{
	yylexer_output("OR detected");
	return OR;
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
	return LEN;
}
"SUBSTR"	{
	yylexer_output("SUBSTR detected");
	return SUBSTR;
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
{ID}		{
	yylexer_output("ID: %s", yytext);
	initialize_id(&yylval.id, yytext);
	return ID_TKN;
}
{COMENT}{NEWLINE}	{
	yylexer_output("COMENTARI: %s", yytext);
}
{COMENT_MULT}{NEWLINE} {
	yylexer_output("COMENTARI_MULT: %s", yytext);
}
{STRING}	{
	yylexer_output("Cadena: %s", yytext);
	yylval.string = str_convert(yytext);
	return STRING_TKN;
}
{WHITESPACE} { /* Ignorem espais en blanc */ }

{NEWLINE}	{
	yylexer_output("NEWLINE_TKN detected");
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
	yylval.oprel.type = LESEQ;
	return OPREL;
}
">="	{
	yylexer_output("BIGEQ detected");
	yylval.oprel.type = BIGEQ;
	return OPREL;
}
"<>"	{
	yylexer_output("NOTEQ detected");
	yylval.oprel.type = NOTEQ;
	return OPREL;
}
"<"		{
	yylexer_output("LESSER detected");
	yylval.oprel.type = LESSER;
	return OPREL;
}
">"		{
	yylexer_output("BIGGER detected");
	yylval.oprel.type = BIGGER;
	return OPREL;
}
"="		{
	yylexer_output("EQUAL detected");
	yylval.oprel.type = EQUAL;
	return OPREL;
}

.				{ yylexer_error(strjoin("Token not recognized: ", yytext)); }

<<EOF>>			{ return 0; }

%%

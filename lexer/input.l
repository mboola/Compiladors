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
	if (lexer_verbose) print_lexer_output("Integer: %s", yytext);
	yylval.integer = yymalloc(sizeof(int));
	*(yylval.integer) = atoi(yytext);
	return INTEGER_TKN;
}
{FLOAT}		{
	if (lexer_verbose) print_lexer_output("Float: %s", yytext);
	yylval.real = yymalloc(sizeof(float));
	*(yylval.real) = atof(yytext);
	return FLOAT_TKN;
}
"True"		{
	if (lexer_verbose) print_lexer_output("Boolean: %s", yytext);
	yylval.boolean = yymalloc(sizeof(char));
	*(yylval.boolean) = 1;
	return TRUE;
}
"False"		{
	if (lexer_verbose) print_lexer_output("Boolean: %s", yytext);
	yylval.boolean = yymalloc(sizeof(char));
	*(yylval.boolean) = 0;
	return FALSE;
}
"not"	{
	if (lexer_verbose) print_lexer_output("NOT detected");
	return NOT;
}
"and"	{
	if (lexer_verbose) print_lexer_output("AND detected");
	return AND;
}
"or"	{
	if (lexer_verbose) print_lexer_output("OR detected");
	return OR;
}
"sin"	{
	if (lexer_verbose) print_lexer_output("SIN detected");
	return SIN;
}
"cos"	{
	if (lexer_verbose) print_lexer_output("COS detected");
	return COS;
}
"tan"	{
	if (lexer_verbose) print_lexer_output("TAN detected");
	return TAN;
}
"LEN"	{
	if (lexer_verbose) print_lexer_output("LEN detected");
	return LEN;
}
"SUBSTR"	{
	if (lexer_verbose) print_lexer_output("SUBSTR detected");
	return SUBSTR;
}
"repeat"	{
	if (lexer_verbose) print_lexer_output("REPEAT detected");
	return REPEAT;
}
"do"		{
	if (lexer_verbose) print_lexer_output("DO detected");
	return DO;
}
"done"		{
	if (lexer_verbose) print_lexer_output("DONE detected");
	return DONE;
}
"PI"	{
	if (lexer_verbose) print_lexer_output("PI detected");
	yylval.real = yymalloc(sizeof(float));
	*(yylval.real) = PI_CONST;
	return FLOAT_TKN;
}
"E"	{
	if (lexer_verbose) print_lexer_output("E detected");
	yylval.real = yymalloc(sizeof(float));
	*(yylval.real) = E_CONST;
	return FLOAT_TKN;
}
"OCT"	{
	if (lexer_verbose) print_lexer_output("OCT detected");
	return OCT;
}
"BIN"	{
	if (lexer_verbose) print_lexer_output("BIN detected");
	return BIN;
}
"HEX"	{
	if (lexer_verbose) print_lexer_output("HEX detected");
	return HEX;
}
"DEC"	{
	if (lexer_verbose) print_lexer_output("DEC detected");
	return DEC;
}
{ID}		{
	if (lexer_verbose) print_lexer_output("ID: %s", yytext);
	initialize_id(&yylval.id, yytext);
	return ID_TKN;
}
{COMENT}{NEWLINE}	{
	if (lexer_verbose) print_lexer_output("COMENTARI: %s", yytext);
}
{COMENT_MULT}{NEWLINE} {
	if (lexer_verbose) print_lexer_output("COMENTARI_MULT: %s", yytext);
}
{STRING}	{
	if (lexer_verbose) print_lexer_output("Cadena: %s", yytext);
	yylval.string = str_convert(yytext);
	return STRING_TKN;
}
{WHITESPACE} { /* Ignorem espais en blanc */ }

{NEWLINE}	{
	if (lexer_verbose) print_lexer_output("NEWLINE_TKN detected");
	return NEWLINE_TKN;
}
":="	{
	if (lexer_verbose) print_lexer_output("ASSIGN detected");
	return ASSIGN;
}
"("		{
	if (lexer_verbose) print_lexer_output("OPENPAR detected");
	return OPENPAR;
}
")"		{
	if (lexer_verbose) print_lexer_output("CLOSEDPAR detected");
	return CLOSEDPAR;
}
"+"		{
	if (lexer_verbose) print_lexer_output("ADDITION detected");
	return ADDITION;
}
"-"		{
	if (lexer_verbose) print_lexer_output("SUBSTRACTION detected");
	return SUBSTRACTION;
}
"**"	{
	if (lexer_verbose) print_lexer_output("POWER detected");
	return POWER;
	}
"*"		{
	if (lexer_verbose) print_lexer_output("MULTIPLICATION detected");
	return MULTIPLICATION;
}
"/"		{
	if (lexer_verbose) print_lexer_output("DIVISION detected");
	return DIVISION;
}
"%"		{
	if (lexer_verbose) print_lexer_output("MOD detected");
	return MOD;
}
"<="	{
	if (lexer_verbose) print_lexer_output("LESEQ detected");
	yylval.oprel.type = LESEQ;
	return OPREL;
}
">="	{
	if (lexer_verbose) print_lexer_output("BIGEQ detected");
	yylval.oprel.type = BIGEQ;
	return OPREL;
}
"<>"	{
	if (lexer_verbose) print_lexer_output("NOTEQ detected");
	yylval.oprel.type = NOTEQ;
	return OPREL;
}
"<"		{
	if (lexer_verbose) print_lexer_output("LESSER detected");
	yylval.oprel.type = LESSER;
	return OPREL;
}
">"		{
	if (lexer_verbose) print_lexer_output("BIGGER detected");
	yylval.oprel.type = BIGGER;
	return OPREL;
}
"="		{
	if (lexer_verbose) print_lexer_output("EQUAL detected");
	yylval.oprel.type = EQUAL;
	return OPREL;
}

.				{ if (lexer_verbose) fprintf(yyfrontend_res, "Lexer: What is this: %s\n", yytext); }

<<EOF>>			{ return 0; }

%%

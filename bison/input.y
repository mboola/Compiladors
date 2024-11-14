%{

#include <stdio.h>
#include <stdlib.h>
#include "helper_functions.h"

%}

%code requires {
  /* Les definicions que s'utilitzen al %union han d'estar aqui */
  #include "data_types.h"
}

/* Definition of yylval */
%union{
    int integer;
    float real;
    id identifier;
    char *string;
    t_assignment assignment;
    t_expression expression;
    void *no_value;
}

%token <integer> INTEGER
%token <real> FLOAT
%token <identifier> ID
%token <string> CADENA
%token <expression> TRUE FALSE
%token ASSIGN NEWLINE ADDITION SUBSTRACTION POWER MULTIPLICATION DIVISION MOD LESEQ BIGEQ NOTEQ LESSER BIGGER EQUAL OPENPAR CLOSEDPAR

%type <no_value> program
%type <assignment> sentence assignment
%type <expression> expression boolean_expression

%start program

%%

program : program sentence | sentence
{
  //fprintf(yyout, "program -> expressio :\n  expressio = '%s'\n", expression_to_str($1));
}

sentence : assignment

assignment : ID ASSIGN expression
{
  $$.name = $1.lexema;
  $$.value = $3.value;
  fprintf(yyout, "Assignment: %s\n", assignment_to_str($$));
}

expression: boolean_expression NEWLINE | arithmetic_expression NEWLINE
{
  fprintf(yyout, "Expression: %s\n", expression_to_str($$));
}

boolean_expression :
  TRUE
  | FALSE
  | arithmetic_expression BIGGER arithmetic_expression { fprintf(yyout, "Bigger.\n"); }
  ;

arithmetic_expression :
  INTEGER
  | arithmetic_expression ADDITION arithmetic_expression { fprintf(yyout, "Addition.\n"); }
  ;

%%

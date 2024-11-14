%{

#include <stdio.h>
#include <stdlib.h>
#include "helper_functions.h"

%}

%code requires {
  /* Les definicions que s'utilitzen al %union han d'estar aqui */
  #include "data_types.h"
}

%union{
    int integer;
    float real;
    char boolean;
    char *string;
    void *no_value;
    struct {
      char *lexema;
      int len;
    } t_id;

    value_info expr_val;
    void *sense_valor;
    struct {
        char *lexema;
        int lenght;
        int line;
        value_info id_val;
    } t_ident;
    struct {
      char *name;
      data_type type;
    } t_assignment;
    struct {
      data_type type;
      void *value;
    } t_expression;
    struct {
      oprel_type type;
    } t_op_rel;
}

%token <integer> INTEGER_TKN
%token <real> FLOAT_TKN
%token <boolean> TRUE FALSE
%token <t_id> ID_TKN
%token <string> STRING_TKN
%token <no_value> NEWLINE ASSIGN OPENPAR CLOSEDPAR ADDITION SUBSTRACTION POWER MULTIPLICATION DIVISION MOD AND NOT OR
%token <t_op_rel> OPREL

%type <no_value> program
%type <t_expression> expression arithmetic_expression boolean_expression
%type <t_assignment> assignment

%start program

%%

program : program sentence | sentence
{
  //fprintf(yyout, "program -> expressio :\n  expressio = '%s'\n", expression_to_str($1));
}

sentence :
  arithmetic_expression NEWLINE
  | boolean_expression NEWLINE
  | assignment
{
  fprintf(yyout, "Sentence.\n");
}

assignment : ID_TKN ASSIGN expression NEWLINE
{
  fprintf(yyout, "Assignment.\n");
}

expression : arithmetic_expression | boolean_expression
{
  fprintf(yyout, "expression.\n");
}

exp : exp1 ADDITION exp | exp1 SUBSTRACTION exp | exp1

exp1 : exp2 MULTIPLICATION exp1 | exp2 DIVISION exp1 | exp2 MOD exp1 | exp2

exp2 : exp3 POWER exp2 | exp3

exp3 : OPENPAR exp CLOSEDPAR | INTEGER_TKN | FLOAT_TKN

arithmetic_expression : exp
{
  fprintf(yyout, "arithmetic_expression.\n");
}

bexp : bexp1 OR bexp | bexp1

bexp1 : bexp2 AND bexp1 | bexp2

bexp2 : bexp3 NOT bexp2 | bexp3

bexp3 : arithmetic_expression OPREL arithmetic_expression | TRUE | FALSE

boolean_expression : bexp
{
  fprintf(yyout, "boolean_expression.\n");
}

%%

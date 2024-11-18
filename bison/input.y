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
%token <no_value> NEWLINE_TKN ASSIGN OPENPAR CLOSEDPAR ADDITION SUBSTRACTION POWER MULTIPLICATION DIVISION MOD AND NOT OR
%token <t_op_rel> OPREL

%type <no_value> program
%type <t_expression> expression arithmetic_expression boolean_expression exp exp1 exp2 exp3
%type <t_assignment> assignment

%start program

%%

program :
  program sentence { printf("program is a collection of sentences\n"); }
  | sentence {printf("program is a sentence\n");}

sentence :
  arithmetic_expression NEWLINE_TKN { printf("new sentence with arithmetic_expression\n"); }
  | boolean_expression NEWLINE_TKN { printf("new sentence with boolean_expression\n"); }
  | assignment { printf("new sentence with assignment\n"); }

assignment : ID_TKN ASSIGN expression NEWLINE_TKN
{ printf("assignment detected \n"); }

expression :
  arithmetic_expression { printf("new expression with arithmetic_expression\n"); }
  | boolean_expression { printf("new sentence with boolean_expression\n"); }

arithmetic_expression : exp {printf("\tnew arithmetic_expression\n");}

exp :
  exp1 ADDITION exp
  | exp1 SUBSTRACTION exp { printf("new exp bc of substraction\n"); }
  | exp1

exp1 :
  exp2 MULTIPLICATION exp1
  | exp2 DIVISION exp1
  | exp2 MOD exp1
  | exp2

exp2 : exp3 POWER exp2 | exp3

exp3 :
  OPENPAR exp CLOSEDPAR {printf("\t parenthesis used \n");}
  | INTEGER_TKN
  | FLOAT_TKN
  | ID_TKN
  | STRING_TKN

bexp : bexp1 OR bexp | bexp1

bexp1 : bexp2 AND bexp1 | bexp2

bexp2 : bexp3 NOT bexp2 | bexp3

bexp3 : arithmetic_expression OPREL arithmetic_expression | TRUE | FALSE

boolean_expression : bexp
{
  fprintf(yyout, "boolean_expression.\n");
}

%%

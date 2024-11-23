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
    int *integer;
    float *real;
    char *boolean;
    char *string;
    t_id id;
    t_expression expression_type;
    t_oprel oprel;
    t_assignment assignment_type;
    void *no_value;
}

%token <integer> INTEGER_TKN
%token <real> FLOAT_TKN
%token <string> STRING_TKN
%token <boolean> TRUE FALSE
%token <id> ID_TKN
%token <no_value> NEWLINE_TKN ASSIGN OPENPAR CLOSEDPAR ADDITION SUBSTRACTION POWER MULTIPLICATION DIVISION MOD AND NOT OR
%token <oprel> OPREL

%type <no_value> program sentence
%type <expression_type> expression arithmetic_expression boolean_expression exp exp1 exp2 exp3
%type <assignment_type> assignment

%start program

%%

program :
  program sentence
  | sentence

sentence :
  arithmetic_expression NEWLINE_TKN { print_expression($1); }
  | boolean_expression NEWLINE_TKN { print_expression($1); }
  | assignment { print_assignment($1); }

assignment : ID_TKN ASSIGN expression NEWLINE_TKN
{
  if (parser_verbose) printf("assignment detected \n");
  if ($1.type == UNKNOWN_TYPE || $1.type == $3.type)
  {
    $1.type = $3.type;
    $1.value = $3.value;
  }
  if ($1.type != UNKNOWN_TYPE && $1.type != $3.type)
    yyerror("Different type assignation.\n");
  update_id(&$1);
}

expression :
  arithmetic_expression
  { if (parser_verbose) printf("new expression with arithmetic_expression\n");
    $$.type = $1.type;
    $$.value = $1.value;
  }
  | boolean_expression { if (parser_verbose) printf("new sentence with boolean_expression\n"); }

arithmetic_expression : exp
{ if (parser_verbose) printf("\tnew arithmetic_expression\n");
  $$.type = $1.type;
  $$.value = $1.value;
  print_expression($$);
}

exp :
  exp1 ADDITION exp { if (parser_verbose) printf("new exp bc of addition\n"); addition(&$$, $1, $3); }
  | exp1 SUBSTRACTION exp { printf("new exp bc of substraction\n"); }
  | SUBSTRACTION exp1 { printf("new unarian exp bc of substraction\n"); }
  | ADDITION exp1 { printf("new unarian exp bc of addition\n"); }
  | exp1 {$$.type = $1.type; $$.value = $1.value;}

exp1 :
  exp2 MULTIPLICATION exp1
  | exp2 DIVISION exp1
  | exp2 MOD exp1
  | exp2 {$$.type = $1.type; $$.value = $1.value;}

exp2 : exp3 POWER exp2
  | exp3 {$$.type = $1.type; $$.value = $1.value; }

exp3 :
  OPENPAR exp CLOSEDPAR {printf("\t parenthesis used \n"); assign_expression(&($$), $2.type, $2.value); }
  | INTEGER_TKN { assign_expression(&($$), INT_TYPE, $1); }
  | FLOAT_TKN { assign_expression(&($$), FLOAT_TYPE, $1); }
  | ID_TKN { get_id(&$1); assign_expression(&($$), $1.type, $1.value); }
  | STRING_TKN { assign_expression(&($$), STRING_TYPE, $1); }

bexp : bexp1 OR bexp | bexp1

bexp1 : bexp2 AND bexp1 | bexp2

bexp2 : bexp3 NOT bexp2 | bexp3

bexp3 : arithmetic_expression OPREL arithmetic_expression | TRUE | FALSE

boolean_expression : bexp
{
  fprintf(yyout, "boolean_expression.\n");
}

%%

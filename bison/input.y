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
%type <expression_type> expression arithmetic_expression boolean_expression exp exp1 exp2 exp3 bexp bexp1 bexp2 bexp3
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
  arithmetic_expression { $$.type = $1.type; $$.value = $1.value; }
  | boolean_expression { $$.type = $1.type; $$.value = $1.value; }

arithmetic_expression :
  exp { $$.type = $1.type; $$.value = $1.value; }

exp :
  exp1 ADDITION exp { addition(&$$, $1, $3); }
  | exp1 SUBSTRACTION exp { substraction(&$$, $1, $3); }
  | SUBSTRACTION exp1 { printf("new unarian exp bc of substraction\n"); }
  | ADDITION exp1 { printf("new unarian exp bc of addition\n"); }
  | exp1 {$$.type = $1.type; $$.value = $1.value;}

exp1 :
  exp2 MULTIPLICATION exp1 { multiplication(&$$, $1, $3); }
  | exp2 DIVISION exp1 { division(&$$, $1, $3); }
  | exp2 MOD exp1 { modulation(&$$, $1, $3); }
  | exp2 {$$.type = $1.type; $$.value = $1.value;}

exp2 :
  exp3 POWER exp2 { power(&$$, $1, $3); }
  | exp3 {$$.type = $1.type; $$.value = $1.value; }

exp3 :
  OPENPAR exp CLOSEDPAR { $$.type = $2.type; $$.value = $2.value; }
  | INTEGER_TKN { $$.type = INT_TYPE; $$.value = $1; }
  | FLOAT_TKN { $$.type = FLOAT_TYPE; $$.value = $1; }
  | STRING_TKN { $$.type = STRING_TYPE; $$.value = $1; }
  | ID_TKN { get_id(&$1); assign_expression(&($$), $1.type, $1.value); }

bexp :
  bexp1 OR bexp
  | bexp1 { $$.type = $1.type; $$.value = $1.value; }

bexp1 :
  bexp2 AND bexp1
  | bexp2 { $$.type = $1.type; $$.value = $1.value; }

bexp2 :
  bexp3 NOT bexp2
  | bexp3 { $$.type = $1.type; $$.value = $1.value; }

bexp3 :
  arithmetic_expression OPREL arithmetic_expression { compare(&$$, $1, $2, $3); }
  | TRUE { $$.type = BOOLEAN_TYPE; $$.value = $1; }
  | FALSE { $$.type = BOOLEAN_TYPE; $$.value = $1; }

boolean_expression :
  bexp
{
  fprintf(yyout, "boolean_expression.\n");
}

%%

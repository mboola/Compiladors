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
  program sentence { if (verbose) printf("program is a collection of sentences\n"); }
  | sentence { if (verbose) printf("program is a sentence\n");}

sentence :
  arithmetic_expression NEWLINE_TKN { if (verbose) printf("new sentence with arithmetic_expression\n"); }
  | boolean_expression NEWLINE_TKN { if (verbose) printf("new sentence with boolean_expression\n"); }
  | assignment { if (verbose) printf("new sentence with assignment\n"); }

assignment : ID_TKN ASSIGN expression NEWLINE_TKN
{ if (verbose) printf("assignment detected \n"); }

expression :
  arithmetic_expression { if (verbose) printf("new expression with arithmetic_expression\n"); }
  | boolean_expression { if (verbose) printf("new sentence with boolean_expression\n"); }

arithmetic_expression : exp {if (verbose) printf("\tnew arithmetic_expression\n");}

exp :
  exp1 ADDITION exp { if (verbose) printf("new exp bc of addition\n"); }
  | exp1 SUBSTRACTION exp { printf("new exp bc of substraction\n"); }
  | SUBSTRACTION exp1 { printf("new unarian exp bc of substraction\n"); }
  | ADDITION exp1 { printf("new unarian exp bc of addition\n"); }
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

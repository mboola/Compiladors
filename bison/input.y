%{

#include "parser_operations.h"
#include "yyfunctions.h"
#include "compiler.h"
#include "compiler_flags.h"
#include "helper_functions.h"
#include "compile_instructions.h"

extern int yylex();

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
    t_repeat repeat_type;
    void *no_value;
}

%token <integer> INTEGER_TKN
%token <real> FLOAT_TKN
%token <string> STRING_TKN
%token <boolean> TRUE FALSE
%token <id> ID_TKN
%token <no_value> NEWLINE_TKN ASSIGN OPENPAR CLOSEDPAR ADDITION SUBSTRACTION POWER MULTIPLICATION DIVISION MOD NOT AND OR SIN COS TAN LEN SUBSTR OCT BIN HEX DEC REPEAT DONE DO
%token <oprel> OPREL

%type <no_value> program sentence representation_mode sentence_list
%type <expression_type> expression arithmetic_expression boolean_expression exp exp1 exp2 exp3 bexp bexp1 bexp2 bexp3
%type <assignment_type> assignment
%type <repeat_type> repeat_start repeat_end

%start program

%%

program : sentence_list { end_compilation(); }

sentence_list :
  sentence_list sentence
  | sentence
  | repeat_end
  | sentence_list repeat_end

repeat_start
  : REPEAT arithmetic_expression DO NEWLINE_TKN {
    handle_repeat_start(&$$, $2);
  }

repeat_end
  : repeat_start sentence_list DONE NEWLINE_TKN {
    handle_repeat_loop(&$$, $1);
  }

sentence :
  boolean_expression NEWLINE_TKN { if (parser_verbose) print_expression($1); }
  | assignment { if (parser_verbose) print_assignment($1); }
  | representation_mode NEWLINE_TKN

representation_mode :
  BIN { repmode = BIN_MODE; }
  | OCT { repmode = OCT_MODE; }
  | DEC { repmode = DEC_MODE; }
  | HEX { repmode = HEX_MODE; }

assignment : ID_TKN ASSIGN expression NEWLINE_TKN
{
  if ($1.type == UNKNOWN_TYPE || $1.type == $3.type)
  {
    $1.type = $3.type;
    $1.value = $3.value;
  }
  if ($1.type != UNKNOWN_TYPE && $1.type != $3.type)
    yyerror("Different type assignation.\n");
  update_id(&$1);
  compile_assignation($1, $3);
}

expression :
  boolean_expression { $$.type = $1.type; $$.value = $1.value; }

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
  exp2 POWER exp3 { power(&$$, $1, $3); }
  | SIN exp3 { sin_funct(&$$, $2); }
  | COS exp3 { cos_funct(&$$, $2); }
  | TAN exp3 { tan_funct(&$$, $2); }
  | LEN exp3 { my_strlen(&$$, $2); }
  | SUBSTR exp3 exp3 exp3 { my_substr(&$$, $2, $3, $4); }
  | exp3 {$$.type = $1.type; $$.value = $1.value; }

exp3 :
  OPENPAR exp CLOSEDPAR { $$.type = $2.type; $$.value = $2.value; }
  | INTEGER_TKN { $$.type = INT_TYPE; $$.value = $1; }
  | FLOAT_TKN { $$.type = FLOAT_TYPE; $$.value = $1; }
  | STRING_TKN { $$.type = STRING_TYPE; $$.value = $1; }
  | ID_TKN { get_id(&$1); assign_expression(&($$), $1.type, $1.value); }

boolean_expression :
  bexp { $$.type = $1.type; $$.value = $1.value; }

bexp :
  bexp1 OR bexp { or(&$$, $1, $3); }
  | bexp1 { $$.type = $1.type; $$.value = $1.value; }

bexp1 :
  bexp2 AND bexp1 { and(&$$, $1, $3); }
  | bexp2 { $$.type = $1.type; $$.value = $1.value; }

bexp2 :
  NOT bexp3 { not(&$$, $2); }
  | bexp3 { $$.type = $1.type; $$.value = $1.value; }

bexp3 :
  arithmetic_expression OPREL arithmetic_expression { compare(&$$, $1, $2, $3); }
  | TRUE { $$.type = BOOLEAN_TYPE; $$.value = $1; }
  | FALSE { $$.type = BOOLEAN_TYPE; $$.value = $1; }
  | arithmetic_expression { $$.type = $1.type; $$.value = $1.value; }

%%

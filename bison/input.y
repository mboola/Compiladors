%{

  #include <stdlib.h>
  #include "parser_operations.h"
  #include "yyfunctions.h"
  #include "compiler_flags.h"
  #include "helper_functions.h"
  #include "compiler.h"
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
    int m_val;
    t_id id;
    t_expression expression_type;
    t_oprel oprel;
    t_assignment assignment_type;
    t_repeat repeat_type;
    t_if if_type;
    t_while while_type;
    t_do do_type;
    t_for_range for_range_type;
    void *no_value;
}

%define parse.error verbose

%token <integer> INTEGER_TKN
%token <real> FLOAT_TKN
%token <string> STRING_TKN
%token <boolean> TRUE FALSE
%token <id> ID_TKN

/* Arithmetic operations */
%token <no_value> ADDITION SUBSTRACTION POWER MULTIPLICATION DIVISION MOD SIN COS TAN
/* Representation modes */
%token <no_value> OCT BIN HEX DEC RIC
/* Boolean operations */
%token <no_value> NOT AND OR
/* String operations */
%token <no_value> LEN SUBSTR
/* Conditional tokens */
%token <no_value> IF THEN FI ELSE SWITCH FSWITCH CASE BREAK
/* Iterative tokens */
%token <no_value> REPEAT DONE DO WHILE UNTIL FOR IN RANGE
/* Other */
%token <no_value> OPENPAR CLOSEDPAR ASSIGN NEWLINE_TKN
%token <oprel> OPREL

%type <m_val> M

%type <no_value> program sentence representation_mode sentence_list
%type <expression_type> expression arithmetic_expression exp exp1 exp2 exp3 exp4
%type <expression_type> boolean_expression bexp bexp1 bexp2 bexp3 bexp4
%type <assignment_type> assignment
/* Repeat */
%type <repeat_type> repeat_start
%type <no_value> repeat_end
/* While */
%type <while_type> while_start while_before_bool
%type <no_value> while_end
/* Do until */
%type <do_type> do_until_start
%type <no_value> do_until_end
/* If */
%type <if_type> if_start if_else
%type <no_value> if_end if_else_end
/* For range */
%type <for_range_type> for_range_start
%type <no_value> for_range_end

%start program

%%

program : sentence_list { end_compilation(); }

repeat_start :
  REPEAT arithmetic_expression DO NEWLINE_TKN {
    handle_repeat_start(&$$, $2);
  }

repeat_end :
  repeat_start sentence_list DONE NEWLINE_TKN {
    handle_repeat_loop($1);
  }

while_before_bool :
  WHILE {
    initialize_while(&$$);
  }

while_start :
  while_before_bool boolean_expression DO NEWLINE_TKN {
    update_while(&$$, $1, $2);
  }

while_end :
  while_start sentence_list DONE NEWLINE_TKN {
    end_while($1);
  }

do_until_start :
  DO NEWLINE_TKN {
    initialize_do(&$$);
  }

do_until_end :
  do_until_start sentence_list UNTIL boolean_expression NEWLINE_TKN {
    end_do($1, $4);
  }

if_start :
  IF boolean_expression THEN NEWLINE_TKN {
    initialize_if(&$$, $2);
  }

if_end :
  if_start sentence_list FI NEWLINE_TKN {
    end_if($1);
  }

if_else :
  if_start sentence_list ELSE NEWLINE_TKN {
    initialize_else(&$$, $1);
  }

if_else_end :
  if_else sentence_list FI NEWLINE_TKN {
    end_else($1);
  }

for_range_start :
  FOR ID_TKN IN arithmetic_expression RANGE arithmetic_expression DO NEWLINE_TKN {
    initialize_for_range(&$$, $2, $4, $6);
  }

for_range_end :
  for_range_start sentence_list DONE NEWLINE_TKN {
    end_for_range($1);
  }

sentence_list :
  sentence_list sentence
  | sentence

sentence :
  expression NEWLINE_TKN {
    print_expression($1);
    compile_expression($1);
  }
  | assignment { print_assignment($1); }
  | representation_mode NEWLINE_TKN
  | NEWLINE_TKN
  | repeat_end
  | if_end
  | if_else_end
  | while_end
  | do_until_end
  | for_range_end

representation_mode :
  BIN { repmode = BIN_MODE; }
  | OCT { repmode = OCT_MODE; }
  | DEC { repmode = DEC_MODE; }
  | HEX { repmode = HEX_MODE; }
  | RIC { repmode = RICARDO_MODE; }

assignment : ID_TKN ASSIGN expression NEWLINE_TKN {
    if ($1.type != UNKNOWN_TYPE && $1.type != $3.type)
      yyerror("Different type assignation.\n");
    
    $1.type = $3.type;
    $1.value = $3.value;
    update_id(&$1);
    compile_assignation($1, $3);
  }

expression :
  boolean_expression {
    assign_expression(&($$), $1);
  }

arithmetic_expression :
  exp {
    assign_expression(&($$), $1);
  }

exp :
  exp1 ADDITION exp {
    addition(&$$, $1, $3);
  }
  | exp1 SUBSTRACTION exp {
    substraction(&$$, $1, $3);
  }
  | exp1 {
    assign_expression(&($$), $1);
  }

exp1 :
  SUBSTRACTION exp2 {
    negate(&$$, $2);
  }
  | ADDITION exp2 {
    assign_expression(&($$), $2);
  }
  | exp2 {
    assign_expression(&($$), $1);
  }

exp2 :
  exp3 MULTIPLICATION exp2 {
    multiplication(&$$, $1, $3);
  }
  | exp3 DIVISION exp2 {
    division(&$$, $1, $3);
  }
  | exp3 MOD exp2 {
    modulation(&$$, $1, $3);
  }
  | exp3 {
    assign_expression(&($$), $1);
  }

exp3 :
  exp4 POWER exp3 {
    power(&$$, $1, $3);
  }
  | SIN exp4 {
    sin_funct(&$$, $2);
  }
  | COS exp4 {
    cos_funct(&$$, $2);
  }
  | TAN exp4 {
    tan_funct(&$$, $2);
  }
  | LEN exp4 {
    my_strlen(&$$, $2);
  }
  | SUBSTR exp4 exp4 exp4 {
    my_substr(&$$, $2, $3, $4);
  }
  | exp4 {
    assign_expression(&($$), $1);
  }

exp4 :
  OPENPAR expression CLOSEDPAR {
		assign_expression(&($$), $2);
	}
	| INTEGER_TKN {
		initialize_expression(&($$), INT_TYPE, $1, 0, NULL);
	}
	| FLOAT_TKN {
		initialize_expression(&($$), FLOAT_TYPE, $1, 0, NULL);
	}
	| STRING_TKN {
		initialize_expression(&($$), STRING_TYPE, $1, 0, NULL);
	}
	| ID_TKN {
		get_id(&$1);
		initialize_expression(&($$), $1.type, $1.value, 0, $1.lexema);
	}
  
M:
  {
    $$ = instructions_inputed;
  }

boolean_expression :
  bexp {
    assign_expression(&($$), $1);
  }

bexp :
  bexp1 OR M bexp {
    or(&$$, $1, $3, $4);
  }
  | bexp1 {
    assign_expression(&($$), $1);
  }

bexp1 :
  bexp2 AND M bexp1 {
    and(&$$, $1, $3, $4);
  }
  | bexp2 {
    assign_expression(&($$), $1);
  }

bexp2 :
  NOT bexp3 {
    not(&$$, $2);
  }
  | bexp3 {
    assign_expression(&($$), $1);
  }

bexp3 :
  bexp4 OPREL bexp3 {
    compare(&$$, $1, $2, $3);
  }
  | bexp4 {
    assign_expression(&($$), $1);
  }

bexp4 :
  arithmetic_expression {
    assign_expression(&($$), $1);
  }
  | TRUE {
    $$.type = BOOLEAN_TYPE; $$.value = $1;
  }
  | FALSE {
    $$.type = BOOLEAN_TYPE; $$.value = $1;
  }

%%

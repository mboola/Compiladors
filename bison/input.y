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
    t_id id;
    t_expression expression_type;
    t_oprel oprel;
    t_assignment assignment_type;
    t_repeat repeat_type;
    t_if if_type;
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

%type <no_value> program sentence representation_mode sentence_list
%type <expression_type> expression arithmetic_expression exp exp1 exp2 exp3 exp4
%type <expression_type> boolean_expression bexp bexp1 bexp2 bexp3 bexp4
%type <assignment_type> assignment
/* Repeat */
%type <repeat_type> repeat_start
%type <no_value> repeat_end
/* While */
%type <no_value> while_start
%type <no_value> while_end
/* Do until */
%type <no_value> do_until_start
%type <no_value> do_until_end
/* If */
%type <if_type> if_start
%type <no_value> if_end if_else_end

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

while_start :
  WHILE boolean_expression DO NEWLINE_TKN {
    
  }

while_end :
  while_start sentence_list DONE NEWLINE_TKN {
    
  }

do_until_start :
  DO NEWLINE_TKN sentence_list {

  }

do_until_end :
  do_until_start UNTIL boolean_expression NEWLINE_TKN {

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

  }

if_else_end :
  if_else sentence_list FI NEWLINE_TKN {

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

expression : boolean_expression { $$.type = $1.type; $$.value = $1.value; }

arithmetic_expression :
  exp { 
    assign_expression(&($$), $1.type, $1.value, $1.reg, $1.lexema);
  }

exp :
  exp1 ADDITION exp {
    addition(&$$, $1, $3);
  }
  | exp1 SUBSTRACTION exp { substraction(&$$, $1, $3); }
  | exp1 { $$.type = $1.type; $$.value = $1.value; }

exp1 :
  SUBSTRACTION exp2 {
    negate(&$$, $2);
  }
  | ADDITION exp2 { $$.type = $2.type; $$.value = $2.value; }
  | exp2 {
    assign_expression(&($$), $1.type, $1.value, $1.reg, $1.lexema);
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
    assign_expression(&($$), $1.type, $1.value, $1.reg, $1.lexema);
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
    assign_expression(&($$), $1.type, $1.value, $1.reg, $1.lexema);
  }

exp4 :
  OPENPAR expression CLOSEDPAR {
		assign_expression(&($$), $2.type, $2.value, $2.reg, $2.lexema);
	}
	| INTEGER_TKN {
		assign_expression(&($$), INT_TYPE, $1, 0, NULL);
	}
	| FLOAT_TKN {
		assign_expression(&($$), FLOAT_TYPE, $1, 0, NULL);
	}
	| STRING_TKN {
		assign_expression(&($$), STRING_TYPE, $1, 0, NULL);
	}
	| ID_TKN {
		get_id(&$1);
		assign_expression(&($$), $1.type, $1.value, 0, $1.lexema);
	}
  

boolean_expression :
  bexp {
    assign_boolean_expression(&($$), $1.type, $1.value, $1.reg, $1.lexema);
  }

bexp :
  bexp1 OR bexp {
    or(&$$, $1, $3);
  }
  | bexp1 {
    assign_boolean_expression(&($$), $1.type, $1.value, $1.reg, $1.lexema);
  }

bexp1 :
  bexp2 AND bexp1 { and(&$$, $1, $3); }
  | bexp2 {
    assign_boolean_expression(&($$), $1.type, $1.value, $1.reg, $1.lexema);
  }

bexp2 :
  NOT bexp3 { not(&$$, $2); }
  | bexp3 {
    assign_boolean_expression(&($$), $1.type, $1.value, $1.reg, $1.lexema);
  }

bexp3 :
  bexp4 OPREL bexp3 { compare(&$$, $1, $2, $3); }
  | bexp4 {
    assign_boolean_expression(&($$), $1.type, $1.value, $1.reg, $1.lexema);
   }

bexp4 :
  arithmetic_expression { $$.type = $1.type; $$.value = $1.value; }
  | TRUE { $$.type = BOOLEAN_TYPE; $$.value = $1; }
  | FALSE { $$.type = BOOLEAN_TYPE; $$.value = $1; }

%%

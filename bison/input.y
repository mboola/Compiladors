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
    t_id id;
    t_expression expression_type;
    t_assignment assignment_type;
    t_repeat repeat_type;
    void *no_value;
}

%define parse.error verbose

%token <integer> INTEGER_TKN
%token <real> FLOAT_TKN
%token <id> ID_TKN
%token <no_value> NEWLINE_TKN ASSIGN OPENPAR CLOSEDPAR ADDITION SUBSTRACTION POWER MULTIPLICATION DIVISION MOD SIN COS TAN OCT BIN HEX DEC RIC REPEAT DONE DO

%type <no_value> program sentence representation_mode sentence_list repeat_end
%type <expression_type> expression arithmetic_expression exp exp1 exp2 exp3 exp4
%type <assignment_type> assignment
%type <repeat_type> repeat_start

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

sentence_list :
  sentence_list sentence
  | sentence
  | repeat_end
  | sentence_list repeat_end

sentence :
  expression NEWLINE_TKN {
    print_expression($1);
    compile_expression($1);
  }
  | assignment { print_assignment($1); }
  | representation_mode NEWLINE_TKN
  | NEWLINE_TKN

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

expression : arithmetic_expression { $$.type = $1.type; $$.value = $1.value; }

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
  | exp4 {
    assign_expression(&($$), $1.type, $1.value, $1.reg, $1.lexema);
  }

exp4 :
  OPENPAR exp CLOSEDPAR {
		assign_expression(&($$), $2.type, $2.value, $2.reg, $2.lexema);
	}
	| INTEGER_TKN {
		assign_expression(&($$), INT_TYPE, $1, 0, NULL);
	}
	| FLOAT_TKN {
		assign_expression(&($$), FLOAT_TYPE, $1, 0, NULL);
	}
	| ID_TKN {
		get_id(&$1);
		assign_expression(&($$), $1.type, $1.value, 0, $1.lexema);
	}

%%

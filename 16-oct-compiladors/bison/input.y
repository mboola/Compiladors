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
    struct {
        char *lexema;
        int lenght;
        int line;
        value_info id_val;
    } ident;
    int enter;
    float real;
    value_info expr_val;
    void *sense_valor;
}

%token <sense_valor> ASSIGN ENDLINE
%token <enter> INTEGER
%token <ident> ID

%type <sense_valor> programa
%type <expr_val> expressio

%start programa

%%

programa : expressio {
             fprintf(yyout, "programa -> expressio :\n  expressio = '%s'\n", value_info_to_str($1));
           }

expressio : ID ASSIGN INTEGER ENDLINE  {
              fprintf(yyout, "ID: %s pren per valor: %d\n",$1.lexema, $3);
              $$.val_type = INT_TYPE;
              $$.val_int = $3;
            }

%%
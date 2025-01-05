#ifndef DATA_TYPES_H
# define DATA_TYPES_H

# include "linked_list.h"

typedef enum {
	UNKNOWN_TYPE,
	INT_TYPE,
	FLOAT_TYPE,
	STRING_TYPE,
	BOOLEAN_TYPE
}	data_type;

typedef enum {
	LESEQ,
	BIGEQ,
	NOTEQ,
	LESSER,
	BIGGER,
	EQUAL
}	oprel_type;

// Struct used to store the possible values
// of an id.
//	->lexema stores the 'name' of the variable
//	->type is an enum of the type of the variable
//	->value is a ptr with the value
// NOTE: a cast is done based on the type
typedef struct {
	char *lexema;
	data_type type;
	void *value;
}	t_id;

// Struct that stores the data of an expression
typedef struct {
	data_type type;
	void *value;
	char *lexema;
	int reg;
	t_list *true_list; // stores list of lines to fill gotos
	t_list *false_list; // same as above
}	t_expression;

// Struct that defines a relational operation
typedef struct {
	oprel_type type;
}	t_oprel;

// Struct that defines the data used in an assigments
// TODO : Im pretty sure it wont be used
typedef struct {
	char *name;
}	t_assignment;

typedef struct {
	data_type type;
	char *update;
	char *jump;
}	t_repeat;


// TODO: convert these two into one
typedef struct {
	t_list *instructions;
	t_expression expression;
	int	true_section_line;
	int	false_section_line;
}	t_if;

typedef struct {
	t_list *instructions;
	t_expression expression;
	int	true_section_line;
	int	false_section_line;
	int current_instructions;
}	t_while;

#endif

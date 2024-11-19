#ifndef DATA_TYPES_H
# define DATA_TYPES_H

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
}	t_expression;

// Struct that defines a relational operation
typedef struct {
	oprel_type type;
}	t_oprel;

// Struct that defines the data used in an assigments
// TODO : Im pretty sure it wont be used
typedef struct {
	char *name;
	data_type type;
}	t_assignment;

#endif

#ifndef FIELD_H
#define FIELD_H

#include <stdio.h>
#include <stdlib.h>

#define SQUARE 0
#define TOR 1
#define LIVING 1
#define DEAD 0

typedef struct {
	unsigned int flat;
	unsigned int table_size;

	char **current_table;
	char **future_table;
} field;

void field_print(field *temp_field);
unsigned int field_next_gen(field *temp_field);
void field_random_gen(field *temp_field);
field *field_read_template(field *temp_field, FILE *stream);
void field_clear(field *temp_field);
field *field_create(unsigned int field_size);

#endif
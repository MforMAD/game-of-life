#include <field.h>

static unsigned int field_endgame_check(field *temp_field);
static unsigned int field_neighbors_count(field *temp_field, unsigned int h_pos, unsigned int w_pos);
static void table_delete(char **temp_table, unsigned int table_size);

void field_print(field *temp_field)
{
	unsigned int i;
	unsigned int j;

	for (i = 0; i < temp_field->table_size; i++) {
		for (j = 0; j < temp_field->table_size; j++) {
			printf("%c", temp_field->current_table[i][j] ? '#' : ' ');
		}

		printf("\n");
	}
}
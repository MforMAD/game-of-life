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


static unsigned int field_endgame_check(field *temp_field)
{
	unsigned int i;
	unsigned int j;
	unsigned int flag1;
	unsigned int flag2;

	for (i = 0, flag1 = 0, flag2 = 0; i < temp_field->table_size; i++) {
		for (j = 0; j < temp_field->table_size; j++) {
			if (temp_field->future_table[i][j] == LIVING) {
				flag1++;
			}

			if (temp_field->future_table[i][j] != temp_field->current_table[i][j]) {
				flag2++;
			}
		}
	}
	
	if (!flag1 || !flag2) {
		return 1;
	} else {
		return 0;
	}
}


unsigned int field_next_gen(field *temp_field)
{
	unsigned int i;
	unsigned int j;
	unsigned int flag;
	unsigned int neighbors;

	for (i = 0; i < temp_field->table_size; i++) {
		for (j = 0; j < temp_field->table_size; j++) {
			neighbors = field_neighbors_count(temp_field, i, j);

			if (temp_field->current_table[i][j] == DEAD) {
				temp_field->future_table[i][j] = (neighbors == 3) ? LIVING : DEAD;
			} else {
				temp_field->future_table[i][j] = (neighbors == 2 || neighbors == 3) ? LIVING : DEAD;
			}
		}
	}

	flag = field_endgame_check(temp_field);

	for (i = 0; i < temp_field->table_size; i++) {
		for (j = 0; j < temp_field->table_size; j++) {
			temp_field->current_table[i][j] = temp_field->future_table[i][j];
		}
	}

	return flag;
}
#include <field.h>

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


unsigned int field_endgame_check(field *temp_field)
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


unsigned int field_neighbors_count(field *temp_field, unsigned int h_pos, unsigned int w_pos)
{
	int i;
	int j;
	int x;
	int y;
	unsigned int neighbors;

	if (temp_field->flat) {
		for (neighbors = 0, i = -1; i <= 1; i++) {
			for (j = -1; j <= 1; j++) {
				x = (i + h_pos + temp_field->table_size) % temp_field->table_size;
				y = (j + w_pos + temp_field->table_size) % temp_field->table_size;	

				neighbors += temp_field->current_table[x][y];	
			}
		}
	} else {
		for (neighbors = 0, i = -1; i <= 1; i++) {
			for (j = -1; j <= 1; j++) {
				x = i + h_pos;
				y = j + w_pos;

				if (x >= 0 && x < temp_field->table_size && y >= 0 && y < temp_field->table_size) {
					neighbors += temp_field->current_table[x][y];
				}
			}
		}
	}

	neighbors -= temp_field->current_table[h_pos][w_pos];

	return neighbors;
}


void field_random_gen(field *temp_field)
{
	unsigned int i;
	unsigned int j;

	for (i = 0; i < temp_field->table_size; i++) {
		for (j = 0; j < temp_field->table_size; j++) {
			temp_field->current_table[i][j] = rand() % 2;
		}
	}
}


field *field_read_template(field *temp_field, FILE *stream)
{
	char buf;

	unsigned int i;
	unsigned int j;
	unsigned int temp_flat;
	unsigned int temp_size;

	fscanf(stream, "%d %d", &temp_flat, &temp_size);

	if (temp_field != NULL) {
		if (temp_field->table_size != temp_size) {
			temp_field = field_delete(temp_field);
		}
	}
	
	temp_field = field_create(temp_size);

	temp_field->flat = temp_flat;

	for (i = 0; i < temp_field->table_size; i++) {
		for (j = 0; j < temp_field->table_size; j++) {
			do {
				buf = fgetc(stream);
			} while(buf != '0' && buf != '1');

			temp_field->current_table[i][j] = (buf == '1') ? 1 : 0;
		}
	}

	return temp_field;
}


void field_clear(field *temp_field)
{
	unsigned int i;
	unsigned int j;

	for (i = 0; i < temp_field->table_size; i++) {
		for (j = 0; j < temp_field->table_size; j++) {
			temp_field->current_table[i][j] = 0;
			temp_field->future_table[i][j] = 0;
		}
	}
}


field *field_create(unsigned int field_size)
{
	unsigned int i;

	field *temp_field;

	temp_field = malloc(sizeof(field));

	temp_field->table_size = field_size;

	temp_field->flat = SQUARE;

	temp_field->current_table = malloc(field_size * sizeof(char*));
	temp_field->future_table = malloc(field_size * sizeof(char*));

	for (i = 0; i < field_size; i++) {
		temp_field->current_table[i] = malloc(field_size * sizeof(char));
		temp_field->future_table[i] = malloc(field_size * sizeof(char));
	}

	field_clear(temp_field);

	return temp_field;
}


void table_delete(char **temp_table, unsigned int table_size)
{
	unsigned int i;

	for (i = 0; i < table_size; i++) {
		free(temp_table[i]);
	}

	free(temp_table);
}


field *field_delete(field *temp_field)
{
	table_delete(temp_field->current_table, temp_field->table_size);
	table_delete(temp_field->future_table, temp_field->table_size);

	free(temp_field);

	return NULL;
}


void table_set(field *temp_field, char **temp_table, unsigned int flag)
{
	unsigned int i;
	unsigned int j;

	if (flag) {
		for (i = 0; i < temp_field->table_size; i++) {
			for (j = 0; j < temp_field->table_size; j++) {
				temp_field->current_table[i][j] = temp_table[i][j];
			}
		}
	} else {
		for (i = 0; i < temp_field->table_size; i++) {
			for (j = 0; j < temp_field->table_size; j++) {
				temp_field->future_table[i][j] = temp_table[i][j];
			}
		}
	}
}
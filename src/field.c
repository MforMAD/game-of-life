#include <field.h>

static unsigned int field_endgame_check(field *temp_field);
static unsigned int field_neighbors_count(field *temp_field, unsigned int h_pos, unsigned int w_pos);
static void table_delete(char **temp_table, unsigned int table_size);
#include <game.h>

void first_gen(char table[T_WIDTH][T_HEIGHT])
{
	char c[2] = {LIVING, DEAD};

	unsigned int i;
	unsigned int j;

	for (j = 0; j < T_HEIGHT; j++) {
		for (i = 0; i < T_WIDTH; i++) {
			table[i][j] = c[rand() % 2];
		}
	}
}


unsigned int neighbor_count(char table[T_WIDTH][T_HEIGHT], unsigned int height, unsigned int width)
{
	unsigned int count = 0;

	if (table[width][!((height + 1) == T_HEIGHT) * (height + 1)] == LIVING) {
		count++;
	}

	if (table[((width == 0) * (T_WIDTH - 1)) + (!(width == 0) * (width - 1))][!((height + 1) == T_HEIGHT) * (height + 1)] == LIVING) {
		count++;
	}

	if (table[!((width + 1) == T_WIDTH) * (width + 1)][!((height + 1) == T_HEIGHT) * (height + 1)] == LIVING) {
		count++;
	}

	if (table[width][((height == 0) * (T_HEIGHT - 1)) + (!(height == 0) * (height - 1))] == LIVING) {
		count++;
	}

	if (table[!((width + 1) == T_WIDTH) * (width + 1)][((height == 0) * (T_HEIGHT - 1)) + (!(height == 0) * (height - 1))] == LIVING) {
		count++;
	}

	if (table[((width == 0) * (T_WIDTH - 1)) + (!(width == 0) * (width - 1))][((height == 0) * (T_HEIGHT - 1)) + (!(height == 0) * (height - 1))] == LIVING) {
		count++;
	}

	if (table[((width == 0) * (T_WIDTH - 1)) + (!(width == 0) * (width - 1))][height] == LIVING) {
		count++;
	}

	if (table[!((width + 1) == T_WIDTH) * (width + 1)][height] == LIVING) {
		count++;
	}

	return count;
}


unsigned int endgame_check(char past_table[T_WIDTH][T_HEIGHT], char future_table[T_WIDTH][T_HEIGHT])
{
	static char past_past_table[T_WIDTH][T_HEIGHT] = {{0}};

	unsigned int i;
	unsigned int j;
	unsigned int f;

	for (f = 0, j = 0; j < T_HEIGHT; j++) {
		for (i = 0; i < T_WIDTH; i++) {
			if (future_table[i][j] == LIVING) {
				f++;
			}
		}
	}

	if (!f) {
		return 1;
	}

	for (f = 0, j = 0; j < T_HEIGHT; j++) {
		for (i = 0; i < T_WIDTH; i++) {
			if (future_table[i][j] != past_table[i][j]) {
				f++;
			}
		}
	}

	if (!f) {
		return 1;
	}

	for (f = 0, j = 0; j < T_HEIGHT; j++) {
		for (i = 0; i < T_WIDTH; i++) {
			if (past_past_table[i][j] != future_table[i][j]) {
				f++;
			}
		}
	}

	if (!f) {
		return 1;
	}

	for (f = 0, j = 0; j < T_HEIGHT; j++) {
		for (i = 0; i < T_WIDTH; i++) {
			past_past_table[i][j] = past_table[i][j];
		}
	}

	return 0;
}


unsigned int next_gen(char past_table[T_WIDTH][T_HEIGHT])
{
	char future_table[T_WIDTH][T_HEIGHT];

	unsigned int i;
	unsigned int j;
	unsigned int neigh_cnt;
	unsigned int flag;

	for (j = 0; j < T_HEIGHT; j++) {
		for (i = 0; i < T_WIDTH; i++) {
			neigh_cnt = neighbor_count(past_table, j, i);

			if (past_table[i][j] == DEAD) {
				if (neigh_cnt == 3) {
					future_table[i][j] = LIVING;
				} else {
					future_table[i][j] = DEAD;
				}
			} else {
				if (neigh_cnt == 2 || neigh_cnt == 3) {
					future_table[i][j] = LIVING;
				} else {
					future_table[i][j] = DEAD;
				}
			}
		}
	}

	flag = endgame_check(past_table, future_table);

	for (j = 0; j < T_HEIGHT; j++) {
		for (i = 0; i < T_WIDTH; i++) {
			past_table[i][j] = future_table[i][j];
		}
	}

	return flag;
}

void print_table(char table[T_WIDTH][T_HEIGHT])
{
	unsigned int i;
	unsigned int j;

	for (j = 0; j < T_HEIGHT; j++) {
		for (i = 0; i < T_WIDTH; i++) {
			printf("%c", table[i][j]);
		}
		printf("\n");
	}
}


void clear_table(char table[T_WIDTH][T_HEIGHT])
{
	unsigned int i;
	unsigned int j;

	for (j = 0; j < T_HEIGHT; j++) {
		for (i = 0; i < T_WIDTH; i++) {
			table[i][j] = DEAD;
		}
	}
}

void read_table(char table[T_WIDTH][T_HEIGHT], FILE *input_file)
{
	unsigned int i;
	unsigned int j;
	char temp;

	for (j = 0; j < T_HEIGHT; j++) {
		for (i = 0; i < T_WIDTH; i++) {
			fscanf(input_file, "%c", &temp);
			table[i][j] = (temp == '1') ? '#' : ' ';
		}

		fgetc(input_file);
	}
}
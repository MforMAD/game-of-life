#include <time.h>
#include <stdlib.h>

#define T_HEIGHT 10
#define T_WIDTH T_HEIGHT * 2
#define LIVING '#'
#define DEAD ' '

void first_gen(char table[T_WIDTH][T_HEIGHT]);
unsigned int neighbor_count(char table[T_WIDTH][T_HEIGHT], unsigned int height, unsigned int width);
unsigned int endgame_check(char past_table[T_WIDTH][T_HEIGHT], char future_table[T_WIDTH][T_HEIGHT]);
unsigned int next_gen(char past_table[T_WIDTH][T_HEIGHT]);
void print_table(char table[T_WIDTH][T_HEIGHT]);
void clear_table(char table[T_WIDTH][T_HEIGHT]);

int main()
{
	srand(time(NULL));
	return 0;
}

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
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <game.h>

int main()
{
	srand(time(NULL));
	char table[T_WIDTH][T_HEIGHT];
	int status;

	clear_table(table);
/*
	FILE *in = fopen("/home/dmitriy/glife/game-of-life/src/test.txt", "r+");

	read_table(table, in);

	fclose(in);
*/
	first_gen(table);

	system("resize -s 10 20");
	system("clear");

	do {
		print_table(table);
		usleep(1000 * 100);
	} while (!next_gen(table));

	print_table(table);

	return 0;
}

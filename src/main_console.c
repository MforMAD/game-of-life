#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <game.h>
#include <menu.h>

int main(int argc, char *argv[])
{
	srand(time(NULL));

	int status;
	char table[T_WIDTH][T_HEIGHT];

	status = main_menu();
	if (status == 1) {
		clear_table(table);
		first_gen(table);

		system("resize -s 10 20");
		system("clear");

		do {
			print_table(table);
			usleep(1000 * 100);
		} while (!next_gen(table));

		print_table(table);
	}
	if (status == 0)
		help();
	if (status == -1)
		return 0;
	return 0;
}
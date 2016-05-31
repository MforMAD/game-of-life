#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <game.h>

int main()
{
	int GTK = 0; //We check, Does this machine have the GTK library. If true we run interface, else we show console version
	srand(time(NULL));
	char table[T_WIDTH][T_HEIGHT];

	if (GTK) {

		return 0;
	}

	else {
		int status;

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

		if (status == -1)
			return 0;
		return 0;
	}

}

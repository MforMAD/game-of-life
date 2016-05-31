#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <game.h>

char table[T_WIDTH][T_HEIGHT];

int main(int argc, char *argv[])
{
	int GTK = 1; //We check, Does this machine have the GTK library. If true we run interface, else we show console version
	srand(time(NULL));

	if (GTK) {
		int status;
		struct base basement;

		basement.app = gtk_application_new("game.of.life", G_APPLICATION_FLAGS_NONE);
		g_signal_connect(basement.app, "activate", G_CALLBACK(start), &basement);
		status = g_application_run(G_APPLICATION(basement.app), argc, argv);
		g_object_unref(basement.app);

		return status;;
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

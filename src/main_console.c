#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <menu.h>
#include <field.h>

int main(int argc, char *argv[])
{
	srand(time(NULL));

	int status, *count;
	char **string;
	
	field *level = NULL;
	unsigned int default_size = 20;
	while (1)
	{
		status = main_menu();
		if (status == 1) {
			if (level == NULL)
				level = field_create(default_size);
		
			field_random_gen(level);

			system("resize -s 40 80");
			system("clear");

			do {
				field_print(level);
				usleep(1000 * 100);
			} while (!field_next_gen(level));

			field_print(level);
		}
		if (status == 0)
			help();
		if (status == -1)
			string = search_templates(count);
		if (status == -2)
			return 0;
	}
	return 0;
}
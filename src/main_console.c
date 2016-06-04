#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <menu.h>
#include <field.h>
#icnlude <template.h>

int main(int argc, char *argv[])
{
	srand(time(NULL));

	int status;
	int count;
	
	unsigned int i;
	unsigned int delay = 100;
	unsigned int default_size;
	unsigned int template_number;
	
	char buf[20] = "./tpl/";
	char resize_buf[20] = "resize -s ";
	char size_buf[20];
	char **string;
	
	FILE *template;
	
	field *level;
	
	default_size = 20;
	level = NULL;
	
	system("resize -s 24 96");
		
	while (1)
	{
		system("clear");
		status = main_menu();
				switch (status) {
				case 0 : 
					system("clear");
					help();
					getchar();
					getchar();
					break;
				case 1 :
					if (level == NULL) {
						level = field_create(default_size);
					}
		
					field_random_gen(level);

					sprintf(size_buf, "%d %d", default_size, default_size);
	
					resize_buf[10] = '\0';


					strcat(resize_buf, size_buf);

					system(resize_buf);
					system("clear");

					do {
						field_print(level);
						usleep(delay * 100);
					} while (!field_next_gen(level));

					sprintf(size_buf, "%d %d", 24, 96);

					resize_buf[10] = '\0';

					strcat(resize_buf, size_buf);

					system(resize_buf);
					system("clear");

					field_print(level);

					break;
				case -1 :
					system("clear");

					string = search_templates(&count);

					for (i = 0; i < count; i++) {
						printf("[%d] %s\n", i + 1, string[i]);
					}
				
					scanf("%d", &template_number);

					template_number--;

					strcat(buf, string[template_number]);

					strcat(buf, ".tpl");

					fflush(stdout);

					template = fopen(buf, "r");

					level = field_read_template(level, template);

					fclose(template);

					buf[6] = '\0';

					sprintf(size_buf, "%d %d", level->table_size, level->table_size);

					resize_buf[10] = '\0';

					strcat(resize_buf, size_buf);

					system(resize_buf);
					system("clear");

					do {
						field_print(level);
						usleep(delay * 100);
					} while (!field_next_gen(level));

					system("resize -s 26 90");
					system("clear");

					field_print(level);

					getchar();
					getchar();

					break;
				case -2 :
					return 0;
					break;
		}

	}
	return 0;
}
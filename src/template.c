#include "template.h"

// Function search for files "*.tpl" in 'search_dir', write name of files without suff in 'result', returns count of names
int search_templates(char *search_dir, char **result)
{
	char cmd[100] = "find ";
	char str[20];

	FILE *temp_file;

	int i;

	strcat(cmd, search_dir);

	strcat(cmd, " -name \"*.tpl\" ");

	strcat(cmd, "-exec basename {} .tpl \\;");

	strcat(cmd, " > tmp_file");

	printf("'%s'\n", cmd);

	system(cmd);

	temp_file = fopen("./tmp_file", "r");

	for (i = 0; !feof(temp_file); i++) {
		fscanf(temp_file, "%s", str);

		result[i] = strdup(str);
	}

	fclose(temp_file);

	system("rm ./tmp_file");

	return i - 1;
}
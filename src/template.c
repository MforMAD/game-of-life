#include <template.h>

// Function search for files "*.tpl" in 'search_dir', write file count in file_count, return array of strings(filenames)
char **search_templates(int *file_count)
{
	char cmd[100] = "find ";
	char str[20];
	char **result;

	FILE *temp_file;

	int i;

	strcat(cmd, "./tpl");

	strcat(cmd, " -name \"*.tpl\" ");

	strcat(cmd, "-exec basename {} .tpl \\;");

	strcat(cmd, " > tmp_file");

	system(cmd);

	temp_file = fopen("./tmp_file", "r");

	for (i = 0; !feof(temp_file); i++) {
		fscanf(temp_file, "%s", str);
	}

	*file_count = i - 1;

	result = (char**) malloc(*file_count * sizeof(char*));

	rewind(temp_file);

	for (i = 0; i < *file_count; i++) {
		fscanf(temp_file, "%s", str);

		result[i] = strdup(str);
	}

	fclose(temp_file);

	system("rm ./tmp_file");

	return result;
}
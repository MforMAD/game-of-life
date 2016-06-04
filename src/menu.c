#include "menu.h"

int main_menu()
{
        char ch;
        printf("Вас Приветствует игра <Жизнь>!\nВыбрать пункт меню вы можете с помощью кнопок 1 - 3 на клавиатуре, а затем нажать Enter\n1.Новая игра\n2.Помощь\n3.Выход\n");
        scanf("%c", &ch);
        switch (ch)
        {
                case '1':
                        return 1;
                        break;
                case '2':
                        return 0;
                        break;
                case '3':
                        return -1;
                        break;
        }
        return -1;
}

void help()
{
	FILE *f;
	char *string;
	string = malloc(sizeof(char) * 256);
	if (fopen("help.txt", "r") != NULL)
	{
		f = fopen("help.txt", "r");
		while (fgets(string, 256, f) != NULL)
			printf("%s", string);
		puts("");
		fclose(f);
        }
	else
		printf("Ошибка, файл не найден");
}

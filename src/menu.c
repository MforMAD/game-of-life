#include "menu.h"

int main_menu()
{
        char ch;
        printf("Вас Приветствует игра <Жизнь>!\nВыбрать пункт меню вы можете с помощью кнопок 1 -3 на клавиатуре, а затем нажать Enter\n1.Новая игра\n2.Помощь\n3.Выход\n");
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
}

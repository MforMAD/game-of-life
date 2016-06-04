#include "menu.h"

int main_menu()
{
        char ch;
        printf("1.Новая игра\n2.Помощь\n3.Выход\n");
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



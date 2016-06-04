KEYS = -g -Wall
INCLUDES = -I src/
DIRS = ./bin ./obj
obj_files_gtk = ./obj/main_gtk.o ./obj/game.o ./obj/template.o ./obj/interface.o ./obj/field.o
obj_files_console = ./obj/main_console.o ./obj/game.o ./obj/template.o ./obj/field.o ./obj/menu.o

GTK_LIB = `pkg-config --cflags --libs gtk+-3.0`

all: $(DIRS) ./bin/game_gtk ./bin/game_console

./bin/game_gtk: $(obj_files_gtk)
	gcc $(obj_files_gtk) -o ./bin/game_gtk $(KEYS) $(GTK_LIB)

./bin/game_gtk: $(obj_files_console)
	gcc $(obj_files_console) -o ./bin/game_gtk $(KEYS)

bin:
	mkdir bin

obj:
	mkdir obj

./obj/main_gtk.o : ./src/main_gtk.c
	gcc -c ./src/main_gtk.c -o ./obj/main_gtk.o $(INCLUDES) $(KEYS) $(GTK_LIB)

./obj/main_console.o : ./src/main_console.c
	gcc -c ./src/main_console.c -o ./obj/main_console.o $(INCLUDES) $(KEYS)

./obj/game.o: ./src/game.c
	gcc -c ./src/game.c -o ./obj/game.o $(INCLUDES) $(KEYS)

./obj/template.o: ./src/template.c
	gcc -c ./src/template.c -o ./obj/template.o $(INCLUDES) $(KEYS)

./obj/interface.o: ./src/interface.c
	gcc -c ./src/interface.c -o ./obj/interface.o $(INCLUDES) $(KEYS) $(GTK_LIB)

./obj/field.o: ./src/field.c
	gcc -c ./src/field.c -o ./obj/field.o $(INCLUDES) $(KEYS)

./obj/menu.o: ./src/menu.c
	gcc -c ./src/menu.c -o ./obj/menu.o $(INCLUDES) $(KEYS)

.PHONY: clean
clean: 
	rm -r ./bin ./obj
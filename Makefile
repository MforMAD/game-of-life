KEYS = -g -Wall
INCLUDES = -I src/
DIRS = ./bin ./obj
obj_files = ./obj/code.o ./obj/game.o ./obj/template.o
GTK_LIB = `pkg-config --cflags --libs gtk+-3.0`

all: $(DIRS) ./bin/code

./bin/code: $(obj_files)
	gcc $(obj_files) -o ./bin/code $(KEYS) $(GTK_LIB)

bin:
	mkdir bin

obj:
	mkdir obj

./obj/code.o : ./src/code.c
	gcc -c ./src/code.c -o ./obj/code.o $(INCLUDES) $(KEYS) $(GTK_LIB)

./obj/game.o: ./src/game.c
	gcc -c ./src/game.c -o ./obj/game.o $(INCLUDES) $(KEYS)

./obj/template.o: ./src/template.c
	gcc -c ./src/template.c -o ./obj/template.o $(INCLUDES) $(KEYS)

.PHONY: clean
clean: 
	rm -r ./bin ./obj
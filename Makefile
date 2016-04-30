./bin/code: bin obj ./obj/code.o 
	gcc ./obj/code.o -o ./bin/code

bin :
	mkdir bin

obj :
	mkdir obj

./obj/code.o : ./src/code.c
	gcc -c ./src/code.c -o ./obj/code.o

.PHONY: clean
clean: 
	rm -r ./bin ./obj
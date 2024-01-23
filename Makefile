OBJ = val.o vm.o
CC = clang

run: build
	main.exe

build: $(OBJ)
	$(CC) main.c $(OBJ) -o main.exe

$.o: %.c
	$(CC) $^ -c -o $@

clean:
	rm *.o

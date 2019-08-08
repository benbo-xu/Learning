./src/static_lib.o:./src/static_lib.c
	gcc -c ./src/static_lib.c -o ./src/static_lib.o
./lib/libstatic_lib.a:./src/static_lib.o
	ar -rcs ./lib/libstatic_lib.a ./src/static_lib.o
./bin/main:./src/main.c
	gcc -L./lib/ ./src/main.c -lstatic_lib -o ./bin/main
clean:





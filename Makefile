OUT_FILE = vm.out
all: main.o vm.o
	gcc -o $(OUT_FILE) main.o vm.o
main.o: main.c
	gcc -c main.c
vm.o: vm.c
	gcc -c vm.c
clean:
	rm -f $(OUT_FILE) main.o vm.o
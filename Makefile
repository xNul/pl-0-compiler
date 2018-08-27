all: main.o vm.o
	gcc -o vm.out main.o vm.o
vm.out: all
run_vm: vm.out
	cd test/ ; bash run_vm.sh
grade: vm.out
	cd test/ ; bash grader.sh
main.o: main.c
	gcc -c main.c
vm.o: vm.c
	gcc -c vm.c
clean:
	rm -f vm.out main.o vm.o

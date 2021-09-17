OUT_FILE = parser.out
STD = c99

all: $(OUT_FILE)

$(OUT_FILE): main.o parser.o token.o data.o symbol.o
	gcc -o $(OUT_FILE) main.o token.o parser.o data.o symbol.o -std=$(STD)

run_parser: $(OUT_FILE)
	cd test/ ; bash run_parser.sh

grade: $(OUT_FILE)
	cd test/ ; bash grader.sh

main.o: main.c
	gcc -c main.c -std=$(STD)

data.o: data.c data.h
	gcc -c data.c -std=$(STD)

parser.o: parser.c parser.h
	gcc -c parser.c -std=$(STD)

token.o: token.c token.h
	gcc -c token.c -std=$(STD)

symbol.o: symbol.c symbol.h
	gcc -c symbol.c -std=$(STD)

removeObjectFiles:
	rm -f main.o token.o parser.o data.o symbol.o

clean: removeObjectFiles
	rm $(OUT_FILE) test/io/your_outputs -rf

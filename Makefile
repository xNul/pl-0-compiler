OUT_FILE = la.out
STD = c99

all: $(OUT_FILE)

$(OUT_FILE): main.o lexical_analyzer.o source_code.o token.o lexical_analyzer_deleteLexerOut.o
	gcc -o $(OUT_FILE) main.o source_code.o lexical_analyzer.o lexical_analyzer_deleteLexerOut.o token.o -std=$(STD)

run_la: $(OUT_FILE)
	cd test/ ; bash run_la.sh

grade: $(OUT_FILE)
	cd test/ ; bash grader.sh

main.o: main.c
	gcc -c main.c

lexical_analyzer.o: lexical_analyzer.c lexical_analyzer.h
	gcc -c lexical_analyzer.c -std=$(STD)

lexical_analyzer_deleteLexerOut.o: lexical_analyzer.h lexical_analyzer_deleteLexerOut.c
	gcc -c lexical_analyzer_deleteLexerOut.c -std=$(STD)

source_code.o: source_code.c source_code.h
	gcc -c source_code.c -std=$(STD)

token.o: token.c token.h
	gcc -c token.c -std=$(STD)

clean:
	rm -f $(OUT_FILE) main.o token.o lexical_analyzer.o lexical_analyzer_deleteLexerOut.o source_code.o
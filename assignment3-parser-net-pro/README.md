# Assignment 2
In this assignment, you are going to implement a parser whose specifications are included in the assignment text. This README file explains the implementation details and introduces the repository which contains the skeleton code.

For your convenience, a repository was prepared containing C files, a Makefile and tester-grader scripts with test cases. These files were used to initialize your repository.

Below are the brief explanations about the files included in your repository. For detailed explanations, you should follow the comments inside those files.

* [Makefile](Makefile): The makefile that helps to build, test and clean your solution.

* [main.c](main.c): The C file that contains the main function, the code required to interpret command line arguments, and the  call to `parser()` function which you should implement.

* [data.h](data.h): Defines the required enumarations and declares the string representations of the tokens, parser errors and non-terminals.

* [data.c](data.c): Defines the strings declared in [data.h](data.h).

* [token.h](token.h): The header file that contains the definitions of the structs Token, TokenList, TokenListIterator, and the declarations of the functions that manipulates those structs.

* [token.c](token.c): The C file that implements the functions declared in [token.h](token.h).

* [symbol.h](symbol.h): Defines the symbol table and symbol table entry structs and declares the API for the symbol table related operations.

* [symbol.c](symbol.c): Implements the symbol table related operations declared in [symbol.h](symbol.h).

* [test/](test/): The folder that contains the test cases and the scripts that you could use to try the test cases on your executable. Further information is included in the [Test & Grade](#test-&-grade) section below.

* [parser.h](parser.h): Declares the `parser()` function, which is needed to be implemented in [parser.c](parser.c) file by you. Also, declares the `printParseErr()` function, which has already been implemented inside [parser.c](parser.c).

* [parser.c](parser.c): The only file that needs modifying by you. Also, this file is the only file that is going to be used while grading your assignment. Other files are going to be replaced by their originals.

Implementation of `parser()` function is a must since it is going to be used by [main.c](main.c) to operate the parser on token list. Helper functions are included as hints of a possible design. However, you are free to remove the helper functions and add new ones.

In the skeleton code, the `parser()` has already been fully-implemented. However, some functions were left incomplete to be implemented by you, which are:

```
int program();
int block();
int const_declaration();
int var_declaration();
int proc_declaration();
int statement();
int condition();
int relop();
int expression();
int term();
```

These functions should return 0 if no error is encountered while parsing them. However, if you encounter any type of error, you should immediately stop parsing and return the corresponding error code from the function. The possible error codes are included in [data.c](data.h) as `parserErrorMsg[]`.

One of the functions that should have a similar structure with the above ones was fully-implemented. Therefore, you are strongly encouraged to visit `factor()` function to see how it was implemented since you can implement the other functions by following a very similar design.

If you would like to follow your own design, you could implement the `parser()` function from stratch. However, make sure that you follow the same function signature declared in `parser.h` file.

# Command Line Arguments
Usage: `./parser.out (pl0_lexer_out) (parser_output_file)`

* `pl0_lexer_out`: The path to the file containing the lexer out for the programming language PL/0.

* `parser_output_file`: The path to the file to write the parser output, which contains the parsing history, the symbol table and the error message if applicable.

You are not required to handle command line argument interpretation since it is already implemented inside [main.c](main.c) file.

In the presence of the test cases, an example usage could be given as:
```
$ ./parser.out test/io/inputs/inp_0.txt your_output_dir/out_0.txt
```
After the execution of the above bash command, one file would be created in `your_output_dir` folder. This file should be the same as `test/io/ground_truth/gt_out_0.txt`.

# Output Format
In this assignment, you are NOT required to explicity print anything by making calls to `printf()` or `fprintf()`. Instead, you will make use of the printer functions given to you, modify the necessary variables and return the correct values from your functions. This will make your program print the correct output on your output file.

There are three main things that are printed on the output file: parser history, symbol table, success/error message. See the following sections to understand how you are going to achieve printing these in your output file.

## Parser History
The printing of the history could be achieved by making use of `printCurrentToken()` and `printNonTerminal()` functions. The calls to `printNonTerminal()` function has already been inserted to the necessary places. Therefore, make sure to call `printCurrentToken()` function whenever you are going to consume a token.

Notice that if you see a token that was not supposed to be there, you should not print it. Instead, you should immediately return from your function with the corresponding error code.

## Symbol Table
In this assignment, you are going to create a simplified symbol table while parsing. You could see the symbol table related structures and the API available to you in the files [symbol.h](symbol.h) and [symbol.c](symbol.c). The only thing you need to do is to fill the variable `symbolTable`, which is declared at the very beginning of [parser.c](parser.c) file as a global variable. Do not worry about printing the symbol table: the given `parser()` function handles the printing of this symbol table.

Also, notice that the symbol table is printed only when the parsing is successful. Therefore, you are not going to see your symbol table when you return an error code.

## Error/Success Message
If the parsing is successful. i.e. you do not encounter with any parser errors while parsing, the `parser()` function should return 0. Otherwise, the `parser()` function should return a non-zero error code.

The `parser()` function directly returns the return value of the `program()` function. Since you are the one who is going to implement `program()` function, your return value will decide the error/success message.

While parsing, check errors at places where applicable. If you encounter any error, stop parsing immediately by returning the error code to the upper level. All the functions should check for errors and propagate the error code till `parser()` function.

The error or success message is printed in [main.c](main.c) file. If you return the correct values from your functions, then you should be able to see the related success or error message in your output file.

# Build & Run
The build is done with the help of the Makefile included in the repository. Following command is enough to build your solution and obtain the executable file `parser.out`:
```
$ make
```
Then, to test your solution, you should use the following command by feeding necessary command line arguments:

```
$ ./parser.out (pl0_lexer_out) (parser_output_file)
```

For further information about command line arguments, read the [Command Line Arguments](#command-line-arguments) section.

# Test & Grade
Test cases with their ground truth outputs were prepared to help you test your solutions. Also, simple tester and grader scripts are included to allow you run your tests in automated manner.

You could find the input files in [test/io/inputs/](test/io/inputs/) folder. The files that your solution should output are included in [test/io/ground_truth/](test/io/ground_truth/) folder.

Since the input files are not easily understandable, the corresponding PL/0 code files are also included in [test/io/inputs_in_pl0/](test/io/inputs_in_pl0/). These files are not going to be used as an input to your parser. They are the PL/0 code files which are used to obtain the token lists included in [test/io/inputs/](test/io/inputs/) folder.

Targets for testing and grading also exist in the [Makefile](Makefile). The target `run_parser` allows you to run your parser on all the given test cases and creates the printed outputs of parser inside [test/io/your_outputs/](test/io/your_outputs/) folder. The target `grade` runs your parser on all the given test cases, creates the printed outputs of your parser and compares it with the ground truth outputs which are included in [test/io/ground_truth/](test/io/ground_truth/) folder.

Basically, what you should do to get printed outputs from your parser as a result of feeding the test cases is:
```
$ make run_parser
```

On top of that, if you are willing to compare your outputs with the ground truth outputs and see how many test cases you passed, you should do:
```
$ make grade
```

Although you do not need, you are encouraged to observe the bash scripts [test/run_parser.sh](test/run_parser.sh) and [test/grader.sh](test/grader.sh), so that, you could come up with your own ideas to better test your work.

To understand the assignment better and to further test your code, you are highly recommended to prepare new test cases and share them.

## Important Note on Grader
Note that passing all the tests does not imply that you will take full points from the assignment. Different and more complex test cases will be included while grading your assignment. Therefore, try to come up with your own test methods to ensure the correctness of your work.

# Hints
* Inspect the files [symbol.h](symbol.h), [symbol.c](symbol.c) and [parser.c](parser.c) carefully. Read all the documentations included in those files to understand the design suggested to you.
* The function `factor()` is a great hint for you. If you could understand what is going on inside this function, implementing the rest should be straightforward for you.
* You may want to use dynamic memory allocation in your implementation. However, the example implementation does not include any malloc/calloc/realloc/free calls inside the [parser.c](parser.c) file. Therefore, if you are not comfortable with manual memory management in C, keep in mind that you could survive without it in this assignment.

# Important Note on Submission

Notice that the only file you should modify is [parser.c](parser.c) file since it is the only file that is going to be used while grading your assignment. Other files are going to be replaced by their originals. Therefore, it is important to ensure that the final version for your [parser.c](parser.c) file successfully builds and works as expected with the originals of the other files.

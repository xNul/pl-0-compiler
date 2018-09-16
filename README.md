# Assignment 2
In this assignment, you are going to implement a lexical analyzer whose specifications are included in the assignment text. This README file explains the implementation details and introduces the repository which contains the skeleton code.

For your convenience, a repository was prepared containing C files, a Makefile and tester-grader scripts with test cases. These files were used to initialize your repository.

Below are the brief explanations about the files included in your repository. For detailed explanations, you should follow the comments inside those files.

* [Makefile](Makefile): The makefile that helps to build, test and clean.

* [main.c](main.c): The C file that contains the main function, the code required to interpret command line arguments, and the  call to `lexicalAnalyzer()` function which you should implement.

* [data.h](data.h): Defines the enumaration and the string representations of the tokens, and constants.

* [lexical_analyzer.h](lexical_analyzer.h): Includes:
  * The declaration of the `lexicalAnalyzer()` function, which is needed to be implemented in [lexical_analyzer.c](lexical_analyzer.c) file by you.
  * The definition of LexerOut struct, which is the return type of the `lexicalAnalyzer()` function.
  * The `LexErr` enumeration, which includes the types of possible lexer errors.

* [lexical_analyzer.c](lexical_analyzer.c): The only file that needs modifying by you. Also, this file is the only file that is going to be used while grading your assignment. Other files are going to be replaced by their originals.

Implementation of `lexicalAnalyzer()` function is a must since it is going to be used by [main.c](main.c) to operate the lexical analyzer on PL/0 source code. Helper functions are included as hints of a possible design. However, you are free to remove the helper functions and add new ones.

In the skeleton code, the `lexicalAnalyzer()` has already been fully-implemented. However, the functions `lexicalAnalyzer()` calls were left incomplete - to be implemented by you. If you decide to follow the suggested design, you should implement the functions `DFA_Alpha()`, `DFA_Digit()` and `DFA_Special()`, which are called from `lexicalAnalyzer()`. 

If you would like to follow your own design, you could implement the `lexicalAnalyzer()` function from stratch. However, make sure that you follow the same function signature declared in `lexical_analyzer.h` file.

* [test/](test/): The folder that contains the test cases and the scripts that you could use to try those test cases on your executable. Further information is included in the [Test & Grade](#test-&-grade) section below.

* [lexical_analyzer_deleteLexerOut.c](lexical_analyzer_deleteLexerOut.c): The implementation of `deleteLexerOut()` function.

* [source_code.h](source_code.h): The header file that contains the declarations for the source code manipulation functions.

* [source_code.c](source_code.c): The C file that implements the functions declared in [source_code.h](source_code.h).

* [token.h](token.h): The header file that contains the definitions of the structs Token, TokenList, and the declarations of the functions that manipulates those structs.

* [token.c](token.c): The C file that implements the functions declared in [token.h](token.h).

# Command Line Arguments
Usage: `./la.out (pl0_source_code_file) (tokenlist_output_file)`

* pl0_source_code_file: The path to the file containing the source code for the programming language PL/0.

* tokenlist_output_file: The path to the file to write the lexical analyzer output, which contains the lexeme table.

You are not required to handle command line argument interpretation since it is already implemented inside [main.c](main.c) file.

In the presence of the test cases, an example usage could be given as:
```
$ ./la.out test/io/inputs/inp_0.txt your_output_dir/lexeme_table_0.txt
```
After the execution of the above bash command, one file would be created in `your_output_dir` folder. This file should be the same as `test/io/ground_truth/gt_out_0.txt`.

# A Note on Output Format
In this assignment, you are not required to print anything. The evaluation will be done based on the return value of `lexicalAnalyzer()` function. For your convenience while testing, the code that prints the return value as a list is included in the repository.

# Build & Run
The build is done with the help of the Makefile included in the repository. Following command is enough to build your solution and obtain the executable file `la.out`:
```
$ make
```
Then, to test your solution, you should use the following command by feeding necessary command line arguments:

```
$ ./la.out (pl0_source_code_file) (tokenlist_output_file)
```

For further information about command line arguments, read the [Command Line Arguments](#command-line-arguments) section.

# Test & Grade
Test cases with their ground truth outputs were prepared to help you test your solutions. Also, simple tester and grader scripts are included to allow you run your tests in automated manner.

You could find the input files in [test/io/inputs/](test/io/inputs/) folder. The files that your solution should output are included in [test/io/ground_truth/](test/io/ground_truth/) folder.

Targets for testing and grading does also exist in the [Makefile](Makefile). The target `run_la` allows you to run your lexical analyzer on all the given test cases and creates the printed outputs of lexical analyzer inside [test/io/your_outputs/](test/io/your_outputs/) folder. The target `grade` runs your lexical analyzer on all the given test cases, creates the printed outputs of your lexical analyzer and compares it with the ground truth outputs which are included in [test/io/ground_truth/](test/io/ground_truth/) folder.

Basically, what you should do to get printed outputs from your lexical analyzer as a result of feeding the test cases is:
```
$ make run_la
```

On top of that, if you are willing to compare your outputs with the ground truth outputs and see how many test cases you passed, you should do:
```
$ make grade
```

Although you do not need, you are encouraged to observe the bash scripts [test/run_la.sh](test/run_la.sh) and [test/grader.sh](test/grader.sh), so that, you could come up with your own ideas to better test your work.

To understand the assignment better and to further test your code, you are highly recommended to prepare new test cases and share them.

## Important Note on Grader
Note that passing all the tests does not imply that you will take full points from the assignment. Different and more complex test cases will be included while grading your assignment. Therefore, try to come up with your own test methods to ensure the correctness of your work.

# Hints
* Inspect the files [data.h](data.h), [token.h](token.h), [lexical_analyzer.h](lexical_analyzer.h) and [lexical_analyzer.c](lexical_analyzer.c) carefully. Read all the documentations included in those files to understand the design suggested to you.
* You may want to use dynamic memory allocation in your implementation. However, the example implementation does not include any malloc/calloc/realloc/free calls inside the [lexical_analyzer.c](lexical_analyzer.c) file. Therefore, if you are not comfortable with manual memory management in C, keep in mind that you could survive without it in this assignment - although you are encouraged to practice.
* The struct `LexerState` is the main structure that holds the state of the lexical analysis. A pointer to an instance of it is passed to the functions you are required to implement. Therefore, make sure that you understand the fields of it. For example, not incrementing the `charInd` field after consuming a character may cause infinite loop since it would be read again and again.

# Important Note on Submission

Notice that the only file you should modify is [lexical_analyzer.c](lexical_analyzer.c) file since it is the only file that is going to be used while grading your assignment. Other files are going to be replaced by their originals. Therefore, it is important to ensure that the final version for your [lexical_analyzer.c](lexical_analyzer.c) file successfully builds and works as expected with the originals of the other files.

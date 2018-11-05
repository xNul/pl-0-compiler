# Assignment 4: Code Generation
In this assignment, you are going to implement a code generator whose specifications are included in the assignment text. This README file explains the implementation details and introduces the repository which contains the skeleton code.

The sections are as follows:

* [Files](#files): The brief introduction to the files included in the skeleton repository.
* [**What is Expected**](#what-is-expected): **What is expected from you in this assignment and how your work will be evaluated.**
* [Command Line Arguments](#command-line-arguments): The explanation of the command line interface to the code generator.
* [How to run the virtual machine?](#how-to-run-the-virtual-machine): How to compile and run the given virtual machine code. The command line interface to it.
* [Symbol Table](#symbol-table): What is changed in the symbol table. Why and how you need to use the symbol table.
* [Register Allocation](#register-allocation): A simple approach for register allocation
* [Build](#build): How to build your solution.
* Test & Grade: How to use the given test cases to test and grade your solution.
* [Hints](#hints): Some hints.
* [Important Note on Submission](#important-note-on-submission): [code_generator.c](code_generator.c) is all your submission.

## Files

For your convenience, a repository was prepared containing C files, a Makefile and tester-grader scripts with test cases. These files were used to initialize your repository.

Below are the brief explanations about the files included in your repository. For detailed explanations, you should follow the comments inside those files.

* [Makefile](Makefile): The makefile that helps to build, test and clean your solution.

* [main.c](main.c): The C file that contains the main function, the code required to interpret command line arguments, and the  call to `code_generator()` function, which you should implement.

* [data.h](data.h): Defines the required enumarations and declares the string representations of the tokens, code generator errors and non-terminals.

* [data.c](data.c): Defines the strings declared in [data.h](data.h).

* [token.h](token.h): The header file that contains the definitions of the structs Token, TokenList, TokenListIterator, and the declarations of the functions that manipulates those structs.

* [token.c](token.c): The C file that implements the functions declared in [token.h](token.h).

* [symbol.h](symbol.h): Defines the symbol table and symbol table entry structs and declares the API for the symbol table related operations. Notice that the symbol structure is different from the one used in parser assignment. There are additional fields. For more information, see the [Symbol Table](#symbol-table) section below.

* [symbol.c](symbol.c): Implements the symbol table related operations declared in [symbol.h](symbol.h).

* [test/](test/): The folder that contains the test cases and the scripts that you could use to try the test cases on your executable. Further information is included in the [Test & Grade](#test-&-grade) section below.

* [vm/](vm/): The files regarding to virtual machine. The same files given in the virtual machine assignment and the object file [vm.o](vm/vm.o) is included in this folder. The object file is compiled in Eustis machine. Therefore, it is possible to get errors if you try to run the virtual machine on your local computer. Instead, make use of the Eustis machine. For more information, see the [How to run the virtual machine?](#how-to-run-the-virtual-machine) section below.

* [code_generator.h](code_generator.h): Declares the `code_generator()` function, which is needed to be implemented in [code_generator.c](code_generator.c) file by you. Also, declares the `printCGErr()` function, which has already been implemented inside [code_generator.c](code_generator.c).

* [code_generator.c](code_generator.c): The only file that needs modifying by you. Also, this file is the only file that is going to be used while grading your assignment. Other files are going to be replaced by their originals.

Implementation of `code_generator()` function is a must since it is going to be used by [main.c](main.c) to operate the code generator on token list. Helper functions are included as hints of a possible design. However, you are free to remove the helper functions and add new ones.

In the skeleton code, the `code_generator()` and `program()` has already been fully-implemented. However, some functions were left incomplete to be implemented by you, which are:

```
int program();
int block();
int const_declaration();
int var_declaration();
int proc_declaration();
int statement();
int condition();
int expression();
int term();
```

**Notice that `relop()` function that was used in your parser is removed in code generator. The reason is that it is easier to generate code for relational operations once both the condition and relop is parsed inside the function `condition()`.**

These functions should return 0 if no error is encountered. However, if you encounter any type of error, you should immediately stop code generation and return the corresponding error code from the function. The possible error codes are included in [data.c](data.c) as `codeGeneratorErrMsg[]`.

**Notice that 5 new error codes are introduced in [data.c](data.c) on top of those of ones that were used in the parser assignment. You could raise these new error codes by making use of your symbol table.**

If you would like to follow your own design, you could implement the `code_generator()` function from stratch. However, make sure that you follow the same function signature declared in `code_generator.h` file.

## What is Expected

In this assignment, you are **NOT** required to explicity print anything by making calls to `printf()` or `fprintf()`. Instead, you will make use of the assembly code emitter function **`emit()`** given to you and return the correct values from your functions. This will make your program print the correct output on your output file.

There are two possible pipelines that could be followed according to the PL/0 code that will be given to you: valid PL/0 code or erroneous PL/0 code. These pipelines are discussed below.

### Pipeline for erroneous PL/O code
The PL/0 code can include errors that you are required to detect. The full list of error codes are given in [data.c](data.c) file. First 15 error codes are the same as the ones you detected in parser assignment. 5 new error codes are included (from 15 to 19), which could be detected by making use of the symbol table.

If you encounter with any code generator errors, the `codeGenerator()` function should return a non-zero error code. While code generation, check errors at places where applicable. If you encounter any error, stop code generation immediately by returning the error code to the upper level. All the functions should check for errors and propagate the error code till `codeGenerator()` function.

The error message is printed in [main.c](main.c) file. If you return the correct values from your functions, then you should be able to see the related error message in your output file.

The test cases from 6 to 9 (test/io/6/, test/io/7/, test/io/8/ and test/io/9/) include errors. The content of these folders are as follows:

* **pl0_code.txt:** The PL/0 code. This file is given for your convenience since inspecting the PL/0 code is easier.
* **lexer_out.txt:** The output of the lexer when the given pl0_code.txt file is inputted. This file will be used as input to your code generator.
* **code_generator_err.txt:** This file includes the code generator error message. Once you return the correct error code from your `codeGenerator()`, your code generator will output this content. **This file will be used as the ground truth output while grading your code generator with erroneous PL/0 code.**

### Pipeline for valid PL/O code
While code generation, you will make use of the `emit()` function. It will fill the assembly code array `vmCode`. At the end of a successful code generation where you return 0 from your `codeGenerator()` function, the assembly code array that is filled by you will be written to a file. However, it is possible to generate different assembly codes that will have the same functionality. Therefore, you are NOT going to be graded by checking whether you generated the very same assembly code that we did. Instead, we will test the functionality of your generated assembly code. For that, we will run your assembly code on the virtual machine and test whether your assembly code will lead the virtual machine to output the expected output.

For instance, let's think of a PL/0 code that adds two numbers. We could think of various variations of assembly code that would perform the functionality of this PL/0 code. However, once we input two numbers n<sub>1</sub> and n<sub>2</sub> while executing any of these assembly codes, it is obvious that the output will be n<sub>1</sub>+n<sub>2</sub>. As in this case, we will check whether the code generated by you really performs the required functionality.

The test cases from 0 to 8 (test/io/0/, ... , and test/io/8/) does not include errors. The content of these folders are as follows:

* **pl0_code.txt:** The PL/0 code. This file is given for your convenience since inspecting the PL/0 code is easier.
* **lexer_out.txt:** The output of the lexer when the given pl0_code.txt file is inputted. This file will be used as input to your code generator.
* **vm_in.txt:** The input to the virtual machine. It is going to be used while executing the code you generated on virtual machine. This file is included in the folder only if the given PL/0 code includes `read` statement. Otherwise, it is not included since the PL/0 code is not expected to take input.
* **vm_out.txt:** The ground truth output of the virtual machine. The code you generated is expected to output this file once it is run on the virtual machine. **This file will be used while grading your code generator with valid PL/0 code.**

To test your results with a valid PL/0 code, you should follow a pipeline with two steps. First, you should input the token list of the PL/0 code (lexer_out.txt) to your code generator. This step should output a file with assembly code. Second, you should run the output assembly code on virtual machine, possibly by inputting vm_in.txt if any `read` statement is included in the PL/0 code. At the end of this step, your virtual machine should output a file with the content of vm_out.txt.

For details about how to run the virtual machine, see the [How to run the virtual machine?](#how-to-run-the-virtual-machine) section below.

## Command Line Arguments
Usage: `./code_generator.out (pl0_lexer_out) (cg_output_file)`

* `pl0_lexer_out`: The path to the file containing the lexer out for the programming language PL/0.

* `cg_output_file`: The path to the file to write the code generator output, which could contain either PM/0 assembly code or code generator error message.

You are not required to handle command line argument interpretation since it is already implemented inside [main.c](main.c) file.

## How to run the virtual machine?
The virtual machine that is going to be used is the same as you implemented in assignment 1. However, you are not required to bring your virtual machine implementation for this assignment. The skeleton code of virtual machine with the object file [vm.o](vm/vm.o) is included in [vm/](vm/) folder. The object file is compiled in Eustis machine. Therefore, it is possible to get errors if you try to run the virtual machine on your local computer. Instead, make use of the Eustis machine.

To compile the virtual machine, run the following command:
```
$ make vm
```
Then, the executable file [vm/vm.out](vm/vm.out) will be created.

The usage of the command line arguments for the virtual machine is as follows:

`./vm.out (ins_inp_file) (simul_outp_file) [vm_inp_file=stdin] [vm_outp_file=stdout]`

* ins_inp_file: The path to the file containing the list of instructions to be loaded to code memory of the virtual machine. This will be output of your code generator.

* simul_outp_file: The path to the file to write the simulation output, which contains both code memory and execution history. The simulation log is not necessary for this assignment. Therefore, you could ignore it by using `/dev/null` as this argument.

* vm_inp_file: The path to the file that is going to be attached as the input stream to the virtual machine. This will be the vm_inp.txt file. If your code does not require inputting to virtual machine, you could ignore this by using `/dev/null` as this argument.

* vm_outp_file: The path to the file that is going to be attached as the output stream to the virtual machine. This will be vm_out.txt file.

For example, an assembly code generated for a PL/0 code that does NOT take any arguments, you could use the following command:

```
$ ./vm/vm.out code_generator_out.txt /dev/null /dev/null my_vm_out.txt
```

For one that takes arguments (caused by the `read` statements in the PL/0 code), you could use the following command:

```
$ ./vm/vm.out code_generator_out.txt /dev/null vm_in.txt my_vm_out.txt
```

## Symbol Table
Symbol table is a transient data used while generating code and is dumped later. In this assignment, you are given a suggested symbol table design. Your final symbol table will not be graded. However, you need to properly build your symbol table and make use of it to generate code with correct functionality.

On top the symbol structure given in parser assignment, two more fields are added. These are:

* unsigned int **address**: You could use this field for symbols of type VAR and PROC. For VAR, you could use it to store the position offset of the variable at stack. For PROC, you could use it to store the address of the entrance point to the procedure.
* Symbol* **scope**: Keeping track of the scope of the symbols is essential. For example, you could have two variables with the same name at different scopes in a PL/0 code. To choose which variable to proceed with, you should keep track of the scopes of the symbols and be aware of your current scope. In [code_generator.c](code_generator.c) file, a global variable is introduced to keep track of the current scope: `Symbol* currentScope`. You could assign it to `NULL` if you are in global scope, i.e., not inside any procedure. If you are inside a procedure, you could assign it to the symbol of the procedure. Then, whenever you need to add a new symbol to your symbol table, you could fill the `scope` field of your symbol with the `currentScope`. If you follow this convention, you could make use of the `findSymbol()` function for your symbol queries. For more information about `findSymbol()`, you could see its documentation inside [symbol.h](symbol.h) file.

To understand the significance of keeping track of the scope, you could observe the following PL/0 code files: [test/io/1/pl0_code.txt](test/io/1/pl0_code.txt), [test/io/2/pl0_code.txt](test/io/2/pl0_code.txt).

## Register Allocation
Once used in an efficient way, register file could improve program's performance drastically. To understand why and how, you are suggested to read the corresponding section of the textbook _(The Dragon Book, Section 8.8., Register Allocation and Assignment)_.

However, for this assignment, you could make use of a very simple strategy for register allocation by using your register file as a stack of temporary values.  The global variable `int currentReg` defined in [code_generator.c](code_generator.c) could be used to keep track of the top of the stack. Whenever you need to store a temporary value, store your value in the register with id `currentReg` and change the top of your stack by incrementing `currentReg`. Then, depending on the operation you are going to apply, you could make use of the value or values at the top of your stack and reflect the pop operation by decrementing the `currentReg` variable.

One disadvantage of this approach is that it limits the expression nesting depth since the number of registers is limited. This issue could be resolved by making use of the stack memory when the register file is fully filled. However, the inputs to test your solution will not include such expressions that would exceed the limits.

## Build
The build is done with the help of the Makefile included in the repository. Following command is enough to build your solution and obtain the executable file `code_generator.out`:
```
$ make all
```

For further information about command line arguments and how to run your executable, read the [Command Line Arguments](#command-line-arguments) section.

## Test & Grade
Test cases with their ground truth outputs were prepared to help you test your solutions. Also, simple tester and grader scripts are included to allow you run your tests in automated manner.

You could find the input files in [test/io/](test/io/) folder. The files that your solution should output are included in the corresponding test case's folder.

Since the input files are not easily understandable, the corresponding PL/0 code files are also included as pl0_code.txt. These files are not going to be used as an input to your code generator. They are the PL/0 code files which are used to obtain the token lists.

Targets for testing and grading also exist in the [Makefile](Makefile). The target `run_cg` allows you to run your code generator on all the given test cases and creates the outputs of your code generator inside [test/io/your_outputs/](test/io/your_outputs/) folder. The target `grade` runs your code generator on all the given test cases, creates the outputs of your code generator and compares it with the ground truth outputs.

Basically, what you should do to get outputs from your code generator as a result of feeding the test cases is:
```
$ make run_cg
```

On top of that, if you are willing to compare your outputs with the ground truth outputs and see how many test cases you passed, you should do:
```
$ make grade
```

Although you do not need, you are encouraged to observe the bash scripts [test/run_cg.sh](test/run_cg.sh) and [test/grader.sh](test/grader.sh), so that, you could come up with your own ideas to better test your work.

To understand the assignment better and to further test your code, you are highly recommended to prepare new test cases and share them.

### Important Note on Grader
Note that passing all the tests does not imply that you will take full points from the assignment. Different and more complex test cases will be included while grading your assignment. Therefore, try to come up with your own test methods to ensure the correctness of your work.

## Hints
* Inspect the files [symbol.h](symbol.h) and [code_generator.c](code_generator.c) carefully. Read all the documentations included in those files to understand the design suggested to you.
* The usage of the functions `emit()` and `findSymbol()` and the global variables `nextCodeIndex`, `currentScope` and `currentReg` is essential. Therefore, make sure that you understand why and how they are used by reading the documentations.
* You may want to use dynamic memory allocation in your implementation. However, the example implementation does not include any malloc/calloc/realloc/free calls inside the [code_generator.c](code_generator.c) file. Therefore, if you are not comfortable with manual memory management in C, keep in mind that you could survive without it in this assignment.

## Important Note on Submission
Notice that the only file you should modify is [code_generator.c](code_generator.c) file since it is the only file that is going to be used while grading your assignment. Other files are going to be replaced by their originals. Therefore, it is important to ensure that the final version for your [code_generator.c](code_generator.c) file successfully builds and works as expected with the originals of the other files.

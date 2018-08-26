# Assignment 1: Test

Test cases with their ground truth outputs were prepared to help you test your solutions. Also, simple tester and grader scripts are included to allow you run your tests in automated manner.

You could find the input files in [inputs/](inputs/) folder. The files that your solution should output are included in [groundtruth/](groundtruth/) folder.

## [run_vm.sh](run_vm.sh)
This bash script allow you to run all the test cases and extract their outputs in automated manner. What it does is to run your virtual machine by feeding the input file paths and output file paths.

In [tests.txt](tests.txt) file, the list of arguments to be fed to your virtual machine is included. The bash script [run_vm.sh](run_vm.sh) runs all the tests included in this list and stores the output files in the output folder.

Before starting, make sure that your virtual machine executable `vm.out` is at the same folder with [run_vm.sh](run_vm.sh). Also, if you are willing to save your outputs in a different directory then current, make sure that the folders in the path of output files do exist. Then, on the terminal, type `$ bash test.sh` to get your outputs.

## [grader.sh](grader.sh)

On top of [run_vm.sh](run_vm.sh), the bash script [grader.sh](grader.sh) allows you to see if you passed or failed the test cases. What it does is using the `diff` tool to compare your output with the ground truth output.

In [tests_grader.txt](tests_grader.txt) file, the list of arguments to be fed to your virtual machine and the ground truth output files are included.

Before starting, make sure that your virtual machine executable `vm.out` is at the same folder with [grader.sh](grader.sh). Also, if you are willing to save your outputs in a different directory then current, make sure that the folders in the path of output files do exist. Then, on the terminal, type `$ bash test.sh` to test your executable.

# Important Note

Note that passing all the tests does not imply that you will take full points from the assignment. Different and more complex test cases will be included while grading your assignment.

To understand the assignment better and to further test your code, you are highly recommended to prepare new test cases and share them. You could start by writing simple pseduo-code and try to translate it to the language that your virtual machine would interpret. Then, you could proceed by writing functions, passing arguments to your functions, returning values from functions and so on.

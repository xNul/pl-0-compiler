# Assignment 1
In this assignment, you are going to implement a virtual machine whose specifications are included in the assignment text. This README file explains the implementation details and introduces the repository.

For your convenience, a repository was prepared containing C files, a Makefile and tester-grader scripts with test cases. These files were used to initialize your repository.

Below are the brief explanations about the files included in your repository. For detailed explanations, you should follow the comments inside those files.

* [Makefile](Makefile): The makefile that helps to build, test and clean.

* [main.c](main.c): The C file that contains the main function and the code required to interpret command line arguments.

* [data.h](data.h): Defines the `Instruction` and `VirtualMachine` data types, and constants.

* [vm.h](vm.h): Includes the declaration of the `simulateVM()` function, which is needed to be implemented in [vm.c](vm.c) file by you.

* [vm.c](vm.c): The only file that needs modifying by you. Also, this file is the only file that is going to be used while grading your assignment. Other files are going to be replaced by their originals.

Implementation of `simulateVM()` function is a must since it is going to be used by [main.c](main.c) to simulate the virtual machine. Helper functions are included as hints of a possible design. However, you are free to remove the helper functions and add new ones.

* [test/](test/): The folder that contains the test cases and the scripts that you could use to try those test cases on your executable. Further information is included in the [Test & Grade](#test-&-grade) section below.

# Command Line Arguments
Usage: `./vm.out (ins_inp_file) (simul_outp_file) [vm_inp_file=stdin] [vm_outp_file=stdout]`

* ins_inp_file: The path to the file containing the list of instructions to be loaded to code memory of the virtual machine.

* simul_outp_file: The path to the file to write the simulation output, which contains both code memory and execution history.

* vm_inp_file: The path to the file that is going to be attached as the input stream to the virtual machine. Useful to feed input for `SIO` instructions. Use dash `-` to assign stdin.

* vm_outp_file: The path to the file that is going to be attached as the output stream to the virtual machine. Useful to save the output printed by `SIO` instructions. Use dash `-` to assign stdout.

You are not required to handle command line argument interpretation since it is already implemented inside [main.c](main.c) file.

In the presence of the test cases, an example usage could be given as:
```
$ ./vm.out test/inputs/inp_code_0.txt your_output_dir/simul_out_0.txt test/inputs/inp_vm_0.txt your_output_dir/vm_out_0.txt
```
After the execution of the above bash command, two files would be created in `your_output_dir` folder. These files should be the same as `test/groundtruth/simul_out_0.txt` and `test/groundtruth/vm_out_0.txt`.

# A Note on Output Format
The `diff` command with `--ignore-blank-lines` and `--ignore-all-space` options on will be used while comparing your outputs with the groundtruth. Therefore, you should not spend much time to match the number of spaces included in your output with the ones in the ground truth. However, it is important to write the output in correct order by including required headers (e.g. `***Execution***`).

For example, the following texts has not difference according to `diff` command (with mentioned options on): 

` * * * Execution * * * ` and `***Execution***` 

`***Code Memory***` and `***CodeMemory***` 

However, the following texts differs from each other according to `diff` command: 

`###Execution###` and `***Execution***` 

`# OP R L M` and `Num Operation R L M` 

For further information about diff command:
```
$ man diff
```

# Build & Run
The build is done with the help of the Makefile included in the repository. Following command is enough to build your solution and obtain the executable file `vm.out`:
```
$ make
```
Then, to test your solution, you should use the following command by feeding necessary command line arguments:

```
$ ./vm.out (ins_inp_file) (simul_outp_file) [vm_inp_file=stdin] [vm_outp_file=stdout]
```

For further information about command line arguments, read the [Command Line Arguments](#command-line-arguments) section.

# Test & Grade
Test cases with their ground truth outputs were prepared to help you test your solutions. Also, simple tester and grader scripts are included to allow you run your tests in automated manner.

You could find the input files in [test/inputs/](test/inputs/) folder. The files that your solution should output are included in [test/groundtruth/](test/groundtruth/) folder.

Targets for testing and grading does also exist in the [Makefile](Makefile). The target `run_vm` allows you to run your virtual machine with all the given test cases and creates the outputs of your virtual machine inside [test/outputs/](test/outputs/) folder. The target `grade` runs your virtual machine with all the given test cases, creates the outputs of your virtual machine and compares it with the ground truth outputs which are included in [test/groundtruth/](test/groundtruth/) folder.

Basically, what you should do to get outputs from your virtual machine as a result of feeding the test cases is:
```
$ make run_vm
```

On top of that, if you are willing to compare your outputs with the ground truth outputs and see how many test cases you passed, you should do:
```
$ make grade
```

Although you do not need, you are encouraged to observe the bash scripts [test/run_vm.sh](test/run_vm.sh) [test/grader.sh](test/grader.sh), so that, you could come up with your own ideas to better test your work.

To understand the assignment better and to further test your code, you are highly recommended to prepare new test cases and share them. You could start by writing simple pseduo-code and try to translate it to the language that your virtual machine would interpret. Then, you could proceed by writing functions, passing arguments to your functions, returning values from functions and so on.

## Important Note on Grader
Note that passing all the tests does not imply that you will take full points from the assignment. Different and more complex test cases will be included while grading your assignment. Therefore, try to come up with your own test methods to ensure the correctness of your work.

# Hints
* The functions `fprintf` and `fscanf` are your friends while performing input/output on FILE pointers. For further information about the functions:
```
$ man fprintf
$ man fscanf
```

# Important Note on Submission

Notice that the only file you should modify is [vm.c](vm.c) file since it is the only file that is going to be used while grading your assignment. Other files are going to be replaced by their originals. Therefore, it is important to ensure that the final version for your [vm.c](vm.c) file successfully builds and works as expected with the originals of the other files.

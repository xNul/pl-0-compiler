# Assignment 1
In this assignment, you are going to implement a virtual machine whose specifications are included in the assignment text. This README file explains the implementation details and introduces the repository.

For your convenience, a repository was prepared containing C files, a Makefile and tester-grader scripts with test cases. These files were used to initialize your repository.

Below are the brief explanations about the files included in your repository. For detailed explanations, you should follow the comments inside those files.

* [Makefile](Makefile): The makefile that helps to build and clean.

* [main.c](main.c): The C file that contains the main function and the code required to interpret command line arguments.

* [data.h](data.h): Defines the `Instruction` and `VirtualMachine` data types, and constants.

* [vm.h](vm.h): Includes the declaration of the `simulateVM()` function, which is needed to be implemented in [vm.c](vm.c) file by you.

* [vm.c](vm.c): The only file that needs modifying by you. Also, this file is the only file that is going to be used while grading your assignment. Other files are going to be replaced by their originals.

Implementation of `simulateVM()` function is a must since it is going to be used by [main.c](main.c) to simulate the virtual machine. Helper functions are included as hints of a possible design. However, you are free to remove the helper functions and add new ones.

* [test/](test/): The folder that contains the test cases and the scripts that you could use to try those test cases on your executable. Further information is included in the [README](test/README.md) file inside the [test/](test/) folder.

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
The `diff` command with `--ignore-blank-lines` and `--ignore-all-space` options on will be used while comparing your outputs with the groundtruth. Therefore, you should not spend much time to match the number of spaces included in your output with the ones in the groundtruth. However, it is important to write the output in correct order by including required headers (e.g. `***Execution***`).

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


# Hints
* The functions `fprintf` and `fscanf` are your friends while performing input/output on FILE pointers. For further information about the functions:
```
$ man fprintf
$ man fscanf
```

# Important Note

Notice that the only file you should modify is [vm.c](vm.c) file since it is the only file that is going to be used while grading your assignment. Other files are going to be replaced by their originals. Therefore, it is important to ensure that the final version for your [vm.c](vm.c) file successfully builds and works as expected with the originals of the other files.

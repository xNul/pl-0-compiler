###############################################################################
# ABOUT run_vm.sh                                                             #
###############################################################################

The simple bash script file "run_vm.sh" is prepared to allow you run all 
the test cases and extract their outputs in automated manner. What it
does is to run your virtual machine by feeding the input file paths 
and output file paths.

In tests.txt file, the list of arguments to be fed to your virtual machine
is included. The bash script test.sh runs all the tests included in this
list and stores the output files in the output folder.

Before starting, make sure that your virtual machine executable "vm.out" is
at the same folder with test.sh. Also, if you are willing to save your outputs
in a different directory then current, make sure that the folders in the path of
output files do exist. Then, on the terminal, type "bash test.sh"
to get your outputs.

###############################################################################
# ABOUT grader_sh                                                             #
###############################################################################

On top of "run_vm.sh", the script "grader.sh" allows you to see if you
passed or failed the test cases. What it does is using the "diff" tool
to compare your output with the groundtruth output.

In tests_grader.txt file, the list of arguments to be fed to your virtual
machine and the groundtruth output files are included.

Before starting, make sure that your virtual machine executable "vm.out" is
at the same folder with grader.sh. Also, if you are willing to save your outputs
in a different directory then current, make sure that the folders in the path
of output files do exist. Then, on the terminal, type "bash test.sh"
to test your executable.

Note that passing all the tests does not imply that you would take full points
from the assignment. Different and more complex test cases will be included
while grading your assignment.

# PL/0 Compiler Implementation

An implementation of a PL/0 compiler done throughout a course. It is divided into four different parts:
1. The Virtual Machine - Executes the given instructions.
2. The Lexer - Assigns tokens to the source code.
3. The Parser - Parses the token output by the Lexer into logical units of code.
4. The Code Generator - Takes the units of code from the Parser and translates them into instructions for the CPU.

\#4 combines all previous parts together to compile the PL/0 code and execute it.

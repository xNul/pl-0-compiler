#include <stdio.h>
#include "vm.h"
#include "data.h"

/* ************************************************************************************ */
/* Declarations                                                                         */
/* ************************************************************************************ */

/**
 * Recommended design includes the following functions implemented.
 * However, you are free to change them as you wish inside the vm.c file.
 * */
void initVM(VirtualMachine*);

int readInstructions(FILE*, Instruction*);

void dumpInstructions(FILE*, Instruction*, int numOfIns);

int getBasePointer(int *stack, int currentBP, int L);

void dumpStack(FILE*, int* stack, int sp, int bp);

int executeInstruction(VirtualMachine* vm, Instruction ins, FILE* vmIn, FILE* vmOut);

/* ************************************************************************************ */
/* Global Data and misc structs & enums                                                 */
/* ************************************************************************************ */

/**
 * allows conversion from opcode to opcode string
 * */
const char *opcodes[] = 
{
    "illegal", // opcode 0 is illegal
    "lit", "rtn", "lod", "sto", "cal", // 1, 2, 3 ..
    "inc", "jmp", "jpc", "sio", "sio",
    "sio", "neg", "add", "sub", "mul",
    "div", "odd", "mod", "eql", "neq",
    "lss", "leq", "gtr", "geq"
};

enum { CONT, HALT };

/* ************************************************************************************ */
/* Definitions                                                                          */
/* ************************************************************************************ */

/**
 * Initialize Virtual Machine
 * */
void initVM(VirtualMachine* vm)
{
    if(vm)
    {
        vm->BP = 1;
    }
}

/**
 * Fill the (ins)tructions array by reading instructions from (in)put file
 * Return the number of instructions read
 * */
int readInstructions(FILE* in, Instruction* ins)
{
    // Instruction index
    int i = 0;
    
    while(fscanf(in, "%d %d %d %d", &ins[i].op, &ins[i].r, &ins[i].l, &ins[i].m) != EOF)
    {
        i++;
    }

    // Return the number of instructions read
    return i;
}

/**
 * Dump instructions to the output file
 * */
void dumpInstructions(FILE* out, Instruction* ins, int numOfIns)
{
    // Header
    fprintf(out,
        "***Code Memory***\n%3s %3s %3s %3s %3s \n",
        "#", "OP", "R", "L", "M"
        );

    // Instructions
    int i;
    for(i = 0; i < numOfIns; i++)
    {
        fprintf(
            out,
            "%3d %3s %3d %3d %3d \n", // formatting
            i, opcodes[ins[i].op], ins[i].r, ins[i].l, ins[i].m
        );
    }
}

/**
 * Returns the base pointer for the lexiographic level L
 * */
int getBasePointer(int *stack, int currentBP, int L)
{
    // Based off of syllabus example. (Appendix D)
    int b1 = currentBP;
    
    // Iterate L levels down until we retrieve our desired b1 (base)
    while (L > 0)
    {
        b1 = stack[b1 + 1];
        L--;
    }
    
    return b1;
}

// Function that dumps the whole stack into output file
// Do not forget to use '|' character between stack frames
void dumpStack(FILE* out, int* stack, int sp, int bp)
{
    if(bp == 0)
        return;

    // bottom-most level, where a single zero value lies
    if(bp == 1)
    {
        fprintf(out, "%3d ", 0);
    }

    // former levels - if exists
    if(bp != 1)
    {
        dumpStack(out, stack, bp - 1, stack[bp + 2]);            
    }

    // top level: current activation record
    if(bp <= sp)
    {
        // indicate a new activation record
        fprintf(out, "| ");

        // print the activation record
        int i;
        for(i = bp; i <= sp; i++)
        {
            fprintf(out, "%3d ", stack[i]);
        }
    }
}

/**
 * Executes the (ins)truction on the (v)irtual (m)achine.
 * This changes the state of the virtual machine.
 * Returns HALT if the executed instruction was meant to halt the VM.
 * .. Otherwise, returns CONT
 * */
int executeInstruction(VirtualMachine* vm, Instruction ins, FILE* vmIn, FILE* vmOut)
{
    switch(ins.op)
    {
        // TODO
        default:
            fprintf(stderr, "Illegal instruction?");
            return HALT;
    }

    return CONT;
}

/**
 * inp: The FILE pointer containing the list of instructions to
 *         be loaded to code memory of the virtual machine.
 * 
 * outp: The FILE pointer to write the simulation output, which
 *       contains both code memory and execution history.
 * 
 * vm_inp: The FILE pointer that is going to be attached as the input
 *         stream to the virtual machine. Useful to feed input for SIO
 *         instructions.
 * 
 * vm_outp: The FILE pointer that is going to be attached as the output
 *          stream to the virtual machine. Useful to save the output printed
 *          by SIO instructions.
 * */
void simulateVM(
    FILE* inp,
    FILE* outp,
    FILE* vm_inp,
    FILE* vm_outp
    )
{
    // Read instructions from file
    Instruction ins[MAX_CODE_LENGTH];
    int insCount = readInstructions(inp, ins);

    // Dump instructions to the output file
    dumpInstructions(outp, ins, insCount);

    // Before starting the code execution on the virtual machine,
    // .. write the header for the simulation part (***Execution***)
    fprintf(outp, "\n***Execution***\n");
    fprintf(
        outp,
        "%3s %3s %3s %3s %3s %3s %3s %3s %3s \n",         // formatting
        "#", "OP", "R", "L", "M", "PC", "BP", "SP", "STK" // titles
    );

    // Create a virtual machine
    VirtualMachine vm;

    // Initialize the virtual machine
    initVM(&vm);

    // Fetch&Execute the instructions on the virtual machine until halting
    int vmState = 0;
    while(!vmState)
    {
        // Fetch
        vm.IR = vm.PC;

        // Advance PC - before execution!
        vm.PC++;

        // Execute the instruction
        vmState = executeInstruction(&vm, ins[vm.IR], vm_inp, vm_outp);

        // Print current state
        // TODO: Following is a possible way of printing the current state
        // .. where instrBeingExecuted is the address of the instruction at vm
        // ..  memory and instr is the instruction being executed.
        /* fprintf(
            outp,
            "%3d %3s %3d %3d %3d %3d %3d %3d ",
            instrBeingExecuted, // place of instruction at memory
             opcodes[instr.op], instr.r, instr.l, instr.m, // instruction info
             vm.PC, vm.BP, vm.SP // vm info
        );*/

        // Print stack info
        // TODO

        fprintf(outp, "\n");
    }

    // Above loop ends when machine halts. Therefore, dump halt message.
    fprintf(outp, "HLT\n");
    return;
}
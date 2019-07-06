@ Filename: ARMSimpleBranchingFailing.s
@ Author: Erik W. Failing
@ Email: ewf0002@uah.edu
@ Course: CS309-01 Summer 2019
@
@ Use these command to assemble, link and run this program
@    as -o student_inputA.o student_inputA.s
@    gcc -o student_inputA student_inputA.o
@    ./student_inputA ;echo $?

.global main @ Have to use main because of C library uses. 

main:

@*******************
prompt:
@*******************

@ Ask the user to enter a number.
 
   ldr r0, =strInputPrompt @ Put the address of my string into the first parameter
   bl  printf              @ Call the C printf to display input prompt. 

@*******************
get_input:
@*******************

@ Set up r0 with the address of input pattern

   ldr r0, =numInputPattern @ Setup to read in one number.

@ scanf puts the input value at the address stored in r1. We are going
@ to use the address for our declared variable in the data section - intInput. 
@ After the call to scanf the input is at the address pointed to by r1 which in this
@ case will be intInput. 
 
   ldr r1, =intInput         @ load r1 with the address of where the
                             @ input value will be stored. 
   bl  scanf                 @ scan the keyboard.
 
@*******************
printinputasNum:
@*******************
@ Print the input out as a number.
@ Get the read in value into r1 so that is can be printed using printf.

   ldr r2, =intInput       @ Put the address of the input value into r2
   ldr r1, [r2]            @ Read the contents of intInput and store in r1 so that
                           @ it can be printed. 
   ldr r0, =strOutputNum
   bl  printf

@*******************
numberbranching:
@*******************
   ldr r5, =intInput 
   ldr r6, [r5]
   cmp r6, #100
   bge case_greater_than_or_equal

@*******************
case_less_than:
@*******************
   ldr r0, =strOutputNumLesser
   bl  printf
   b char_prompt

@*******************
case_greater_than_or_equal:
@*******************
   ldr r0, =strOutputNumGreater
   bl  printf

@*******************
char_prompt:
@*******************

@ Ask the user to enter a character.
 
   ldr r0, =charInputPrompt @ Put the address of my string into the first parameter
   bl  printf              @ Call the C printf to display input prompt. 

@*******************
get_char_input:
@*******************

@ Set up r0 with the address of input pattern

   ldr r0, =charInputPattern @ Setup to read in one number.

@ scanf puts the input value at the address stored in r1. We are going
@ to use the address for our declared variable in the data section - intInput. 
@ After the call to scanf the input is at the address pointed to by r1 which in this
@ case will be intInput. 
 
   ldr r1, =charInput         @ load r1 with the address of where the
                             @ input value will be stored. 
   bl  scanf                 @ scan the keyboard.

@*******************
printinputasChar:
@*******************
@ Print the input out as a number.
@ Get the read in value into r1 so that is can be printed using printf.

   ldr r2, =charInput       @ Put the address of the input value into r2
   ldr r1, [r2]            @ Read the contents of intInput and store in r1 so that
                           @ it can be printed. 
   ldr r0, =charOutputNum
   bl  printf

@*******************
characterBranching:
@*******************
   ldr r5, =charInput 
   ldr r6, [r5]
   cmp r6, #90
   ble case_upper

@*******************
case_lower:
@*******************
   cmp r6, #96
   ble case_special
   cmp r6, #123
   bge case_special

   ldr r0, =strOutputCharLowercase
   bl  printf
   b   myexit

@*******************
case_upper:
@*******************
   cmp r6, #64
   ble case_special

   ldr r0, =strOutputCharUppercase
   bl  printf
   b   myexit

@*******************
case_special:
@*******************
   ldr r0, =strOutputCharSpecial
   bl  printf

@*******************
myexit:
@*******************
@ End of my code. Force the exit and return control to OS

   mov r7, #0x01 @SVC call to exit
   svc 0         @Make the system call. 

.data

@ Declare the strings and data needed

.balign 4
strInputPrompt: .asciz "Input the number: "

.balign 4
charInputPrompt: .asciz "Input the chracter: "

.balign 4
strOutputNum: .asciz "The number value is: %d \n"

.balign 4
charOutputNum: .asciz "The character value is: %c \n"

.balign 4
strOutputNumGreater: .asciz "The number is greater than or equal to 100\n"

.balign 4
strOutputNumLesser: .asciz "The number less than 100\n"

.balign 4
strOutputCharUppercase: .asciz "The character is uppercase\n"

.balign 4
strOutputCharLowercase: .asciz "The character is lowercase\n"

.balign 4
strOutputCharSpecial: .asciz "The character is special\n"

@ Format pattern for scanf call.

.balign 4
numInputPattern: .asciz "%d"  @ integer format for read. 

.balign 4
charInputPattern: .asciz "%s"  @ char format for read. 

.balign 4
intInput: .word 0   @ Location used to store the user input. 

.balign 4
charInput: .word 0   @ Location used to store the user input. 

@ Let the assembler know these are the C library functions. 

.global printf
@  To use printf:
@     r0 - Contains the starting address of the string to be printed. The string
@          must conform to the C coding standards.
@     r1 - If the string contains an output parameter i.e., %d, %c, etc. register
@          r1 must contain the value to be printed. 

.global scanf
@  To use scanf:
@      r0 - Contains the address of the input format string used to read the user
@           input value. In this example it is numInputPattern.  
@      r1 - Must contain the address where the input value is going to be stored.
@           In this example memory location intInput declared in the .data section
@           is being used.  
@ 

@end of code. 

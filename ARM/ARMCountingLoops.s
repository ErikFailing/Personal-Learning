@ Filename: Lab4ARMFailing.s
@ Author: Erik W. Failing
@ Email: ewf0002@uah.edu
@ Course: CS309-01 Summer 2019
@ Purpose:  Show CS309 students how to read user inputs from KB. 
@ History:  Changed this code from using the stack pointer to a 
@           locally declared variable. 
@
@ Use these command to assemble, link and run this program
@    as -o Lab4ARMFailing.o Lab4ARMFailing.s
@    gcc -o Lab4ARMFailing Lab4ARMFailing.o
@    ./Lab4ARMFailing ;echo $?

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

   ldr r2, =intInput       @ Put the address of the input value into r2
   ldr r1, [r2]            @ Read the contents of intInput and store in r1 so that
   mov r5, r1              @ it can be printed. Also store value in r5 so r1 can be used for other things

@*******************
validate_input:
@*******************
@ Validates the input to make sure the number is between 2 and 100
   cmp r5, #2
   blt reject_input			@If the number is below 2, branch to reject input and end
   cmp r5, #100
   bgt reject_input			@If the number is above 100, branch to reject input and end
 
@*******************
printinputasNum:
@*******************
@ Print the input out as a number.
@ Get the read in value into r1 so that is can be printed using printf.

   ldr r0, =strOutputNum
   bl  printf

@*******************
setupEvensToNum:
@*******************
@Sets up the registers to go into the even sum loop
   ldr r0, =strOutputEvenNumbers
   bl  printf				@Prints out the header for the even numbers section

   mov r6, #2
   mov r7, #0
   add r7, r6, r7			@Sums the values

   mov r1, r6				@Print the current even number
   ldr r0, =num
   bl  printf

@*******************
printEvensToNum:
@*******************
@Loop until evens count to the number
   add r6, r6, #2			@Go to the next number
   cmp r6, r5				@Check to see if should loop again
   bgt printEvensSum		@If not, branch to print even sum

   add r7, r6, r7			@Sum the values

   mov r1, r6				@Print the current even number 
   ldr r0, =num
   bl  printf

   b   printEvensToNum		@ Loop back to top

@*******************
printEvensSum:
@*******************
   mov r1, r7				
   ldr r0, =strOutputEvenSum
   bl  printf				@Print the even sum

@*******************
setupOddsToNum:
@*******************
   mov r1, r5
   ldr r0, =strOutputOddNumbers
   bl  printf				@Prints out the header for the odd numbers section

   mov r6, #1
   mov r7, #0
   add r7, r6, r7			@Sums the values

   mov r1, r6				@Print the currrent odd number 
   ldr r0, =num
   bl  printf


@*******************
printOddsToNum:
@*******************
@Loop until evens count to the number
   add r6, r6, #2			@Go to the next number
   cmp r6, r5				@Check to see if should loop again
   bgt printOddsSum			@If not, branch and print odd sum

   add r7, r6, r7			@Sum the values

   mov r1, r6				@Print the current odd number 
   ldr r0, =num
   bl  printf

   b   printOddsToNum		@Loop back to top of print odds to num

@*******************
printOddsSum:
@*******************
   mov r1, r7				
   ldr r0, =strOutputOddSum
   bl  printf				@Print the odd sum
   b   myexit				@Skip over reject input and branch to end

@*******************
reject_input:
@*******************
   ldr r0, =strOutputInvalid
   bl  printf				@Print a rejection of input error message

@*******************
myexit:
@*******************
@ End of my code. Force the exit and return control to OS

   mov r7, #0x01 @SVC call to exit
   svc 0         @Make the system call. 

.data

@ Declare the strings and data needed

.balign 4
strInputPrompt: .asciz "Input a number between 2 and 100: "

.balign 4
strOutputNum: .asciz "The number value is: %d \n"

.balign 4
num: .asciz "%d\n"

.balign 4
strOutputEvenNumbers: .asciz "The even numbers from 1 to %d are:\n"

.balign 4
strOutputOddNumbers: .asciz "The odd numbers from 1 to %d are:\n"

.balign 4
strOutputEvenSum: .asciz "The even sum is: %d\n"

.balign 4
strOutputOddSum: .asciz "The odd sum is: %d\n"

.balign 4
strOutputInvalid: .asciz "ERROR: The number entered was invalid\n"

@ Format pattern for scanf call.

.balign 4
numInputPattern: .asciz "%d"  @ integer format for read. 

.balign 4
intInput: .word 0   @ Location used to store the user input. 

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

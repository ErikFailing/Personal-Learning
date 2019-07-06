@ File: helloworld.s
@ Author: Erik W. Failing
@ Email: ewf0002@uah.edu
@ Course: CS309-01 Summer 2019
@ Purpose: Provide enough assembly to allow students to complete an assignment. 
@
@ Use these commands to assemble, link and run the program
@
@  as -o helloworld.o helloworld.s
@  gcc -o helloworld helloworld.o
@ ./helloworld ;echo $?
@
@ If you get an error from the as command AND it does not call out a line
@ number, check to make sure the current directory contains the file.
@
@ If your codes executes with no errors but your string is not printing then
@ you have forgotten the end your string with \n. 

.global main
main:

@use system call to write string to the STDIO

    MOV   r7, #0x04    @ A 4 is a write command and has to be in r7.
    MOV   r0, #0x01    @ 01 is the STD (standard) output device. 
    MOV   r2, #0x16    @ Length of string in Hex.
    LDR   r1, =string1 @ Put address of the start of the string in r1
    SVC   0            @ Do the system call

@ Use the C library to print the second string. 
    LDR  r0, =string2 @ Put address of string in r0
    BL   printf       @ Make the call to printf

@use system call to write string to the STDIO

    MOV   r7, #0x04    @ A 4 is a write command and has to be in r7.
    MOV   r0, #0x01    @ 01 is the STD (standard) output device. 
    MOV   r2, #0x43    @ Length of string in Hex.
    LDR   r1, =string3 @ Put address of the start of the string in r1
    SVC   0            @ Do the system call

@ Force the exit of this program and return command to OS

    MOV  r7, #0X01
    SVC  0

@ Declare the stings

.data       @ Lets the OS know it is OK to write to this area of memory. 
.balign 4   @ Force a word boundry.
string1: .asciz "Erik Wickman Failing\n"  @Length 0x16

.balign 4   @ Force a word boundry
string2: .asciz "ewf0002@uah.edu\n" @Length 0x11

.balign 4   @ Force a word boundry
string3: .asciz "This is my first ARM Assembly program for CS309-01 (Summer 2019).\n" @Length 0x43

.global printf

@end of code and end of file. Leave a blank line after this. 

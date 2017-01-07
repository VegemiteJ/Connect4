# Connect4



Install Instructions
====================================
Two methods for changes and compilation:

1) Use included makefile
2) Use Visual studio project on VSMerge branch

Automatic iterations:
./CompileRun.sh

Manual Builds from src directory:
make

Running in bin directory:
./Connect4.exe (params)

README Additional notes

running make should work.
//Following is for deprecated networking support only. 
If fails due to redefinition of 'select' function, modify the file
/usr/include/sys/select.h and comment out the function:
int select __P (...); on line 73.

Finding host. Server may need to port forward on router for the port they 
want to use. Maybe an inbuilt port works idk. Otherwise follow prompts.
To connect to own computer use ip 'localhost'.

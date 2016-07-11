# Connect4

Automatic iterations:
./CompileRun.sh

Manual Builds from src directory:
make

Running in bin directory:
./Connect4.exe [true if this is server] e.g.
./Connect4.exe true
./Connect4.exe false

README Additional notes

running make should work.
If fails due to redefinition of 'select' function, modify the file
/usr/include/sys/select.h and comment out the function:
int select __P (...); on line 73.

Finding host. Server may need to port forward on router for the port they 
want to use. Maybe an inbuilt port works idk. Otherwise follow prompts.
To connect to own computer use ip 'localhost'.
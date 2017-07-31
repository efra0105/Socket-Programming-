# Socket-Programming-

Socket Programming Assignment

Introduction

The goal of this assignment was to create 3 programs; two of them that are the
client programs and the other is a server program. Client _1 which is machine ‘A’(Volta)
sends a C struct comprising of an integer value, a character value and a float value to the
server process which is machine ‘B’(Rohan). Then the server makes the following changes:
it doubles the integer value, adds 1 to the float value as seen in the image below, and then
increases the character value to the next higher value. Then the server which is machine ‘C’
prints the original value received then modifies them, and transmits it to client_2(Jason).
Finally, client_2 receives those values from the server and terminates all the connections
from all programs.
First we created a folder in Unix named “560” after that we uploaded the files to compile in
the 3 terminals:
-In the Volta server we upload the file client_1.c and compile using this step:
-“gcc client1.c o- client_1” to compile
-“. /client_1 jason.sdsu.edu 1234” to run program
- The connection is established and the data is sent successfully to Jason server.
-While maintaining rohan and Jason terminals open we compile the next program in Jason:
- “gcc server_1.c –lnsl –lsocket –o server_1”
- “./server_1 1234 rohan.sdsu.edu 4321” sends data to rohan server.
-Rohan received data from Jason, modifies it and sends it back:
-“gcc client_2.c –lnsl -lsocket o- client_2”
-“./client_2 4321”
In addition, to make this program work successfully we compile Rohan and Jason first, and
at the end we compile Volta, so that when we enter the information in Volta the data is sent
in to Jason first and then Rohan and the output is given to Jason to terminate all
connections.

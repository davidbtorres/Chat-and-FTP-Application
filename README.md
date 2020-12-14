CS 484: Computer Networks
Project 2: Chat Application
-------------------------------------------------------------
Group Members:
-------------------------------------------------------------
Omar Navarro
David Torres
Anaira Quezada
Anissa Valenzuela 

-------------------------------------------------------------
Program Summary:
-------------------------------------------------------------
This program creates a basic chat application using the UDP protocol.
Each client instance must register and then sign in. 
 
Option register:
 command: $ register,username,password

Option signin:
 command: $ sigin,username,password
 
Once signed in users can select from three options:
   Option 0: recieve a list of all users online
   Option 1: send a message to another user online
   Option "refresh": Issues a blank command

Option 0:
 command: $ 0

Option 1:
 command: $  1,recipientName
 command: $  message intended for sending 

Option refresh:
 command: $ refresh

------------------------------------------------------------
Compilation and Execution:
------------------------------------------------------------
Terminal One:
make

Terminal One:
./Server <Server_IpAddress> <Server_PortNumber>

Terminal Two:
./Client <Server_IpAddress> <Server_PortNumber>

Terminal Three: 
./Client <Server_IpAddress> <Server_PortNumber>

Note: 
./Server must execute before ./Client

-------------------------------------------------------------
Example Execution:
-------------------------------------------------------------
./Client
Command: register,user2,psswd
Message sent
register
From server: register successful
Command: signin,user2,psswd
Message sent
signin,user2
Signed to profile: user2
Command: <user_message>


-------------------------------------------------------------
./Client
Command: register,user1,psswd
Message sent
register
From server: register successful
Command: signin,user1,psswd
Message sent
signin,user1
Signed to profile: user1
Command: 0
Message sent
option0,List of users online:
user2
user1

option0,List of users online:
user2
user1

Command: 1,user2
Message sent
option1
Write your message:
<user_message>
Command: Message sent


-------------------------------------------------------------

./Server
Awaiting client...

Awaiting client...
Buffer: register Recieved from: 
Awaiting client...
Buffer: signin,user2 Recieved from: 
Awaiting client...
Buffer: option0,List of users online:
user2
 Recieved from: 
Awaiting client...
Buffer: register Recieved from: 
Awaiting client...
Buffer: signin,user1 Recieved from: 
Awaiting client...
Buffer: option0,List of users online:
user2
user1
 Recieved from: 
Awaiting client...
Buffer: Message sent Recieved from: 
Awaiting client...


-------------------------------------------------------------
Notes:
-------------------------------------------------------------
-Make sure ./Server is executed before ./Client
-A valid IP adress must be used in order to connect
-The port number must be greater than or equal to 5000
-Messages between clients must not have spaces. 
-In order to receive new messages, command "refresh" must be executed. 












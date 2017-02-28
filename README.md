Info
------------------------------------
Connect4 project using front and backend elements.

Aim of the game is to get 4 of your tokens connected. They can be arranged vertically, horizontally or diagonally.

Tech used:
Alpha Beta search ai written in cpp.

Game playing logic writen in cpp.

Web server in nodejs using net tcp and socket io for the ai and client connections.

Client written in javascript and uses socket io to communicate back to the node js server. 

Build Instructions
-------------------------------------
1) Web server and java script app.

Ensure nodejs is installed and npm is installed.

Clone to directory. In Js_Client folder, run npm install to get all the dependencies. 

Move socket.io.min.js from node_modules\socket.io\node_modules\socket.io-client\dist to public\.

2) Cpp ai server.

Download googletest framework. Open Connect4.sln. Link googletest framework to all projects.

Install gtest adapter from nuget.

Build solution. 


Run Instructions
--------------------------------------
1) Run the CPP server Connect4_runner project

2) Start the nodejs server with nodemon index.js
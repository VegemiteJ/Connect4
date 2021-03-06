var express = require('express');
var app = express();
var http = require('http').createServer(app);
var Server = require('socket.io');
var io = new Server(32455);
var exec = require('child_process').execFile;

// Raw TCP Library - for cpp messages
var net = require('net');

app.use(express.static('public'))

http.listen(3010, function () {
  console.log('Listening on port 3010!')
})


//Configuration
//---------------------------------------------------------
var cppPort = 30455;
var NumSimultaneousUsers = 4;
var firstConnection = true;
var numberActiveUsers = 0;

var serverStart =function(portToUse){
   console.log("Starting new ai instance");
   exec('../Connect4/x64/Debug/Connect4Runner.exe', ['-1',String(portToUse)] ,function(err, data) {  
        console.log(err)
        console.log(data.toString());                       
    });  
}

app.get('/', function (req, res) {
  console.log('Page view: ' + String(numberActiveUsers));
  //res.send('SoonTM')
  if (numberActiveUsers < NumSimultaneousUsers)
  {
    console.log('Sending Board');
    res.sendFile('board.html', {root: __dirname + "/public"} )
    numberActiveUsers = numberActiveUsers + 1;
  } else
  {
    console.log('Sending Busy');
    res.sendFile('Busy.html', {root: __dirname + "/public"} )
  }
});



//Socket handling
//--------------------------------------------------------
var users = [];
var availablePorts = [cppPort, cppPort+1, cppPort+2, cppPort+3];
var availableIndexes = [0, 1, 2, 3];

//Whenever someone connects via JS this gets executed
io.on('connection', function(socket){
  console.log('A user connected');
  console.log('Socket details is: ' + String(socket.request.connection.remoteAddress))
  
  //If there is a space available
  if (numberActiveUsers <= NumSimultaneousUsers)
  {
    console.log('New Player: ' + String(numberActiveUsers));

    //Retrieve the port to use
    var index = availableIndexes.splice(0,1); //extract entry at index 0
    var firstPort = availablePorts[index];    //Parse the port
    console.log('Index: ' + index + ' Port: ' + firstPort);

    //Create the entry and push it to arr of active users
    var entry = new Object();
    entry.sock = socket;
    entry.cppPort = firstPort;
    var newAiSock = new net.Socket();
    entry.aiSock = newAiSock;
    users.push(entry);

    //Start the cpp Server
    serverStart(firstPort);

    //Create the cpp socket after 300ms timeout
    newAiSock.connect(firstPort,'192.168.1.100', function(){
      console.log('connected to cpp');
    })
    newAiSock.on('data',function(data){
      console.log('Received ai move: [' + data + ']');
      var entry = findAIEntry(newAiSock);
      var jsSock = entry.sock;
      sendToJS(jsSock, data);
    });
    newAiSock.on('error',function(){
      console.log('Closed-Error');
    });
    newAiSock.on('end',function(){
      console.log('Closed-End');
    });
    newAiSock.on('close',function(){
      console.log('Closed-Normal');
      //Find and delete the entry
      var entry = findAIEntry(newAiSock);
      console.log('Looking for entry - len = ' + availablePorts.length);
      console.log('Port: ' + entry.cppPort);
      console.log('Type of: ' + String(typeof(availablePorts)));

      console.log('Printing Elements: ');
      for (cnt =0; cnt<availableIndexes.length;cnt++)
      {
        console.log(availablePorts[availableIndexes[cnt]]);
      }
      
      //Find index of used port
      var portInd = availablePorts.indexOf(entry.cppPort);
      console.log('Index of port: '+  portInd);
      var usrInd = users.indexOf(entry);
      console.log('Index of usr: ' + usrInd);
      users.splice(usrInd,1);
      availableIndexes.push(portInd); //Push port as back available

      console.log('Printing Elements: ');
      for (cnt =0; cnt<availableIndexes.length;cnt++)
      {
        console.log(availablePorts[availableIndexes[cnt]]);
      }
      
    });


    socket.on('message',function(data)
    {
      console.log('Received from js: [' + data + '] user: ' + String(socket.request.connection.remoteAddress));
      var entry = findJSEntry(socket);
      var aiSock = entry.aiSock;
      sendToCpp(aiSock,data);
    });

    //Whenever someone disconnects this piece of code executed
    socket.on('disconnect', function () {
      console.log('A user disconnected');
      var entry = findJSEntry(socket);
      var aiSock = entry.aiSock;
      console.log('Sending stop code to ai');
      sendToCpp(aiSock,-1);
      console.log('Sent');
    });

  }
});

function findJSEntry(sock)
{
  //Search for the entry
  for (itr=0; itr<users.length; itr++)
  {
    if (users[itr].sock === sock)
    {
      return users[itr];
    }
  }
  console.log('MISSING AI SOCKET???!??!?!?!?!?!?');
}

function findAIEntry(sock)
{
    //Search for the entry
  for (itr=0; itr<users.length; itr++)
  {
    if (users[itr].aiSock === sock)
    {
      return users[itr];
    }
  }
  console.log('MISSING JS SOCKET???!??!?!?!?!?!?');
}

//Data routers
//--------------------------------------------
function sendToCpp(sock,data)
{
  var sendData = String(data);
  sock.write(sendData);
}

function sendToJS(sock,data)
{
  var sendData = String(data);
  sock.send(sendData);
}
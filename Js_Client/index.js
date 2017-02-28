var express = require('express');
var app = express();
var http = require('http').createServer(app);
var Server = require('socket.io');
var io = new Server(21357);
var exec = require('child_process').execFile;
var firstConnection = true;
// Load the TCP Library - for cpp messages
var net = require('net');

var cppPort = 21556;

var fun =function(){
   console.log("fun() start");
   exec('../Connect4/x64/Debug/Connect4Runner.exe', ['1',String(cppPort)] ,function(err, data) {  
        console.log(err)
        console.log(data.toString());                       
    });  
}

app.get('/', function (req, res) {
  console.log('Page view: ' + String(firstConnection));
  //res.send('SoonTM')
  if (firstConnection)
  {
    res.sendFile('board.html', {root: __dirname + "/public"} )
    //Start the cpp ai
    fun();
  } else
  {
    res.sendFile('Busy.html', {root: __dirname + "/public"} )
  }
})

app.use(express.static('public'))

http.listen(3000, function () {
  console.log('Listening on port 3000!')
})

//Socket handling
//--------------------------------------------------------
var cppClientSocket;
var jsRecvSocket;

var error=true;

//Whenever someone connects this gets executed
io.on('connection', function(socket){
  console.log('A user connected');
  if (firstConnection)
  {
    console.log('First Connection');
    jsRecvSocket = socket;
    firstConnection = false;

    socket.on('message',function(data)
    {
      console.log('Received from js: [' + data + ']');
      sendToCpp(data);
    });

    //Whenever someone disconnects this piece of code executed
    jsRecvSocket.on('disconnect', function () {
      console.log('A user disconnected');
      sendToCpp(-1);
      firstConnection = true;
      console.log('FirstConnection: ' + String(firstConnection));
    });

    //Create the cpp socket
    cppClientSocket = new net.Socket();
    cppClientSocket.connect(cppPort,'192.168.1.100', function(){
      console.log('connected to cpp');
    })

    cppClientSocket.on('data',function(data){
      console.log('Received ai move: [' + data + ']');
      sendToJS(data);
    });

    cppClientSocket.on('error',function(){
      console.log('Closed-Error');
      firstConnection = true;
      jsRecvSocket = null;
    });

    cppClientSocket.on('end',function(){
      console.log('Closed-End');
      firstConnection = true;
      jsRecvSocket = null;
    });

    cppClientSocket.on('close',function(){
      console.log('Closed-Normal');
      firstConnection = true;
      jsRecvSocket = null;
    });

  }
});

function sendToCpp(data)
{
  var sendData = String(data);
  cppClientSocket.write(sendData);
}

function sendToJS(data)
{
  var sendData = String(data);
  jsRecvSocket.send(sendData);
}
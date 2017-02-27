var express = require('express');
var app = express();
var http = require('http').createServer(app);
var Server = require('socket.io');
var io = new Server(21357);

// Load the TCP Library - for cpp messages
var net = require('net');

app.get('/', function (req, res) {
  //res.send('SoonTM')
  if (firstConnection)
  {
    res.sendFile('board.html', {root: __dirname + "/public"} )
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

var firstConnection=true;

cppClientSocket = new net.Socket();
cppClientSocket.connect(21356,'192.168.1.100', function(){
  console.log('connected to cpp');
})

cppClientSocket.on('data',function(data){
  console.log('Received ai move: [' + data + ']');
  sendToJS(data);
});

//Whenever someone connects this gets executed
io.on('connection', function(socket){
  if (firstConnection)
  {
    firstConnection = false;
    jsRecvSocket = socket;
    console.log('A user connected');

    socket.on('message',function(data)
    {
      console.log('Received from js: [' + data + ']');
      sendToCpp(data);
    });

    //Whenever someone disconnects this piece of code executed
    socket.on('disconnect', function () {
      console.log('A user disconnected');
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
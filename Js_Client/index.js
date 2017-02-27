var express = require('express');
var app = express();
var http = require('http').createServer(app);
var Server = require('socket.io');
var io = new Server(21357);


app.get('/', function (req, res) {
  //res.send('SoonTM')
  res.sendFile('board.html', {root: __dirname + "/public"} )
})

app.use(express.static('public'))

http.listen(3000, function () {
  console.log('Listening on port 3000!')
})

//Whenever someone connects this gets executed
io.on('connection', function(socket){
  console.log('A user connected');

  setTimeout(function(){
    socket.send('Example message');
  }, 5000);

  //Whenever someone disconnects this piece of code executed
  socket.on('disconnect', function () {
    console.log('A user disconnected');
  });

});

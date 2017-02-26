var express = require('express')
var app = express()

app.get('/', function (req, res) {
  res.send('SoonTM')
  //res.sendfile('board.html', {root: __dirname + "/public"} )
})

//app.use(express.static('public'))

app.listen(3000, function () {
  console.log('Listening on port 3000!')
})

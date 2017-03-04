var connect4 = document.getElementById("boardGame");
var player1=true;
var height = 6;
var width = 7;

var connection = false;
var gameOver = 0;
var winner = 0;

//Try connection after 400ms
var socket;
setTimeout( function() {
	socket = io('www.connect4.xyz:21357');

	socket.on('connection', function(){
		console.log('ClientConnected')
		connection = true;
	});

	socket.on('message', function(data){
		console.log('Received msg: ' + data);
		
		//Win state
		if (parseInt(data) == -1 || gameOver > 0)
		{
			console.log('Game Over');
			//Received winner
			if (gameOver==1)
			{
				winner = parseInt(data);
				console.log('Winner: ' + winner);
			}
			if (gameOver == 2)	//Plot winning move
			{
				var move = parseInt(data);
				var moveColour = (winner == 1 ? 1 : 0);
				console.log('Colour: ' + moveColour + ' move: ' + move);
				if (winner == 2){
					drawMove(moveColour, move-1);
					window.alert('AI won!');
				} else {
					window.alert('Player won!');
				}
			}
			gameOver++;
		}
		else
		{
			if (!player1)
			{
				player1 = true;
				var move = parseInt(data);
				drawMove(0,move-1);
			}
		}
	});
},400);

var tokens = [];

for (var i = 0; i < width; i++) {
	//Creating new column
	var newCol = document.createElement('div');
	tokens.push(0);
	newCol.id = i;
	newCol.className = 'column';
	connect4.appendChild(newCol);

	//Add clicking listeners
	newCol.addEventListener("click", function(){
		if (player1){
			drawMove(1,this.id);
			var move = parseInt(this.id);
			move = move+1;
			socket.send(move);
		}
		player1 = false;
    });

	for (var j = 0; j < height; j++ ) {
		//Creating slots within column
		var newRow = document.createElement('div');
		newRow.id = 'row' + String(i * height + j);
		newRow.className = 'row';
		newCol.appendChild(newRow);
		//newRow.innerHTML = String(i * height + j);	
	};
};

//Dynamically change the size of each slot based on the 
//number of rows and columns
var columns = document.getElementsByClassName('column');
for (var i = 0; i < columns.length ; i++) {
	columns[i].style.width = String(100 / width) + '%';
};
var rows = document.getElementsByClassName('row');
for (var i = 0; i < rows.length ; i++) {
	rows[i].style.height = String(100 / height) + '%';
};

//Adds blue or red token to the board
function drawMove(isRed, column) {
	if (tokens[column] >= height)
	{
		return;
	}
	var row = height - tokens[column]-1;
	tokens[column]++;
	var slot = document.getElementById('row' + String(column * height + row));

	if (isRed) {
		//slot.style.background = "url('images/red.png') no-repeat center center";
		var circle = document.createElement('div');
		circle.id = 'row' + String(i * height + j) + '_slot';
		circle.className = 'circlered';
		slot.appendChild(circle);
	} else {
		//slot.style.background = "url('images/blue.png') no-repeat center center";
		var circle = document.createElement('div');
		circle.id = 'row' + String(i * height + j) + '_slot';
		circle.className = 'circleblue';
		slot.appendChild(circle);
	}
}
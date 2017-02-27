var socket = io('http://www.connect4.xyz:21357');
var connect4 = document.getElementById("boardGame");
var player1=true;
var height = 7;
var width = 6;

socket.on('connection', function(){
	console.log('ClientConnected')
});
socket.on('message', function(data){
	console.log(data);
	if (!player1)
	{
		player1 = true;
		var move = parseInt(data);
		drawMove(0,move-1);
	}
});

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
		slot.style.background = "url('images/red.png') no-repeat center center";
	} else {
		slot.style.background = "url('images/blue.png') no-repeat center center";
	}
}
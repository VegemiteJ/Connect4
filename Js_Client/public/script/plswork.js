var socket = io('http://www.connect4.xyz:21357');
var connect4 = document.getElementById("boardGame");
var width = 6;
var height = 7;

var tokens = [];
var filledCols = [];

for (var i = 0; i < width; i++) {
	//Creating new column
	var newCol = document.createElement('div');
	tokens.push(0);
	newCol.id = i;
	newCol.className = 'column';
	connect4.appendChild(newCol);

	//Add clicking listeners
	newCol.addEventListener("click", function(){
		drawMove(1,this.id,6);
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
//Handle connection setup
socket.on('connection', function(){
	console.log('ClientConnected')
});
socket.on('message', function(data){
	window.alert(data)
});

//Adds blue or red token to the board
function drawMove(isRed, column, row) {
	var slot = document.getElementById('row' + String(column * height + row));

	if (isRed) {
		slot.style.background = "url('images/red.png') no-repeat center center";
	} else {
		slot.style.background = "url('images/blue.png') no-repeat center center";
	}
}

function sendMove(move)
{

}
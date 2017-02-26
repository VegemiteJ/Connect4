var connect4 = document.getElementById("boardGame");
var width = 6;
var height = 7;

var tokens = [];

for (var i = 0; i < width; i++) {
	//Creating new column
	var newCol = document.createElement('div');
	tokens.push(0);
	newCol.id = 'column' + String(i);
	newCol.className = 'column';
	connect4.appendChild(newCol);

	//Add clicking listeners
	newCol.addEventListener("click", function(){
		window.alert(this.id);
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


drawMove(1, 1, 6);

//Adds blue or red token to the board
function drawMove(isRed, column, row) {
	var slot = document.getElementById('row' + String(column * height + row));

	if (isRed) {
		slot.style.background = "url('images/red.png') no-repeat center center";
	} else {
		slot.style.background = "url('images/blue.png') no-repeat center center";
	}
}
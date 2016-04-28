var boardSize = 3;
var gridSize = 100;
var grid, ctx;

function Point(x, y) {
	this.x = x;
	this.y = y;
};

function Box(x, y, w, h) {
	this.x = x;
	this.y = y;
	this.w = w;
	this.h = h;

	this.containsPoint = function(p) {
		return (p.x >= this.x && p.x <= (this.x + this.w)) && 
		       (p.y >= this.y && p.y <= (this.y + this.h));
	};

	this.getCenter = function() {
		return new Point(this.x + (this.w / 2), this.y + (this.h / 2));
	};
};

// initialize game board
function initGrid() {
	var spacing = 2;
	
	grid = new Array(boardSize);

	for (var i = 0; i < grid.length; i++) {
		grid[i] = new Array(boardSize);

		for (var j = 0; j < grid[i].length; j++) {
			grid[i][j] = new Box(
				i * gridSize + (spacing / 2), 
				j * gridSize + (spacing / 2), 
				gridSize - spacing, 
				gridSize - spacing
			);
		}
	}
};

// updates the game letters if it's our turn and that space isn't occupied
// actual letter drawing is done in the client.js "update" event
function onClick(p) {
	// only allow clicking if it's our turn and the game isn't over
	if (!Client.isMyTurn())
		return;

	var letters = Client.getLetters();
	var player = Client.getPlayer();

	for (var i = 0; i < grid.length; i++)
		for (var j = 0; j < grid[i].length; j++)
			// only make a move if the squre isn't occupied
			if (grid[i][j].containsPoint(p) && letters[i][j] == -1) {
				letters[i][j] = player.letter;
				Client.onMove(letters);
				break;
			}
};

function drawLetter(center, letter) {
	ctx.fillStyle = "red";
	ctx.font = "30px Arial";
	ctx.fillText(letter, center.x - 15, center.y + 15);
};

function drawGrid() {
	var letters = Client.getLetters();

	for (var i in grid)
		for (var j in grid[i]) {
			// draw cell background
			ctx.fillStyle = "#ddd";
			ctx.fillRect(grid[i][j].x, grid[i][j].y, grid[i][j].w, grid[i][j].h);

			// drawe piece if it exists
			if (letters && letters[i][j] != -1)
				drawLetter(grid[i][j].getCenter(), letters[i][j]);
		}
};

function drawBoard() {
	ctx = $("canvas")[0].getContext('2d');

	drawGrid(ctx);

	$("canvas").click(function(click) {
		onClick(new Point(click.offsetX, click.offsetY));
	});
};

$(document).ready(function() {
	Client.setOnUpdate(function() {
		drawGrid();
	});

	initGrid();
	drawBoard();
});






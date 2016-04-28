var boardSize = 13;
var gridSize = 40;
var pieceRadius = gridSize / 4;
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

function StatusUpdate() {
	this.player = -1;
	this.pieces = null;
	this.result = -1;
	this.captures = 0;
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

function fillCircle(center, color, radius) {	
	ctx.fillStyle = color;
	ctx.beginPath();
	ctx.arc(center.x, center.y, radius, 0, 2 * Math.PI, false);
	ctx.closePath();
	ctx.fill();
};

// returns true if the piece at row, r, and column, c, is mine
function pieceIsMine(r, c, pieces) {
	return r >= 0 && 
		   r <= boardSize && 
		   c >= 0 && 
		   c <= boardSize && 
		   pieces[r][c] == Client.getPlayer().color;
};

// returns true if the piece at row, r, and column, c, is my opponent's;
// or false if it's mine or empty
function pieceIsOpponents(r, c, pieces) {
	return r >= 0 && 
		   r <= boardSize && 
		   c >= 0 && 
		   c <= boardSize && 
		   pieces[r][c] != Client.getPlayer().color &&
		   pieces[r][c] != -1;
};

// method derived from
// http://math.hws.edu/eck/cs124/javanotes3/c8/ex-8-6-answer.html
//
// returns true if we are a winner in the given direction
// searches dirX and dirY from the start point, then in the 
// opposite direction, counting each matching piece
function didWinInDirection(pieces, startRow, startCol, dirX, dirY) {
	var count = 1;

	// look in the x, y direction
	var r = startRow + dirX;
	var c = startCol + dirY;

	while (pieceIsMine(r, c, pieces)) {
		count++;
		r += dirX;
		c += dirY;
	}

	// look in the opposite direction
	r = startRow - dirX;
	c = startCol - dirY;

	while (pieceIsMine(r, c, pieces)) {
		count++;
		r -= dirX;
		c -= dirY;
	}

	return count == 5;
};

function didWin(pieces, addedRow, addedCol) {
	return didWinInDirection(pieces, addedRow, addedCol, -1, 0) ||
		   didWinInDirection(pieces, addedRow, addedCol, -1, -1) ||
		   didWinInDirection(pieces, addedRow, addedCol, 0, -1) ||
		   didWinInDirection(pieces, addedRow, addedCol, 1, -1);
};

function isDraw(pieces) {
	for (var i in pieces)
		for (var j in pieces[i]) {
			if (pieces[i][j] == -1)
				return false;
		}
	return pieces && true;
};

// returns the number of captures made my moving one of my pieces to
// "startRow" and "startCol" and in the direction specified by "dirX" and
// "dirY"
// 
// this function will only return either 0 or 1
function getCapturesInDirection(pieces, startRow, startCol, dirX, dirY) {
	var r = startRow;
	var c = startCol;

	// only need to check the first 3 spaces away from the starting point
	for (var i = 1; i <= 3; i++) {
		r += dirX;
		c += dirY;

		// pattern for the first 3 spaces away is (opponent, opponent, me)
		
		// first and second space
		if ((i <= 2) && !(pieceIsOpponents(r, c, pieces)))
			return 0;

		// third space
		if (i == 3 && !pieceIsMine(r, c, pieces))
			return 0;
	}

	return 1;
};

// returns the number of captures that were made by adding a piece
// at "addedRow" and "addedCol"
function getCaptures(pieces, addedRow, addedCol) {
	var count = 0;

	for (var r = -1; r <= 1; r++)
		for (var c = -1; c <= 1; c++)
			count += getCapturesInDirection(pieces, addedRow, addedCol, r, c);

	return count;
};

// returns a StatusUpdate object that will be send to the server
// and relayed back to all clients
//
// @param pieces - the new, updated pieces
// @param addedRow - the index of the row of the piece that was added
// @param addedCol - the index of the column of the piece that was added
function getStatusUpdate(pieces, addedRow, addedCol) {
	var update = new StatusUpdate();

	update.player = Client.getPlayer().number;
	update.pieces = pieces;
	update.captures = getCaptures(pieces, addedRow, addedCol);

	if (didWin(pieces, addedRow, addedCol))
		update.result = Client.getPlayer().color;
	else if (isDraw())
		update.result = "nobody (draw)";
	else
		update.result = -1;

	return update;
};

// updates the game pieces if it's our turn and that space isn't occupied
// actual piece drawing is done in the client.js "update" event
function onClick(p) {
	// only allow clicking if it's our turn and the game isn't over
	if (!Client.isMyTurn() || Client.isGameOver())
		return;

	var pieces = Client.getPieces();
	var player = Client.getPlayer();

	for (var i = 0; i < grid.length; i++)
		for (var j = 0; j < grid[i].length; j++)
			// only make a move if the squre isn't occupied
			if (grid[i][j].containsPoint(p) && pieces[i][j] == -1) {
				pieces[i][j] = player.color;
				Client.onMove(getStatusUpdate(pieces, i, j));
				break;
			}
};

function drawGrid() {
	var pieces = Client.getPieces();

	for (var i in grid)
		for (var j in grid[i]) {
			// draw cell background
			ctx.fillStyle = "#ddd";
			ctx.fillRect(grid[i][j].x, grid[i][j].y, grid[i][j].w, grid[i][j].h);

			// drawe piece if it exists
			if (pieces && pieces[i][j])
				fillCircle(grid[i][j].getCenter(), pieces[i][j], pieceRadius);
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






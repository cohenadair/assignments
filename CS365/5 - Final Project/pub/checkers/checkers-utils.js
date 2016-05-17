// The types of pieces in Checkers. 
var Type = {
	NORMAL: 0,
	KING: 1
};

// The different colors used in Checkers. A variable is used so the
// game's theme could easily be changed.
var Color = {
	NONE: "",
	PIECE_LEFT: "red",
	PIECE_RIGHT: "black",
	PIECE_KING: "#ffcc00",
	BOARD_LIGHT: "#eeeeee",
	BOARD_DARK: "#808080",
	HIGHLIGHT: "#ffffb3"
};

var Board = {
	SIZE: 10,
	SIZE_GRID: 60,
	SIZE_PIECE: 20,
	SPACING: 2,
	COLOR_OCCUPIED: Color.BOARD_DARK,
};

/**
 * StatusUpdate
 */
function StatusUpdate() {
	this.winner = -1;				// who is the winner
	this.result = "waiting";		// the current game result
	this.pieces = null;				// all the pieces
};

/**
 * Point
 */
function Point(x, y) {
	this.x = x;
	this.y = y;
};

Point.prototype.equals = function(point) {
	return this.x == point.x && this.y == point.y;
};

/**
 * Piece
 */
function Piece(color, position) {
	this.type = Type.NORMAL;
	this.color = color;
	this.position = position;
	this.captured = false;
};

Piece.prototype.getCenter = function(grid) {
	return grid[this.position.x][this.position.y].getCenter();
};

Piece.prototype.getBox = function(grid) {
	return grid[this.position.x][this.position.y];
};

Piece.prototype.isSelected = function(grid) {
	return this.getBox(grid).isSelected();
};

Piece.prototype.setSelected = function(grid, selected) {
	this.getBox(grid).setSelected(selected);
};

Piece.prototype.capture = function() {
	this.captured = true;
	this.position = new Point(-1, -1);
};

// Updates the Piece's type (i.e. to Type.KING) if it's new position is
// at the the opposite side of the board.
Piece.prototype.updateType = function() {
	// a piece can never go back from being a king
	if (this.type == Type.KING)
		return;

	// if the piece is at the end of the board, switch it to a king
	if ((this.color == Color.PIECE_RIGHT && this.position.x == 0) ||
		(this.color == Color.PIECE_LEFT && this.position.x == Board.SIZE - 1))
		this.type = Type.KING;
};

/**
 * MovableSpot
 */
function MovableSpot(position, jumpedPieces) {
	this.position = position;
	this.jumpedPieces = jumpedPieces;
};

/**
 * Box
 */
function Box(x, y, w, h, color, onClick) {
	this.x = x;
	this.y = y;
	this.w = w;
	this.h = h;
	this.color = color;
};

// Returns true if the Point object "p" is inside the Box; false otherwise.
Box.prototype.containsPoint = function(p) {
	return (p.x >= this.x && p.x <= (this.x + this.w)) && 
	       (p.y >= this.y && p.y <= (this.y + this.h));
};

// Returns the center of the Box as a Point object.
Box.prototype.getCenter = function() {
	return new Point(this.x + (this.w / 2), this.y + (this.h / 2));
};

// Returns true if the Box is selected; false otherwise.
Box.prototype.isSelected = function() {
	return this.color == Color.HIGHLIGHT;
};

Box.prototype.setSelected = function(selected) {
	this.color = selected ? Color.HIGHLIGHT : Color.BOARD_DARK;
};



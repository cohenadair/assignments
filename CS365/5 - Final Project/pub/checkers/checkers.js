var ctx;				// canvas context
var grid;				// 2D array of Box
var pieces;				// array of Piece
var selectedPiece;		// keeps track of the selected piece
var movableSpots;		// the movable spots for the selected piece
var visitedSpots; 		// used as a cache when searching for movable spots
var kingImage;			// the image of the crown used for kinged pieces


/**
 * Initializing
 */

function resetVisitedSpots() {
	visitedSpots = new Array(Board.SIZE);

	for (var c = 0; c < visitedSpots.length; c++) {
		visitedSpots[c] = new Array(Board.SIZE);

		for (var r = 0; r < visitedSpots[c].length; r++)
			visitedSpots[c][r] = false;
	}
};

// Initializes a single board item. Either a spot, or a piece.
function initItem(c, r, color) {
	// set the new grid item's position and color
	grid[c][r] = new Box(
		c * Board.SIZE_GRID + (Board.SPACING / 2),
		r * Board.SIZE_GRID + (Board.SPACING / 2),
		Board.SIZE_GRID - Board.SPACING,
		Board.SIZE_GRID - Board.SPACING,
		color
	);

	// add a piece to a starting position if needed
	if (color == Board.COLOR_OCCUPIED) {
		// first 3 columns
		if (c < 3)
			pieces.push(new Piece(Color.PIECE_LEFT, new Point(c, r)));
		// last 3 columns
		else if (c > 6)
			pieces.push(new Piece(Color.PIECE_RIGHT, new Point(c, r)));
	}
};

function initBoard() {
	grid = new Array(Board.SIZE);
	pieces = new Array();

	for (var c = 0; c < grid.length; c++) {
		grid[c] = new Array(Board.SIZE);

		// start on a different color for each column
		var boardColor = (c % 2 == 0) ? Color.BOARD_LIGHT : Color.BOARD_DARK;

		for (var r = 0; r < grid[c].length; r++) {
			initItem(c, r, boardColor);

			// toggle the board color for each grid item
			boardColor = (boardColor == Color.BOARD_LIGHT) ?
				Color.BOARD_DARK :
				Color.BOARD_LIGHT;
		}
	}
};

function init() {
	ctx = $("canvas")[0].getContext('2d');

	initBoard();

	$("canvas").click(function(click) {
		onClick(new Point(click.offsetX, click.offsetY));
	});
};

/**
 * Drawing
 */

// Resets all selected or highlighed board spots.
function resetSelection() {
	for (var c in grid)
		for (var r in grid[c])
			if (grid[r][c].isSelected())
				grid[r][c].setSelected(false);
};

function drawBoard() {
	for (var c in grid) {
		for (var r in grid[c]) {
			var b = grid[c][r];
			ctx.fillStyle = b.color;
			ctx.fillRect(b.x, b.y, b.w, b.h);
		}
	}
};

function drawPieces() {
	for (var i in pieces) {
		if (pieces[i].captured)
			continue;

		var center = pieces[i].getCenter(grid);

		ctx.fillStyle = pieces[i].color;
		ctx.beginPath();
		ctx.arc(center.x, center.y, Board.SIZE_PIECE, 0, 2 * Math.PI, false);
		ctx.closePath();
		ctx.fill();

		pieces[i].updateType();

		// draw the crown image if the piece is a king
		if (pieces[i].type == Type.KING) {
			ctx.drawImage(
				kingImage,
				center.x - Board.SIZE_GRID / 2,
				center.y - Board.SIZE_GRID / 2
			);
		}
	}
};

function draw() {
	drawBoard();
	drawPieces();
};

function redraw() {
	ctx.clearRect(0, 0, 600, 600);
	draw();
};

/**
 * Gameplay
 */

function nextTurn() {
	selectedPiece = null;
	movableSpot = null;

	resetSelection();
	redraw();
};

function getPieceClicked(pointClicked) {
	for (var i in pieces)
		if (!pieces[i].captured && pieces[i].getBox(grid).containsPoint(pointClicked))
			return pieces[i];

	return null;
};

function getSpotClicked(pointClicked) {
	for (var c in grid)
		for (var r in grid[c])
			if (grid[c][r].containsPoint(pointClicked))
				return new Point(c, r);

	return null;
};

function getPieceAtPosition(gridPosition) {
	for (var i in pieces)
		if (!pieces[i].captured && pieces[i].position.equals(gridPosition))
			return pieces[i];

	return null;
};

function isInBoardBounds(r, c) {
	return (c < grid.length && c >= 0 && r < grid.length && r >= 0);
};

// A recursive function that gets all possible movable spots for
// the given piece.
//
// The function works by recursivly checking the spot at each
// direction (top left, top right, bottom left, bottom right) are
// movable from the given Piece. If it is, it is added to result
// array, and then this function is called for the spot that was
// just added. This mimics the starting Piece being moved to that
// spot.
//
// @param startPiece - The Piece object that will be moving.
// @param spot - A Point object of the current grid location.
// @param jumpedPieces - An array of Piece objects that have been
//                       jumped by moving to the current spot.
function getMovableSpotsHelper(startPiece, spot, jumpedPieces) {
	var arr = new Array();
	var r, c, p, jumpPiece, isEmpty;

	// return if out of bounds or if we've visited this spot before
	if (!isInBoardBounds(spot.x, spot.y) || visitedSpots[spot.x][spot.y])
		return arr;

	thisPiece = getPieceAtPosition(spot);
	isEmpty = (thisPiece == null);

	// return if there's a piece at this spot and it's not the first call
	if (!isEmpty && !thisPiece.position.equals(startPiece.position))
		return arr;

	arr.push(new MovableSpot(spot, jumpedPieces));

	visitedSpots[spot.x][spot.y] = true;

	var getSpotsInDir = function(dir) {
		r = parseInt(spot.y) + dir.y;
		c = parseInt(spot.x) + dir.x;
		p = new Point(c, r);

		if (isInBoardBounds(c, r)) {
			jumpPiece = getPieceAtPosition(p);

			if (jumpPiece) {
				if (jumpPiece.color != startPiece.color) {
					arr = arr.concat(getMovableSpotsHelper(
						startPiece,
						new Point(c + dir.x, r + dir.y),
						jumpedPieces.concat([jumpPiece])
					));
				}

			// add the empty only if the current spot is not empty
			} else if (!isEmpty) {
				// spot is empty, add spot
				arr.push(new MovableSpot(p, jumpedPieces));
			}
		}
	}

	// checks all 4 directs for KING
	if (startPiece.type == Type.KING) {
		getSpotsInDir(new Point(1, -1));
		getSpotsInDir(new Point(1, 1));
		getSpotsInDir(new Point(-1, -1));
		getSpotsInDir(new Point(-1, 1));

	// check right direction for pieces on the left side of the board
	} else if (startPiece.color == Color.PIECE_LEFT) {
		getSpotsInDir(new Point(1, -1));
		getSpotsInDir(new Point(1, 1));

	// check left direction for pieces on the right side of the board
	} else if (startPiece.color == Color.PIECE_RIGHT) {
		getSpotsInDir(new Point(-1, -1));
		getSpotsInDir(new Point(-1, 1));
	}

	return arr;
};

// See getMovableSpotsHelper
function getMovableSpots(piece) {
	if (!piece)
		return null;

	resetVisitedSpots();
	return getMovableSpotsHelper(piece, piece.position, new Array());
};

function movePiece(toSpot) {
	// capture all jumped pieces
	for (var j in toSpot.jumpedPieces)
		toSpot.jumpedPieces[j].capture();

	selectedPiece.position = toSpot.position;
	nextTurn();

	// send updates to server
	var update = new StatusUpdate();
	update.pieces = pieces;
	Client.sendUpdate(update);
};

function onClickPiece(clickedPiece) {
	// selects or deselects the given piece and all its movable spots
	var update = function(piece, selected) {
		clickedPiece.setSelected(grid, selected);
		selectedPiece = piece;
		movableSpots = getMovableSpots(piece);

		// if there are movable spots, select them
		if (movableSpots) {
			for (var i in movableSpots) {
				var c = movableSpots[i].position.x;
				var r = movableSpots[i].position.y;
				grid[c][r].setSelected(selected);
			}
		} else
			resetSelection();
	};

	// if the Piece clicked is selected, deselect it
	if (clickedPiece.isSelected(grid))
		update(null, false);

	// if the Piece clicked isn't select and there isn't already one selected
	// select the clicked Piece
	else if (!selectedPiece)
		update(clickedPiece, true);

	redraw();
};

// Triggered when an empty spot is clicked (i.e. when moving a piece).
function onClickEmpty(pointClicked) {
	var spotClicked = getSpotClicked(pointClicked);

	for (var i in movableSpots)
		if (movableSpots[i].position.equals(spotClicked)) {
			movePiece(movableSpots[i]);
			break;
		}
};

function isMyTurn() {
	return Client.turn == Client.player.socketId;
};

function onClick(p) {
	if (!isMyTurn())
		return;

	var clickedPiece = getPieceClicked(p);

	if (clickedPiece) {
		if (clickedPiece.color == Client.player.color)
			onClickPiece(clickedPiece, movableSpots);
	} else if (selectedPiece)
		// if a Piece wasn't clicked, but there is one selected,
		// check for a valid
		onClickEmpty(p, movableSpots);
};

function setTurnDiv(text) {
	$("#whos-turn").html(text);
};

function updateDivs() {
	if (Client.player == -1)
		setTurnDiv("The game is full");
	else if (Client.player.socketId == Client.turn)
		setTurnDiv("It is YOUR turn");
	else
		setTurnDiv("It is NOT your turn");

	$("#color").html("You are " + Client.player.color);
};

$(document).ready(function() {
	kingImage = new Image();
	kingImage.src = "checkers/king.png";
	kingImage.onload = function() {
		init();
		draw();
	};

	//handle Chat message send
	$('#chatButton').click(function() {
	    console.log("click worked");
			var msg = $('#message').val();
	    Client.sendMessage(msg);
	});

	Client.onPlayerConnect = function() {
		updateDivs();
		Client.hideLogin();
		Client.showGame();
	};

	Client.onReceiveUpdate = function(data) {
		Client.turn = data.turn;
		updateDivs();

		// reset pieces one var at a time
		// this is because the Piece prototypes aren't passed
		// to and from the server
		for (var i in pieces) {
			pieces[i].type = data.pieces[i].type;
			pieces[i].color = data.pieces[i].color;
			pieces[i].position.x = data.pieces[i].position.x;
			pieces[i].position.y = data.pieces[i].position.y;
			pieces[i].captured = data.pieces[i].captured;
		}

		redraw();
	};
});

var socket = io();
var me = null;
var turn = null;
var pieces = null;
var onUpdate = null;
var status = -1;

socket.on("confirmConnection", function(data) {
	me = data.me;
	pieces = data.pieces;
	turn = data.turn;

	onUpdate();
	showCaptures(null, null);
	showStatus();
	showOpponent(data.opponentConnected);
	showMessage();
	showTurn();
});

socket.on("playerDisconnect", function() {
	showOpponent(false);
	showTurn(null);
});

socket.on("playerConnect", function(data) {
	turn = data.turn;
	showOpponent(data.opponentConnected);
	showTurn();
});

socket.on("update", function(data) {
	pieces = data.pieces;
	turn = data.turn;
	status = data.result;

	onUpdate();
	showCaptures(data.p1, data.p2);
	showStatus();
	showTurn();
});

function isGameOver() {
	return status != -1;
};

// returns a color class based on the provided player
function getClass(player) {
	if (player && player != -1)
		return player.color == "BLUE" ? "blue" : "red";
	return "black";
};

// utility function to initilize a message <div>
function showDiv(selector, cls, text) {
	$(selector).removeClass();
	$(selector).addClass(cls);
	$(selector).html(text);
};

function showCaptures(p1, p2) {
	var getText = function(p) {
		return p.color + " has made " + p.captures + " captures";
	};

	// defaults if both players aren't yet connected
	p1 = p1 ? p1 : { color:"RED", captures:0 };
	p2 = p2 ? p2 : { color:"BLUE", captures:0 };

	showDiv("#p1-caps", getClass(p1), getText(p1));
	showDiv("#p2-caps", getClass(p2), getText(p2));
};

function showStatus() {
	showDiv(
		"#status", 
		"black", 
		"The winner is " + (isGameOver() ? status : "in progress")
	);
};

function showMessage() {
	showDiv(
		"#msg", 
		getClass(me), 
		me ? "You are " + me.color : "Game is full"
	);
};

function showOpponent(connected) {
	showDiv(
		"#opponent", 
		connected ? "lime" : "red", 
		"Oppenent is " + (connected ? "connected" : "not connected")
	);
};

function showTurn() {
	showDiv(
		"#turn", 
		isGameOver() ? "black" : getClass(turn), 
		isGameOver() ? "GAME OVER" : "It is " + (turn != -1 ? turn.color : "nobody") + "'s turn"
	);
};

function makeMove(statusUpdate) {
	socket.emit("move", statusUpdate);
};

// to be used outside of client.js
// this isn't required, but it makes method calls from other files
// more organized and clear
var Client = {
	getPieces: function() {
		return pieces;
	},

	getPlayer: function() {
		return me;
	},

	setOnUpdate: function(onUpdateCallback) {
		onUpdate = onUpdateCallback;
	},

	onMove: function(statusUpdate) {
		makeMove(statusUpdate);
	},

	isMyTurn: function() {
		return me.number == turn.number;
	},

	isGameOver: function() {
		return isGameOver();
	}
};



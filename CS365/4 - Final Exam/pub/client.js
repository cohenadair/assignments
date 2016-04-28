var socket = io();
var me = null;
var turn = null;
var letters = null;
var isOpponentConnected = false;
var onUpdate = null;

socket.on("onConnect", function(data) {
	me = data.me;
	isOpponentConnected = data.bothPlayersConnected;
	letters = data.letters;
	turn = data.turn;

	updateGame();
});

socket.on("onPlayerConnectionUpdate", function(data) {
	isOpponentConnected = data.bothPlayersConnected;
	letters = data.letters;
	turn = data.turn;

	updateGame();
});

socket.on("onUpdate", function(data) {
	letters = data.letters;
	turn = data.turn;

	updateGame();
});

function updateGame() {
	if (me == null) {
		showGameMessage("Game is full");
		$("#game").hide();
		return;
	}

	if (!isOpponentConnected) {
		showGameMessage("Waiting for opponent");
		$("#game").hide();
	} else {
		$("#game-msg").hide();
		$("#game").show();
		$("#turn").text("Is is " + turn.letter + "'s turn");
		$("#me").text("You are " + me.letter);
	}

	onUpdate();
};

function showGameMessage(msg) {
	$("#game-msg").show();
	$("#game-msg").text(msg);	
};

var Client = {
	// called in game.js
	setOnUpdate: function(onUpdateCallback) {
		onUpdate = onUpdateCallback;
	},

	getLetters: function() {
		return letters;
	},

	getPlayer: function() {
		return me;
	},

	isMyTurn: function() {
		return me.letter == turn.letter;
	},

	onMove: function(letters) {
		socket.emit("playLetter", letters);
	}
};

$(document).ready(function() {
	$("#reset").click(function() {
		socket.emit("reset");
	});
});



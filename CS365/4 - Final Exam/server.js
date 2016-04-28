// Node modules
var express = require("express");
var socketio = require("socket.io");
var http = require("http");
var app = express();
var server = http.Server(app);
var io = socketio(server);

app.use(express.static("pub"));

server.listen(4444, eventHandlers);

function eventHandlers() {
	io.on("connection", function(socket) {
		addPlayer(socket);

		socket.on("disconnect", function() {
			removePlayer(socket);
		});

		socket.on("playLetter", function(data) {
			letters = data;
			playLetter();
		});

		socket.on("reset", function() {
			initLetters();
			playLetter();
		});
	});
};

var mPlayer = null;
var oPlayer = null;
var letters = null;

// initialize letters
function initLetters() {
	letters = new Array(3);
	for (var i = 0; i < 3; i++) {
		letters[i] = new Array(3);
		for (var j = 0; j < 3; j++)
			letters[i][j] = -1;
	}
}

initLetters();

function Player(id, letter) {
	this.id = id;
	this.letter = letter;
	this.turn = false;
};

function addPlayer(socket) {
	if (!mPlayer) {
		mPlayer = new Player(socket.id, "M");
		onConnect(socket, mPlayer);
	} else if (!oPlayer) {
		oPlayer = new Player(socket.id, "O");
		onConnect(socket, oPlayer);
	} else
		onConnect(socket, null);
};

function removePlayer(socket) {
	if (mPlayer && socket.id == mPlayer.id)
		mPlayer = null;
	else if (oPlayer && socket.id == oPlayer.id)
		oPlayer = null;

	onPlayerConnectionUpdate(socket);
};

function bothPlayersConnected() {
	return mPlayer != null && oPlayer != null;
};

function playLetter(socket) {
	io.emit("onUpdate", {
		letters: letters,
		turn: toggleTurn()
	});
};

function onConnect(socket, player) {
	socket.emit("onConnect", {
		me: player,
		bothPlayersConnected: bothPlayersConnected(),
		letters: letters,
		turn: getTurn()
	});

	onPlayerConnectionUpdate(socket);
};

function onPlayerConnectionUpdate(socket) {
	socket.broadcast.emit("onPlayerConnectionUpdate", {
		bothPlayersConnected: bothPlayersConnected(),
		letters: letters,
		turn: getTurn()
	});
};

function getTurn() {
	if (!mPlayer || !oPlayer)
		return null;

	if (mPlayer.turn)
		return mPlayer;
	else if (oPlayer.turn)
		return oPlayer;

	mPlayer.turn = true;
	return mPlayer;
};

function toggleTurn() {
	if (!mPlayer || !oPlayer)
		return null;

	if (mPlayer.turn) {
		mPlayer.turn = false;
		oPlayer.turn = true;
		return oPlayer;
	} else if (oPlayer.turn) {
		oPlayer.turn = false;
		mPlayer.turn = true;
		return mPlayer;
	}

	return mPlayer;
};


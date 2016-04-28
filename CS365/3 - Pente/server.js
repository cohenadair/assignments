// Node modules
var express = require("express");
var socketio = require("socket.io");
var http = require("http");
var app = express();
var server = http.Server(app);
var io = socketio(server);

app.use(express.static("pub"));

// Pente modeuls
var model = require("./model.js");

server.listen(4444, eventHandlers);

function eventHandlers() {
	io.on("connection", function(socket) {
		addPlayer(socket);

		socket.on("move", function(data) {
			handleMove(socket, data);
		});

		socket.on("disconnect", function() {
			removePlayer(socket);
		});	
	});
};

function addPlayer(socket) {
	// confirmation for new player
	socket.emit("confirmConnection", {
		me: model.addPlayer(socket), 
		opponentConnected: model.areBothPlayersConnected(),
		turn: model.getStartTurn(),
		pieces: model.pieces
	});

	// alert other players that a new player connected
	socket.broadcast.emit("playerConnect", {
		opponentConnected: model.areBothPlayersConnected(),
		turn: model.getStartTurn()
	});
};

function removePlayer(socket) {
	model.removePlayer(socket);
	socket.broadcast.emit("playerDisconnect"); // notify remaining players
}

function handleMove(socket, data) {
	model.pieces = data.pieces;

	var player = model.getPlayer(data.player);

	player.captures += data.captures;
	if (player.captures >= 5)
		data.result = player.color;

	io.emit("update", {
		pieces: model.pieces,
		turn: model.nextPlayer(),
		result: data.result,
		p1: model.p1,
		p2: model.p2
	});

	if (data.result != -1)
		model.reset();
};







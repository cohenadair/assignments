//This part is the same as usual...
var express = require("express");
var app = express();

var http = require("http");

//We are getting an instance of a Node HTTP (web) server here.
//We are also telling it to connect up with our Express application,
//so it can handle requests.
var server = http.Server(app);

//On command prompt, we need to do "npm install socket.io"
var socketio = require("socket.io");

//instantiates our 'io' instance, and also connects it up with the HTTP
//server we already created.
var io = socketio(server);

//Just for static files (like usual).  Eg. index.html, client.js, etc.
app.use(express.static("pub"));

// used to keep track of current location
var STEP = 50;
var left = 0;

server.listen(4444, function() {
	io.on("connection", function(socket) {
		// initialize client on connection
		move(left);

		socket.on("tugLeft", function() {
			move(left - STEP);
		});

		socket.on("tugRight", function() {
			move(left + STEP);
		})
	});	
});

function move(newLeft) {
	left = newLeft;
	
	// game over
	if (left != 0 && (Math.abs(left / STEP) == 10)) {
		left = 0;
		io.emit("done", left < 0 ? "left" : "right");
	}

	io.emit("move", left);
};




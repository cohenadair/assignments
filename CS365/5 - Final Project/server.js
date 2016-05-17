// Checkers modules
var login = require("./login.js");
var players = require("./players.js");

// Node modules
var mongoClient = require("mongodb").MongoClient;
var express = require("express");
var http = require("http");
var socketIo = require("socket.io");

var app = express();
var server = http.Server(app);
var io = socketIo(server);

var db;
var url = 'mongodb://localhost:27017/checkerUsers';

app.use(express.static("pub"));

io.on("connection", function(socket) {
	console.log("Someone Connected");

	socket.on("disconnect", function() {
		console.log("Someone left");
		players.removePlayer(socket.id);
	});

	socket.on("addUser", function(user, onFinish) {
		login.insertUser(db, user, function(result, msg) {
			onFinish(result, msg);
		});
	});

	//Handling new messages in chat
	socket.on("newMessage", function(data) {
			io.emit("updateDialogue", data);
	});

	socket.on("login", function(login_info, onAddPlayerCallback) {
        var username = login_info.username;
        var password = login_info.password;
        console.log("Username: " + username + ", Password: " + password);
        // check if user/pass combination is correct

        // assume login is correct
        // add player and send result to back to client
        login.loginUser(db, login_info, function (result, msg) {
            if (!result) {
            	onAddPlayerCallback({success: false, msg: "Username or password is Incorrect"});
            } else {
            	
                if (players.areBothConnected()) {
    	        	players.p1.turn = true;
    		    }
    		
    	        onAddPlayerCallback({
    	        	readyToStart: players.areBothConnected(),
    	        	player: players.addPlayer(socket.id),
    	        	turn: players.getTurn(),
                    success: true
    	        });
    	
    	        socket.broadcast.emit("onOpponentConnect", {
    	        	readyToStart: players.areBothConnected(),
    	        	turn: players.getTurn()
            	});
            	
            }  
        });
    });

    socket.on("update", function(data) {
    	io.emit("update", {
    		turn: players.getNextTurn(),
    		pieces: data.pieces
    	});
    });
});

mongoClient.connect(url, function(err, database) {
	if (err)
		throw err;

	db = database;
	console.log("We connected to Mongo");

	server.listen(8026, function() {
		console.log("Server is ready");
	})
});

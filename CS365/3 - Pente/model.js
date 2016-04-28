function Player(number, color) {
	this.number = number;
	this.color = color;
	this.turn = false;
	this.captures = 0;
	this.socketId = -1;
	this.isConnected = function() {
		return this.socketId != -1;
	};
};

var Model = function() {
	this.reset();
};

Model.prototype.reset = function() {
	// reset players
	this.p1 = new Player(1, "RED");
	this.p2 = new Player(2, "BLUE");

	// initialize the board pieces
	this.pieces = new Array(13);
	for (var i = 0; i < this.pieces.length; i++) {
		this.pieces[i] = new Array(13);
		for (var j = 0; j < this.pieces[i].length; j++)
			this.pieces[i][j] = -1;
	}
};

// returns the player whose turn it is; or null if there aren't two
// players connected
Model.prototype.getStartTurn = function() {
	if (!this.areBothPlayersConnected())
		return -1;

	this.p1.turn = true;
	return this.p1;
};

Model.prototype.nextPlayer = function() {
	// toggle player turn values
	this.p1.turn = !this.p1.turn;
	this.p2.turn = !this.p2.turn;
	return this.p1.turn ? this.p1 : this.p2;
};

// returns a Player object of the new player or null if the game is full
// @param socket - the socket for the player to be added.
Model.prototype.addPlayer = function(socket) {
	if (!this.p1.isConnected()) {
		this.p1.socketId = socket.id;
		return this.p1;
	}
	
	if (!this.p2.isConnected()) {
		this.p2.socketId = socket.id;
		return this.p2;
	}

	// set player 1 to get the first move
	if (this.areBothPlayersConnected())
		this.p1.turn = true;
	
	return null;
};

// removes the player at the given socket
// @param socket - the socket for the player to be removed
Model.prototype.removePlayer = function(socket) {
	if (socket.id == this.p1.socketId)
		this.p1.socketId = -1;
	else
		this.p2.socketId = -1;
};

// returns true there are 2 players connected; false otherwise
Model.prototype.areBothPlayersConnected = function() {
	return this.p1.isConnected() && this.p2.isConnected();
};

Model.prototype.getPlayer = function(playerNumber) {
	return playerNumber == 1 ? this.p1 : this.p2;
};

module.exports = new Model();



function Player(color) {
	this.socketId = -1;
	this.turn = false;
	this.color = color;
};

Player.prototype.isConnected = function() {
	return this.socketId != -1;	
};

Player.prototype.connect = function(socketId) {
	this.socketId = socketId;
};

Player.prototype.disconnect = function() {
	this.socketId = -1;
};

function Players() {
	this.p1 = new Player("black");
	this.p2 = new Player("red");
};

Players.prototype.areBothConnected = function() {
	return this.p1.isConnected() && this.p2.isConnected();
};

// Returns the new player was added or -1 if the game is full.
Players.prototype.addPlayer = function(socketId) {
	if (!this.p1.isConnected()) {
		this.p1.connect(socketId);
		return this.p1;
	}

	if (!this.p2.isConnected()) {
		this.p2.connect(socketId);
		return this.p2;
	}

	console.log("Game is full");
	return -1;
};

Players.prototype.removePlayer = function(socketId) {
	if (this.p1.socketId == socketId)
		this.p1.disconnect();
	else if (this.p2.socketId == socketId)
		this.p2.disconnect();
};

Players.prototype.get = function(socketId) {
	if (this.p1.socketId == socketId)
		return this.p1;
	else if (this.p2.socketId == socketId)
		return this.p2;
	return -1;
};

Players.prototype.getTurn = function() {
	if (!this.p1.isConnected() || !this.p2.isConnected())
		return -1;

	return this.p1.turn ? this.p1.socketId : this.p2.socketId;
};

Players.prototype.getNextTurn = function() {
	this.p1.turn = !this.p1.turn;
	this.p2.turn = !this.p2.turn;
	return this.p1.turn ? this.p1.socketId : this.p2.socketId;
};

module.exports = new Players();

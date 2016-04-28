var express = require("express");
var server = express();

bodyParser = require("body-parser");
server.use(bodyParser.urlencoded({extended: false}));

server.use("/postupdate", function(req, res) {
	handlePost(req, res);
	res.end();
});

server.use("/getupdate", function(req, res) {
	handleGet(req, res);
	res.end();
});

// must come AFTER the check for /vote URL
server.use(express.static("pub"));
server.listen(8080);

// initialize results
var NUMBER_OF_TEAMS = 4;
var results = new Array(NUMBER_OF_TEAMS);

for (var i =0; i < NUMBER_OF_TEAMS; i++) {
	results[i] = new Array(NUMBER_OF_TEAMS);
	for (var j = 0; j < NUMBER_OF_TEAMS; j++)
		results[i][j] = "";
}

function handlePost(req, res) {
	if (req.body.result == "win") {
		results[req.body.team1][req.body.team2] = "win";
		results[req.body.team2][req.body.team1] = "lose";
	} else if (req.body.result == "draw") {
		results[req.body.team1][req.body.team2] = "draw";
		results[req.body.team2][req.body.team1] = "draw";
	}

	res.json(results);
}

function handleGet(req, res) {
	res.json(results);
}


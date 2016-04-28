var PIZZA = "pizza";
var SANDWICHES = "sandwiches";
var BROWNIES = "brownies";

var results = new Array();
results[PIZZA] = 0;
results[SANDWICHES] = 0;
results[BROWNIES] = 0;

function handleResults(req, res) {
	results[req.body.lunch_choice]++;

	res.write(PIZZA + ": " + results[PIZZA] + "\n");
	res.write(SANDWICHES + ": " + results[SANDWICHES] + "\n");
	res.write(BROWNIES + ": " + results[BROWNIES] + "\n");
}

var express = require("express");
var server = express();

bodyParser = require("body-parser");
server.use(bodyParser.urlencoded({extended: false}));

server.use("/vote", function(req, res) {
	handleResults(req, res);
	res.end();
});

// must come AFTER the check for /vote URL
server.use(express.static("./pub"));

server.listen(8080);
console.log("Server is now running on port 8080.");
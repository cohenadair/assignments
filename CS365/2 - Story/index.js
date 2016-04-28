function Node(question, options, optionNodes, image) {
	this.question = question;
	this.options = options;
	this.optionNodes = optionNodes;
	this.img = image;
}

var starve = new Node(
	"John is sad and hungry.",
	null,
	null,
	"sad.png"
);

var peanutButter = new Node(
	"Should he buy peanut butter?",
	["Yes", "No"],
	[
		new Node("John is happy eating peanut butter on his bread.", null, null, "happy.png"),
		new Node("John is said eating plain bread.", null, null, "sad.png")
	]
);

var steak = new Node(
	"Does John want BBQ sauce?",
	["Yes", "No"],
	[
		new Node("John is happy eating steak with BBQ sauce.", null, null, "happy.png"),
		new Node("John is sad eating plain steak.", null, null, "sad.png")
	]
);

var goToStore = new Node(
	"John is at the store. What should he buy?",
	["Steak", "Bread"],
	[steak, peanutButter],
	null
);

var eat = new Node(
	"John doesn't have any food. What should he do?",
	["Go to the store", "Starve"],
	[goToStore, starve],
	null
);

var head = new Node(
	"John is hungry. What should John do?",
	["Eat", "Starve"],
	[eat, starve],
	null
);

var beginJohnsStory = function(node) {
	$("#question").text(node.question);

	if (!node.options) {
		$("#option1").hide();
		$("#option2").hide();
	} else {
		$("#option1").text(node.options[0]).off('click').click(function() {
			beginJohnsStory(node.optionNodes[0]);
		});
		$("#option2").text(node.options[1]).off('click').click(function() {
			beginJohnsStory(node.optionNodes[1]);
		});
	}

	if (node.img) {
		$("img").attr('src', node.img);
		$("img").show();
	}
}

$(document).ready(function() {
	$("img").hide();
	beginJohnsStory(head);
});
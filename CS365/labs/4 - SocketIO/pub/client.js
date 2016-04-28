
var socket = io();

socket.on("move", function(data) {
	moveToPostition(data);
});

socket.on("done", function(data) {
	alert("Game over! The winner is the dog on the " + data);
});

function moveToPostition(pos) {
	$("#foreground").css("left", pos+"px");
}

$(document).ready(function() {
	$("#left").click(function() {
		socket.emit("tugLeft", null);
	});

	$("#right").click(function() {
		socket.emit("tugRight", null);
	});
});


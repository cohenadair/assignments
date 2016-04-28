var NUMBER_OF_TEAMS = 4;

var select1 = function() {
	return $("#sel1");
}

var select2 = function() {
	return $("#sel2");
}

var select3 = function() {
	return $("#sel3");
}	

function getCellId(r, c) {
	return r.toString() + c.toString();
}

// creates the inner HTML of the results table
// results is a 2D array of Strings
function updateTable(results) {
	var html = "";

	for (var r = 0; r <= NUMBER_OF_TEAMS; r++) {
		html += "<tr>";
		
		for (var c = 0; c <= NUMBER_OF_TEAMS; c++) {
			html += "<td id='" + getCellId(r, c) + "'>";
			
			if (r == 0 && c == 0)
				html += "";
			else if (r > 0 && c == 0)
				html += "Team " + r;
			else if (r == 0 && c > 0)
				html += c;
			else 
				html += results[r - 1][c - 1];

			html += "</td>";
		}

		html += "</tr>";
	}

	$("table").html(html);
}

function getResults() {
	$.get({
		url: "http://127.0.0.1:8080/getupdate",
		success: function(data) {
			updateTable(data);		
		}
	});
}

function postResults() {
	if (select1().val() == select3().val()) {
		alert("Teams cannot play against themselves!");
		return;
	}

	$.post({
		url: "http://127.0.0.1:8080/postupdate",
		data: { team1: select1().val(), team2: select3().val(), result: select2().val() },
		success: function(data) {
			console.log(data);
			updateTable(data);
		}
	});
}

function initUpdateForm() {
	var html = "";
	for (var i = 0; i < NUMBER_OF_TEAMS; i++)
		html += "<option value='" + i + "'>" + (i + 1) + "</option>";

	select1().html(html);	
	select3().html(html);
}

$(document).ready(function() {
	getResults();
	initUpdateForm();

	$("button").click(function() {
		postResults();
	});
});
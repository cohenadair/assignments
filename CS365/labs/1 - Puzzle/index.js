// HTML ids of each button
var BTN_FILL_3 = "#fill-3";
var BTN_EMPTY_3 = "#empty-3";
var BTN_POUR_3 = "#pour-3";

var BTN_FILL_5 = "#fill-5";
var BTN_EMPTY_5 = "#empty-5";
var BTN_POUR_5 = "#pour-5";

var IMG_CUP_3 = "#three-cup";
var IMG_CUP_5 = "#five-cup";

var DESC_CUP_3 = "#three-cup-description";
var DESC_CUP_5 = "#five-cup-description";

var FINISHED = "#finished";

function Cup(maxValue, imgId, descId) {
	this.descriptionId = descId;
	this.maxValue = maxValue;
	this.imgId = imgId;
	this.value = 0;
	
	this.fill = function() {
		this.setValue(this.maxValue);
	};

	this.empty = function() {
		this.setValue(0);
	};

	this.pour = function(toCup) {
		// this cup
		var oldValue = this.value;
		var newValue = this.value - toCup.getEmptySpace();

		if (newValue <= 0)
			this.empty();
		else
			this.setValue(newValue);

		// the cup being poured into
		newValue = toCup.value + oldValue;

		if (newValue >= toCup.maxValue)
			toCup.fill();
		else
			toCup.setValue(newValue);
	};

	this.getEmptySpace = function() {
		return this.maxValue - this.value;
	};

	this.setValue = function(value) {
		this.value = value;
		$(this.imgId).attr("src", this.value + "OutOf" + this.maxValue + ".jpg");
		$(this.descriptionId).text(this.value + "/" + this.maxValue + " filled");
	};
};

var cup_3 = new Cup(3, IMG_CUP_3, DESC_CUP_3);
var cup_5 = new Cup(5, IMG_CUP_5, DESC_CUP_5);

function checkResult() {
	if (cup_5.value == 4)
		$(FINISHED).show();
	else
		$(FINISHED).hide();
}

function initialize() {
	$(BTN_FILL_3).click(function() {
		cup_3.fill();
		checkResult();
	});

	$(BTN_EMPTY_3).click(function() {
		cup_3.empty();
		checkResult();
	});

	$(BTN_POUR_3).click(function() {
		cup_3.pour(cup_5);
		checkResult();
	});

	$(BTN_FILL_5).click(function() {
		cup_5.fill();
		checkResult();
	});

	$(BTN_EMPTY_5).click(function() {
		cup_5.empty();
		checkResult();
	});

	$(BTN_POUR_5).click(function() {
		cup_5.pour(cup_3);
		checkResult();
	});

	$(FINISHED).hide();
};

$(document).ready(function() {
	initialize();
});





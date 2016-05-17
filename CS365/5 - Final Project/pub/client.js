var socket = io();
var usernameOne;
var usernametwo;
var currentUserName;
var count;

// A variable used for accessing information from other JavaScript files.
var Client = {
    player: null,
    isGameReady: false,
    turn: -1
}

Client.sendMessage = function(data) {
    var msg = $('#message').val()
    if(msg.length > 0) {
        socket.emit("newMessage", {user: currentUserName, message: data});
    }
    $('#message').val("");

};

Client.sendUpdate = function(data) {
    socket.emit("update", data);
};

//@Param1 = message that was just sent from one of clients
// ^ holds username and a message
//updates conversation dialogue box on all clients
socket.on("updateDialogue", function(msg) {
      $('#dialogue').append(msg.user + ": " + msg.message + "\n");
      //Try to be able to send via 'Enter' key
      //disable typing in textarea
      //if input is empty don't send a message

});

Client.hideLogin = function() {
    $("#login").hide();
};

Client.showGame = function() {
    $("#game").show();
};

socket.on("onOpponentConnect", function(data) {
    Client.isGameReady = data.readyToStart;
    Client.turn = data.turn;
    Client.onPlayerConnect();
});

socket.on("update", function(data) {
    Client.onReceiveUpdate(data);
});



// Handles user login and sign up
// Author: Kyle and Cohen
function LoginAndSignUp(){

	var getNode = function(s) {

		return document.querySelector(s);
    };

    var username_input = getNode('#username'),
	    password_input = getNode('#password'),
	    nameError = getNode('#usernameError'),
	passError = getNode('#passwordError'),
        submit = getNode('#submit'),
        sign = getNode('#signup');

    // Login
    $("#submit").click(function() {
        count++;
        console.log("Clicked submit");

    	var user_name = username_input.value,
            user_password = password_input.value;

    	if (user_name == "") {
    		nameError.innerHTML = "Supply a valid username";
    		return false;
    	}

        if (user_password == "") {
            nameError.innerHTML = "Supply a valid password";
            return false;
        }
        currentUserName = user_name;

        // send credientials to the server
        socket.emit("login", {
            username: user_name,
            password: user_password
        }, function(data) {
            if (!data.success) nameError.innerHTML = data.msg;

            else{
           		Client.hideLogin();
                Client.showGame();
                Client.player = data.player;
    	        Client.isGameReady = data.readyToStart;
    	        Client.turn = data.turn;
                Client.onPlayerConnect();

            }
        });

		return true;
    });

    // Signup
    $("#signup").click(function() {
        console.log("Clicked submit");

        var user = {
            username: username_input.value,
            password: password_input.value
        };

        socket.emit("addUser", user, function(result, msg) {
            // show message to user
            nameError.innerHTML = msg;
            // do something with the result
            console.log(result);
        });
    });

    $("#game").hide();
}

$(LoginAndSignUp);

$(document).ready(function() {
  //handle Chat message send
  $('#chatButton').click(function() {
      console.log("click worked");
      var msg = $('#message').val();
      Client.sendMessage(msg);
  });
  //Handle chat message send on 'Enter'
  $('#message').keypress(function(e) {
      if(e.which && e.which == 13) {
        var msg = $('#message').val();
        Client.sendMessage(msg);
      }
  });
});

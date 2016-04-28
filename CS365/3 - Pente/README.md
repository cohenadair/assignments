Pente
=====

Write a 2-player implementation of the game Pente. Essentially, you take turns placing pieces on a 13 by 13 or 19 by 19 board, and try to make 5 in a row to win. If your opponent has a two-in-a-row and you place a piece so that it is now blocked on both sides (e.g. resulting in black, white, white, black in a row/column/diagonal), then you capture those two surrounded pieces. If a player makes 5 captures (10 pieces), that counts as a win. If the pieces are arranged correctly, is possible to make multiple captures in one move. However, you cannot "move into a capture". That is to say, if "black, white, white, black in a row" occurs as a result of white making a move, then no capture is made. 

No database is required for this project. However, make the web interface responsive in the following sense: when one player makes a move, the other player (on some other computer) should immediately see that the move was made on their screen. This should be done with a server push (with socket.io), not by having the client continuously poll the server. 

Only one room needs to be supported; multiple rooms is not a requirement. Users might be put into seats automatically or manually, usernames or anonymously - it is your call on how to implement that.
Notes
=====

Notes used to plan out the application before coding begins.

#### Server
* Events
  * onConnect(socket id)
  * onMove(updated 2D array)
* Data
  * Socket id for each player (max 2)
  * 2D array (grid) of Integer (1 or 2, depending on the player)

#### Client
* Socket Events
  * onMove()
  * onGameOver(winner)
  * onGameFull()
  * onConnect()
* UI Events
  * onClickBoard()

#### Interface
* Title
* Display the current player's name (either "Player 1" or "Player 2")
* Show who's turn it is
* 13x13 <table> element; <td> respond to onClick() events
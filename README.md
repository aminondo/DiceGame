# DiceGame

Well the first thing you need to do is
limit the players ie pick a two or three player game
each player gets five dice so thats 10 or fifteen random numbers you need
to generate.

Your probably going to make use of menus

Menu A
1. To make a bid
2. To see your dice
followed by a call to clear the screen
once your finished viewing your dice
3. Call the other player a liar.


Number 1 is the most problematic your going to have to decide if 1's are wild.. if I were you I would make 1's wild..
makes for a more interesting game.

You need a way of storing bids and a way of checking if new bids are legal

only legal bids like inital bid "I have 2 two's"
followed by next player bidding higher like "I have 2 threes" or "I have 3 two's" 

Your probaly going to ask the bidder something like
How many dice ?
followed by
what Value are you bidding on the dice ?
then a message should be displayed that matches the user input
like

You have bid 2 three's

then check if its legal by comparing value of previous bid
and taking appropriate action.
ie initial bid of 2 two's = value of 4 ie 2 X 2 =4
compare if 2 three's are legal ie 2 X 3 = 6 which is greater than 4 so bid is legal game proceeds to next player who gets 

Menu A

if bid is not legal a warning should be issused
"Illegal BID please bid again."
followed by player entering a bid again.

The calling the player a liar should uncover all the dice

in a ten dice two player game if the player has bid "6 sixes"

two rows of 5 dice should be printed like this
player1
dice1: 1 dice2: 6 dice3: 6 dice4: 4 dice5: 1
player2 
dice1: 6 dice2: 3 dice3: 3 dice4: 6 dice5: 3 

means that that player calling the player a LIAR has failed in his bid

as there are 6 sixes including the wild card 1's

Player 1 in this case should be told he has won followed by a

"Play again ?" message

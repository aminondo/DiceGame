
#include "Helper_Functions.c"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX 5
#define TRUE 0
#define FALSE 1


int main(){
	int endRound = TRUE;
	struct player user;
	struct player computer;
	int playerTurn = 1;
	int lowestRemainingDice;
	int playerChoice;
	int s;
	char input[MAX];
	char playAgain = 'Y';


	//initizalize structs
	resetgame(&user,&computer);
	
	//introduction and rules
	printf("\t\t\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("  "
"\n888      d8b                                8888888b.  d8b      "            
"\n888      Y8P                                888    Y88 Y8P       "           
"\n888                                         888    888            "          
"\n888      888  8888b.  888d888 .d8888b       888    888 888  .d8888b .d88b.  "
"\n888      888      88b 888P    88K           888    888 888 d88P    d8P  Y8b "
"\n888      888 .d888888 888      Y8888b.      888    888 888 888     88888888 "
"\n888      888 888  888 888          X88      888  .d88P 888 Y88b.   Y8b.     "
"\n88888888 888  Y888888 888      88888P'      8888888P   888  Y8888P  Y8888  "
 "\n  ........."
 "\n :~, *   * ~,"
 "\n : ~, *   * ~."
 "\n :  ~........~"
 "\n : *:         :      ~'~,"
 "\n :  :         :    ~' *  ~,"
 "\n ~* :    *    : ,~' *    * ~,"
 "\n  ~,:         :.~,*    *  ,~ :"
 "\n   ~:.........::  ~, *  ,~   :"
 "\n               : *  ~,,~  *  :"
 "\n               :* * * :  *   :"
 "\n                ~, *  : *  ,~"
 "\n                  ~,  :  ,~"
 "\n                    ~,:,~ \n");
	printf("Welcome to Liar's Dice!\n");
	printf("The purpose of the game is to guess how many\n");
	printf("of a certain die are in both cups. In each round\n");
	printf("you can either call or bid. Bidding consists of raising\n");
	printf("your opponenets prior bid by either going up a\n");
	printf("facevalue or increasing the number bidded, or both. Calling occurs\n");
	printf("when you do not believe the opponents bid and you raise your\n");
	printf("cup in order to see if his bid is correct. The round\n");
	printf("ends when someone calls. The loser of the round loses a die.\n");
	printf("The game ends when someone is left with no dice.\n\n\n");

	do{
		lowestRemainingDice = 5;
		resetgame(&user,&computer);
		printf("Enter a positive seed value, in order to randomize dice rolling: ");
		do{
			if (fgets(input, sizeof(input), stdin ))
				if(sscanf(input, "%d", &s) == 1){
						if (s<0) 
							printf("\nInvalid Choice.Try again.\n");
				}
		}while(s<0);
		srand(s);
		
		while(lowestRemainingDice > 0)  //represents each round, ends when a player has no more dice
		{
			rollDice(&user);
			rollDice(&computer);
			while (endRound == TRUE) //continues until a player calls, finishing the round
			{ 
				if (playerTurn%2 != 0){  //user's turn
					printf("\n------------------------------------------");
					printf("\nPlayer 1, your dice are:\n");
					showDice(user);
					if (playerTurn==1){
					printf("\n Press 1 if you want to bid.");
					}else{
					printf("\n Press 1 if you want to bid.");
					printf("\n Press 2 if you want to call. ");
					}

					do {      											//this do/while loop makes sure
						if (fgets(input, sizeof(input), stdin ))
							if(sscanf(input, "%d", &playerChoice) == 1){
							
								if ((playerChoice < 1) || (playerChoice > 2))
									printf(" \n Invalid Choice.Try again.\n");
								}
					} while((playerChoice < 1) || (playerChoice > 2));   

					if (playerChoice == 1){  //user bids
						makeBid(&user, &computer);
						playerTurn++;
					}

					if (playerChoice == 2){ //user calls
						if(userCall(&user, &computer) == EXIT_SUCCESS)
							playerTurn = 2;
						else
							playerTurn = 1;
						endRound = FALSE;
					} 	
				}

				if (playerTurn%2 == 0 && computer.remainingDice != 0){ //computers's turn
					if(computerBid(&computer, &user) == EXIT_SUCCESS)
						playerTurn++;
					else if (computerCall(&computer,&user) == EXIT_SUCCESS){
							playerTurn = 1;
							endRound = FALSE;
						} else{
							playerTurn = 2;
							endRound = FALSE;
						}
						
				}	
			}

			//calculates lowest remaining Dice
			if (user.remainingDice > computer.remainingDice)
				lowestRemainingDice = computer.remainingDice;
			else
				lowestRemainingDice = user.remainingDice;
			endRound = TRUE;
		}

		//determines winner
		if (user.remainingDice == 0)
			printf("\nGame is over. Computer won. \n");
		else
			printf("\nGame is over. You won! \n");


		//exit game or restart game
		printf("\nWould you like to play again? (Y/N)\n");
		do{
			if (fgets(input, sizeof(input), stdin ))
				if(sscanf(input, "%c", &playAgain) == 1){
					printf("\n %c \n", playAgain);
						if (!(playAgain == 'Y' || playAgain == 'N')) 
									printf("Invalid Choice.Try again.\n");
				}
		}while(!(playAgain == 'Y' || playAgain == 'N'));

		if (playAgain == 'N')
			printf("Exiting....\n\n\n");

	} while( playAgain == 'Y');
	return EXIT_SUCCESS;
}

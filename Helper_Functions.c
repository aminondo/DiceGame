#include "Helper_Functions.h"
#define MAX 5
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/**************************************************
structure of each player
contains the remaining dice each player has, the value for
each of his dice in each round, his bid and a value that 
serves to control the array when a player loses a die.
***************************************************/
struct player {
	int remainingDice;
	int quantityBid;
	int  facevalueBid;
	int dice[MAX];
	int diceToRemove;
};

/***************************************************
function name: computerCall(struct player computer, struct player user)
purpose: controls program when computer calls, dice are shown, the bid is checked
and the loser loses a dice
input: struct of both players, since the computer needs both to check the bid, and 
determine loser
output: returns exit_success if computer is right and exit_failure if computer is
wrong
*********************************************************/
int computerCall(struct player *computer, struct player *user){
	int computerWin;
	printf("\n------------------------------------------");
	printf("\nComputer Calls!!!!!!!!!!!!!!!! \n");
	printf("User's Dice: \n");
	showDice(*user);
	printf("\n Computer's Dice: \n");
	showDice(*computer);
	
	if(checkBid(*computer, *user) == EXIT_SUCCESS){
		printf("Computer loses a dice.\n");
		removeDice(computer);
		computerWin = EXIT_FAILURE;
	} else {
		printf("User loses a dice.\n");
		removeDice(user);
		computerWin = EXIT_SUCCESS;
	}
	

	//reset values bid by both computer and user
	computer->facevalueBid = 0;
	computer->quantityBid = 0;
	user->facevalueBid = 0;		
	user->quantityBid = 0;
	
	return computerWin;	
}


/***********************************************************
function name: userCall(struct player user, struct player computer)
purpose: controls program when user calls, dice are shown, the bid is checked
and the loser loses a dice
input: struct of both players, since the program needs both to check the bid, and 
determine loser
output: returns exit_failure if user was wrong and ext_success if user was right
***********************************************************/
int userCall(struct player *user, struct player *computer){
	int userWins;
	printf("\n------------------------------------------");
	printf("\nPLayer 1 calls.\n");
	printf("User's Dice: \n");
	showDice(*user);
	printf("\n Computer's Dice: \n");
	showDice(*computer);
	
	if(checkBid(*user, *computer) == EXIT_SUCCESS){
		printf("User loses a dice.\n");
		removeDice(user);
		userWins = EXIT_FAILURE;
	} else {
		printf("Computer loses a dice.\n");
		removeDice(computer);
		userWins = EXIT_SUCCESS;
	}
	

					
	//reset values bid by both computer and user
	computer->facevalueBid = 0;
	computer->quantityBid = 0;
	user->facevalueBid = 0;
	user->quantityBid = 0;
	
	return userWins;
}


/************************************************************
function name:int rollDice(struct player person)
purpose: roll the dice in the player's struct, so long as
the current value in the array isn't -1, since -1 represents a
lost dice
input: struct player person, represents the struct of the player whom
the dice are going to be rolled. called for both user and computer
output: void, since changes struct directly
************************************************************/
void rollDice(struct player *person){
	int k;
	for (k=0;k<person->remainingDice;k++){
			person->dice[k]=rand() % 5 + 1;
	}
}



/*************************************************************
function name:removeDice(struct player person)
purpose: remove dice from player, sets last position in dice array
to -1 and decreases the dicetoRemove variable by one.
input: struct player person, represents the player who will lose a die
output: void, changes array directly
************************************************************/
void removeDice(struct player *person){

	person->remainingDice=person->remainingDice-1;
	person->dice[person->diceToRemove]=-1;
	person->diceToRemove=person->diceToRemove-1;
}


/************************************************************
function name: makeBid(struct player user, struct player computer)
purpose: function to make sure user makes a correct bid. It error checks
every time it asks user for input, and then checks that the bid is higher
than the previous bid.
input:struct player user, struct player computer, function needs structs of 
both players in order to chech the bid, and in order to save the player's bid
inside the struct
output:


**************************************************************/
void makeBid(struct player *user, struct player *computer){
	char char_value[MAX];  //
	char char_bid[MAX];
	int facevalue;
	int bid;

	do{
		printf("Enter Facevalue:\n");
		do{											//this do/while loop makes sure the user
			if (fgets(char_value, sizeof(char_value), stdin ))
				if(sscanf(char_value, "%d", &facevalue) == 1){
					if ( (facevalue<1) || (facevalue > 6) )
						printf("Invalid Facevalue.Try again.\n");
			}
		} while ( facevalue<1 || facevalue > 6 );
		user->facevalueBid = facevalue; //sets value in user struct

		printf("Enter bid: \n");
		do{											//this do/while loop makes sure the user
		if (fgets(char_bid, sizeof(char_bid), stdin ))
				if(sscanf(char_bid, "%d", &bid) == 1){
					if ( bid<1 || bid > 10 )
						printf("Invalid Bid.Try again.\n");
				}
		} while ( bid < 1 || bid > 10);
		user->quantityBid = bid; //sets value in user struct
	} while (isBidCorrect(*user, *computer) == EXIT_FAILURE);

	if (user->quantityBid == 1)
		printf("User bids %d %d \n\n", user->quantityBid, user->facevalueBid);
	else
		printf("User bids %d %d's \n\n", user->quantityBid, user->facevalueBid);
		
}
 

/*************************************************************
function name:isBidCorrect(struct player user, struct player computer)
purpose; checks to see whether the users bid is higher than the computer's bid
the function is called by the function makeBid()
input: struct player user, struct player computer, both player's structures 
are needed in order to compare their bids
output: EXIT_SUCCESS if bid is higher and EXIT_FAILURE if bid is lower
**************************************************************/
int isBidCorrect(struct player user, struct player computer){
	if (user.quantityBid > computer.quantityBid )
		return EXIT_SUCCESS;
	else if (user.quantityBid == computer.quantityBid && user.facevalueBid > computer.facevalueBid)
			return EXIT_SUCCESS;
		else{
			printf("Your Bid is lower than the computer's bid. Please Try again.\n");
			if (computer.quantityBid == 1)
				printf("The computer bid %d %d\n", computer.quantityBid, computer.facevalueBid);
			else
				printf("The computer bid %d %d's\n", computer.quantityBid, computer.facevalueBid);
			return EXIT_FAILURE;
		}
}
		

/****************************************************************
function name: showdice(struct player person)
purpose: prints out the dice from a player, will only print the dice that
are still eligible in the game
input: struct player person, takes as input the struct of the player you want
to print the dice
output: void, changes the struct directly
*****************************************************************/
void showDice(struct player person){

	int k=0;
	for (k=0;k<(person.remainingDice);k++){
		if (person.dice[k] != -1)
			printf("%i\t", person.dice[k]);
	}
	printf("\n\n");
}



/***************************************************************** 
function name: resetgame(struct player user, struct player comp)
purpose: reinitializes each players structs in order to be able to play again
input: struct player user, struct player computer, takes both players structs,
in order to reinitialize both
output: void
******************************************************************/

void resetgame(struct player *user, struct player *computer){

	user->remainingDice=5;
	user->diceToRemove=4;
	user->facevalueBid = 0;
	user->quantityBid = 0;
	computer->remainingDice=5;
	computer->diceToRemove=4;
	computer->facevalueBid = 0;
	computer->quantityBid = 0;
} 





/************************************************************

*************************************************************/

double bidProbability(struct player computer, int bid, int face, struct player user){

	double q;
	double countrepeatedFV = 0; 
	double exactprobability = 0;
	double probability = 0;
	int k;
	int x;
	double single = .1666667; // represents 1/6
	double five = .8333333;  //represents 5/6
	int dice_unknown = user.remainingDice;
	for (k=0;k<computer.remainingDice;k++){
		if (computer.dice[k]== face)
			countrepeatedFV++;
	}

//q is the quantity of any face value bidded by the user minus the quantity 
//of this face value held by the computer
	q=bid-countrepeatedFV;



//This for loop will calculate the exact probabilies and add them up to estimate the actual probability
	for (x=q;x<=dice_unknown;x++){
		double denominator = factorial(q+x-1)*factorial(dice_unknown-q+x-1);
		double numerator = factorial(dice_unknown);
		double one_sixth = pow(single, (q+x-1));  // 1/6 to the power of q+x-1
		double five_sixth = pow(five, (dice_unknown-q-x+1)); // 5/6 to the power of n-q-x+1
		exactprobability = numerator / denominator * one_sixth * five_sixth;
		probability=probability+exactprobability;
	}

	return probability*100;

}


/******************************************************
function name: factorial(int n)
purpose: calculates the factorial of n
input: int n, the number we want to calculate the factorial of
output: result, the factorial of n
*******************************************************/

double factorial(int n){
	int c;
	double result=1;

	for (c=1;c<=n;c++){
		result=result*c;
	}

	return result;
}


/**************************************************
function name: checkBid(struct player caller, struct player bidder)
purpose: checks bid at the end of each round, to see whether the caller
was correct or incorrect
input: struct player caller, struct player bidder, takes as input, the struct
of both players in order to have access to their dice
output: returns EXIT_SUCCESS if bid is correct and EXIT_FAILURE if bid is incorrect

****************************************************/

int checkBid(struct player caller, struct player bidder){
	int count = 0;
	int bidTotal = bidder.quantityBid;
	int faceValue = bidder.facevalueBid;
	int dice_per_cup = 5;
	int k;
	//count Total dice with faceValue
	for (k=0;k<dice_per_cup;k++){
		if(caller.dice[k] == faceValue)  //counts the dice in the caller's cup
			count++;
		if (bidder.dice[k] == faceValue) // counts the dice in the bidder's cup
			count++;
	}
	
	if (count >= bidTotal){
		printf("The bid is correct. \n");
		return EXIT_SUCCESS;
	} else{
		printf("The bid is incorrect. \n");
		return EXIT_FAILURE;
	}
	
}


/*********************************************************

*********************************************************/
int computerBid(struct player *computer, struct player *user){
	int i;
	int j;
	int maxBid = user->remainingDice+computer->remainingDice;
	int maxFaceValue = 6;
	int quantityBid;
	int facevalueBid;
	double highestProb = 0;
	int minBid = user->quantityBid;
	int minValue = user->facevalueBid;
	
	if(user->facevalueBid == 6){
		minValue = 1;
		minBid++;
	} else
		minValue++;
		
	if(minBid == 0) //if computer starts
		minBid++;
		
	for(i=minBid;i<=maxBid;i++){
		for(j=minValue;j<=maxFaceValue;j++){
			if(bidProbability(*computer,i,j, *user)>highestProb){
				quantityBid = i;
				facevalueBid = j;
				highestProb = bidProbability(*computer,i,j, *user);
			}
			if((bidProbability(*computer,i,j, *user) == highestProb) && (j > facevalueBid) && (quantityBid == i))
				facevalueBid = j;
		}
		minValue=1;

	}
	
	if (highestProb>15){
		if (quantityBid == 1)
			printf("Computer bids %d %d \n", quantityBid, facevalueBid);
		else
			printf("Computer bids %d %d's \n",quantityBid,facevalueBid);
		computer->facevalueBid = facevalueBid;
		computer->quantityBid = quantityBid;
		return EXIT_SUCCESS;
	} else
		return EXIT_FAILURE;
		
	
	
}









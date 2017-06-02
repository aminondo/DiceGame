#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_


//Helper_Function.h header file


/*************************************
This is the include file for al helper functions used by the program Liar's Dice,
***************************************/


struct player;  

void rollDice(struct player *person); 

void removeDice(struct player *person);

double bidProbability(struct player computer, int bid, int face, struct player user); //calculate the probability of a bid

int isBidCorrect(struct player user, struct player computer);  

int computerBid(struct player *computer, struct player *user);  //algorythm for computer to make a bid

int computerCall(struct player *computer, struct player *user);  

int userCall(struct player *user, struct player *computer);

void showDice(struct player person); 

void  makeBid(struct player *user, struct player *computer);

void resetgame(struct player *user, struct player *computer);

int checkBid(struct player caller, struct player bidder); //checks whether a bid is true or not

double factorial(int n);  


#endif //_DICE_HELPER_LIB_H_

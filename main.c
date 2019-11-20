#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10 
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30


//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;							
 
//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users

//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag

//some utility functions

//get an integer input from standard input (keyboard)
//return : input integer value
//         (-1 is returned if keyboard input was not integer)
int getIntegerInput(void) {
    int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}


//card processing functions ---------------

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum, int i){
	
	int input;
	//if cardnum(0~12) 10,11,12 is '10', other get cardnum+1
	if(cardnum/13==0){			
		if(cardnum>=10)
		input=10;
		else
		input=cardnum+1;
		}
	//if cardnum(13~25) -> 23,24,25 is '10', other get cardnum+1
	else if(cardnum/13==1){
		if(cardnum>=23)
		input=10;
		else
		input=cardnum%12;
	}
	//if cardnum(26~38) -> 36,37,38 is '10', other get cardnum+1
	else if(cardnum/13==2){
		if(cardnum>=36)
		input=10;
		else
		input=cardnum%25;
	}
	//if cardnum(39~51) -> 49,50,51 is '10', other get cardnum+1
	else if(cardnum/13==3){
		if(cardnum>=49)
		input=10;
		else
		input=cardnum%38;
	}
	//when get card 'A' if cardSum>10 input is 1, but if cardSum<10 input is 11
	if(input==1){ 
		if(cardSum[i]>10)
		input=1;
	else
		input=11;
	}
	

	return input;
}



int main(int argc, char *argv[]) {
	//initialize roundIndex, action, count
	//declare argument
	int roundIndex = 1;
	int max_user;
	int i,j;
	int count=2;
	int action=0;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	max_user=configUser();

	//Game initialization --------
	//1. players' dollar
	for(i=0;i<max_user;i++){
		dollar[i] = N_DOLLAR;
	}
	//2. card tray
	mixCardTray();



	//Game start --------
	do {
		
		printf("\n-------------------------------------\n");
		printf("--------ROUND %d ( cardIndex : %d)---------",roundIndex, cardIndex);
		printf("\n-------------------------------------\n");
		
		betDollar(); //beting dollars out of last money
		offerCards(); //1. give cards to all the players
		
		printf("\n----------CARD OFFERING----------\n");
		printCardInitialStatus();// print initial status of card(each players')
		printf("\n------------------ GAME start --------------------------\n");		
		//each player's turn
		
	
	return 0;

}



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

//print the card information (e.g. DiaA)
//set A,J,Q,K on each card(Hart,Club,Spade,Dia) and then set number of remaining cards(cardnum+1)
void printCard(int cardnum) {	
		switch(cardnum){
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7: 
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:  
			if (cardnum==0)
				printf("Hart A ");
			else if (cardnum==10)
				printf("Hart J ");
			else if (cardnum==11)
				printf("Hart Q ");
			else if (cardnum==12)
				printf("Hart K ");
			else
				printf("Hart %d ", cardnum+1);
				
			break;
			
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
			case 22:
			case 23:
			case 24:
			case 25:
		
			if (cardnum==13)
				printf("Club A ");
			else if (cardnum==23)
				printf("Club J ");
			else if (cardnum==24)
				printf("Club Q ");
			else if (cardnum==25)
				printf("Club K ");				
			else
				printf("Club %d ", (cardnum%12));
		
			break;
					
			case 26:
			case 27:
			case 28:
			case 29:
			case 30:
			case 31:
			case 32:
			case 33:
			case 34:
			case 35:
			case 36:
			case 37:	
			case 38:
		
			if (cardnum==26)
				printf("Spade A ");
			else if (cardnum==36)
				printf("Spade J ");
			else if (cardnum==37)
				printf("Spade Q ");
			else if (cardnum==38)
				printf("Spade K ");
			else
				printf("Spade %d ", (cardnum%25));
			
			break;
			
		
			case 39:
			case 40:
			case 41:
			case 42:
			case 43:
			case 44:
			case 45:
			case 46:
			case 47:
			case 48:
			case 49:
			case 50:
			case 51:	
			
			if (cardnum==39)
				printf("Dia A ");
			else if (cardnum==49)
				printf("Dia J ");
			else if (cardnum==50)
				printf("Dia Q ");
			else if (cardnum==51)
				printf("Dia K ");
			else
				printf("Dia %d ", (cardnum%38));
			
			break;
		}
		
}


//card array controllers -------------------------------
void mixCardTray(void) {
	
	int i, j;
	int temp;
	
	for(i=0; i<N_CARDSET*N_CARD; i++){
		
		CardTray[i]=i;
		cardSum[i]=0;
		
	}
	
	for(j=0; j<N_CARDSET*N_CARD; j++){
		
		int k = rand()%(N_CARDSET*N_CARD);
		temp = CardTray[j]; 
		CardTray[j] = CardTray[k];
		CardTray[k] = temp;
	}
}

//get one card from the tray
int pullCard(void) {
	int p_card;

	p_card=CardTray[cardIndex];
	
	cardIndex++;
	
	return p_card;
}


//playing game functions -----------------------------

//player settiing
int configUser(void) {
	do{
		printf("input the number of player(MAX:5)");
		n_user=getIntegerInput(); 
	}while(n_user>N_MAX_USER);
	//when n_user is bigger than 5, action again
	return n_user;
}


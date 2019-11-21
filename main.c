#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card_processing.c"
#include "card_array_controllers.c"
#include "playing_game.c"

#define N_CARDSET         1
#define N_CARD            52
#define N_DOLLAR         50


#define N_MAX_CARDNUM      13
#define N_MAX_USER         5
#define N_MAX_CARDHOLD      10 
#define N_MAX_GO         17
#define N_MAX_BET         5

#define N_MIN_ENDCARD      30


//card tray object
extern int CardTray[N_CARDSET*N_CARD];
extern int cardIndex;                     
 
//player info
extern int dollar[N_MAX_USER];                  //dollars that each player has
extern int n_user;                           //number of users

//play yard information
extern int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];   //cards that currently the players hold
extern int cardSum[N_MAX_USER];               //sum of the cards
extern int bet[N_MAX_USER];                  //current betting 
int gameEnd = 0;                      //game end flag
//some utility functions
//calculate the actual card number in the blackjack game
extern int getCardNum();
//print the card information (e.g. DiaA)
//set A,J,Q,K on each card(Hart,Club,Spade,Dia) and then set number of remaining cards(cardnum+1)
extern void printCard();
extern void mixCardTray();
//get one card from the tray
extern int pullCard();
//player settiing
extern int configUser();
//betting
extern void betDollar();
//offering initial 2 cards
extern void offerCards();
//print initial card status
extern void printCardInitialStatus();
extern int getAction();
//When pull new card, print player's card status
extern void printUserCardStatus();
// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
extern void calcStepResult();
//print a round's result
extern void checkResult();
//print final winner according to capital remaining
//By compare all of players' capital
extern void checkWinner();

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



int main(int argc, char *argv[]) {
   //initialize roundIndex, action, count
   //declare argument
   int roundIndex = 1;
   int max_user;
   int i,j;
   int count=2;
   int action=0;
   int hands_up;
   
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
      printf("--------ROUND %d ( cardIndex : %d )---------",roundIndex, cardIndex);
      printf("\n-------------------------------------\n");
      
      betDollar(); //beting dollars out of last money
      offerCards(); //1. give cards to all the players
      
      printf("\n----------CARD OFFERING----------\n");
      printCardInitialStatus();// print initial status of card(each players')
      printf("\n------------------ GAME start --------------------------\n");      
      //each player's turn
      for (i=0;i<=n_user;i++) //each player
      {   
         //initialize cardSum for next round
         cardSum[i]=0;
      
         //initialize count=2 
		 //initialize action=0        
         count=2;
         action = 0;
         
         //start my turn
         if(i==0){
            printf("->my turn!----------\n");
            //print first 2 cards at my turn
            printUserCardStatus(i, count);
            //if card is 'A' hands up 1
			for(j=0;j<count;j++){
                 cardSum[i]+=getCardNum(cardhold[i][j],i);
                 if((getCardNum(cardhold[i][j],i))==1)
                  	hands_up=1;
                 }
            //if card is 'A' and cardsum is 11, it is blackjack!
			if(hands_up==1&&cardSum[i]==11){
               	cardSum[i]=-1;
               	//judge dead or not
				calcStepResult(i,count);
                //if blackjack, finish myturn by set action=1
				action =1;
			}
            //if not blackjack at fist time, start this function
			while(action==0){
		   		//ask action or not and get enter
               	printf("\n   :::Action?(0-go, other integer-stop)");
                action = getIntegerInput();
				//if I choose stop, print STAY and go out this loop 
				if(action!=0){
                    printf("	:::STAY!\n");
					break;
                	}
				//if I select 'GO' hold a card
				cardhold[0][count] = pullCard();
				//initialize carsum is 0
				cardSum[0]=0;
				//set hands_up = 0
                hands_up=0;
            	//if card is 'A', hands up 1
                for(j=0;j<=count;j++){
						cardSum[i]+=getCardNum(cardhold[i][j], i);
						if(getCardNum(cardhold[i][j], i)==1)
							hands_up=1;
					}
				//if card is 'A' and cardsum is smaller than 11 plus 10 at cardSum
				if(hands_up==1&&cardSum[i]<=11){
					cardSum[i]+=10;
					}
                //plus count when I pull card
				count++;
                printUserCardStatus(i, count);
				calcStepResult(i, count);
            	//if cardSum is bigger than 21, break this loop and print minus dollar and remain capital
                if(cardSum[i]>21){
                  	dollar[i]-=bet[i];
                   	printf("-->-$%d ($%d)",bet[i],dollar[i]);
                    break;
					}
				if(cardSum[i]==21)
					break;                                
                }
                

               }
         //start players' turn   
         else if(i<n_user){
            //initialize action = 0 and count = 2
            action=0;
            count=2;
            //start first process 
            printf("\n\n->player %d turn!----------\n",i);
            printUserCardStatus(i, count);
            //if card is 'A' hands up 1
            for(j=0;j<count;j++){
                  cardSum[i]+=getCardNum(cardhold[i][j],i);
                  if((getCardNum(cardhold[i][j],i))==1)
                  	hands_up=1;
                  }
                //if card is 'A' and cardsum is 11, it is blackjack! 
                if(hands_up==1&&cardSum[i]==11){
                	cardSum[i]=0;
                	calcStepResult(i,count);
                	action=1;
				}
			//if not blackjack at fist time, start this function
            while(action==0){   
           			//judge player's action
					action=getAction(i,count);                   
					//if player's state is STAY, go out this loop 
                    if (action !=0)
                    	break;
					//when player's state is 'GO' pull a card
					cardhold[i][count]=pullCard();
                    //initialize carsum is 0
					cardSum[i]=0;
                    //set hands_up = 0
					hands_up=0;
                    //if card is 'A', hands up 1
					for(j=0;j<=count;j++){
						cardSum[i]+=getCardNum(cardhold[i][j], i);
						if(getCardNum(cardhold[i][j], i)==1)
						hands_up=1;
					}
					//if card is 'A' and cardsum is smaller than 11 plus 10 at cardSum
					if(hands_up==1&&cardSum[i]<=11){
					cardSum[i]+=10;
					}
                    //plus count when I pull card
					count++;
                    //print card status
                    printUserCardStatus(i, count);
                    calcStepResult(i,count);
                	//if cardSum is bigger than 21, break this loop and print minus dollar and remain capital
				   if(cardSum[i]>21){
                     	dollar[i]-=bet[i];
                     	printf("-->-$%d ($%d)",bet[i],dollar[i]);
                     	break;
					 	}
               }
                     //When player's state is 'STAY' 
            }
         
         //start dealer's turn
         else if(i=n_user){
            //initialize action = 0 and count = 2
            action=0;
            count=2;
            //start first process 
            printf("\n\n->server turn!----------\n");         
            printUserCardStatus(i, count);
        	//if card is 'A' hands up 1
           for(j=0;j<count;j++){
                cardSum[i]+=getCardNum(cardhold[i][j],i);
                if((getCardNum(cardhold[i][j],i))==1)
                  	hands_up=1;
                  }
                //if card is 'A' and cardsum is 11, it is blackjack! 
                if(hands_up==1&&cardSum[i]==11){
                	cardSum[i]=-1;
                	calcStepResult(i,count);
                	action=1;
				}
            //if not blackjack at fist time, start this function
            while(action==0){
                    //judge dealer's action
					action=getAction(i,count);
					//if dealer's state is STAY, go out this loop 
                    if (action !=0)
                    	break;
					//when dealer's state is 'GO' pull a card
					cardhold[i][count]=pullCard();
                    //initialize carsum is 0
					cardSum[i]=0;
					//set hands_up = 0
                    hands_up=0;
                    //if card is 'A', hands up 1
                    for(j=0;j<=count;j++){
						cardSum[i]+=getCardNum(cardhold[i][j], i);
						if(getCardNum(cardhold[i][j], i)==1)
						hands_up=1;
					}
					//if card is 'A' and cardsum is smaller than 11 plus 10 at cardSum
					if(hands_up==1&&cardSum[i]<=11){
					cardSum[i]+=10;
					}
					//plus count when I pull card
                    count++;
                    //print next status
                    printUserCardStatus(i, count);
                    calcStepResult(i,count);
                    //if sum of cards is 21 or bigger than 21, break this loop
                    if(cardSum[i]>21)
                    break;
                    }
            //print dealer's result
            if(cardSum[i]<21){
               printf("\n[[[[[[ server result is ...%d ]]]]]]\n",cardSum[i]);
            }
            else if(cardSum[i]>21){
               printf("\n[[[[[[ server result is ... overflow!! ]]]]]]\n");
            }
         }
      
      }
      
      printf("\n--------------------------------ROUND%d result------------------------------\n", roundIndex);
      checkResult(count);
      //when any player's capital is 0, game is end
      for(i=0;i<n_user;i++){
        if(dollar[i]==0)
       	gameEnd = 1;
      //when cardIndex is over, game is end   
        else if(cardIndex>=48)
        gameEnd = 1;
      }
    //when finish one round, plus roundIndex
    roundIndex++;
   } while (gameEnd == 0);
   //check final winner
   checkWinner();
   
   
   return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CARDSET         1
#define N_CARD            52
#define N_DOLLAR         50


#define N_MAX_CARDNUM      13
#define N_MAX_USER         5
#define N_MAX_CARDHOLD      10 
#define N_MAX_GO         17
#define N_MAX_BET         5

#define N_MIN_ENDCARD      30

//player info
int dollar[N_MAX_USER];                  //dollars that each player has
int n_user;                           //number of users
//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];   //cards that currently the players hold
extern int cardSum[N_MAX_USER];               //sum of the cards
int bet[N_MAX_USER];                  //current betting 

//playing game functions -----------------------------

//player settiing
int configUser(void) {
  	//action this function until n_user is more than N_MAX_USER
  	do{
      printf("input the number of player(MAX:5)");
      n_user=getIntegerInput();
   	  //when n_user is bigger than 5, action again
	  if(n_user>N_MAX_USER){
      	printf("TOO MANY!\n");
	 	}
	  //when n_user is not collect, action again
	  else if(n_user==-1){
	  	printf("AGAIN!\n");
	  	printf("input the number of player(MAX:5)");
	  	n_user=getIntegerInput();
	  	}
   }while(n_user>N_MAX_USER);

   return n_user;
}

//betting
void betDollar(void) {
   //assignment of for sentence
   int i;
   
   printf("\n----------BETTING STEP----------\n");
   printf("->Your betting(total:%d) ",dollar[0]);
   //get bet from me by getIntegerInput() function 
   bet[i]=getIntegerInput();
   //In the case of plaeyrs assign betting dollar randomly(1~5)
   for(i=1;i<n_user;i++){
      bet[i]=1+rand()%5;
      printf("->player%d bets %d(out of $%d)\n",i,bet[i],dollar[i]);
   }
   
}


//offering initial 2 cards
void offerCards(void){
    //assignment of for sentence
   int i;
   //1. give two card for each players(initial 2)
   for (i=0;i<n_user;i++)
   {
      cardhold[i][0] = pullCard();
      cardhold[i][1] = pullCard();
   }
   //2. give two card for the operator (initial 2)
   cardhold[n_user][0] = pullCard();
   cardhold[n_user][1] = pullCard();
   
   return;
}

//print initial card status
void printCardInitialStatus(void) {

   int i;
   
   for(i=0;i<=n_user;i++){
   //after offerCards, print initial card status of me
      if(i==0){
      	printf("Your card: ");
      	printCard(cardhold[i][0]);
      	printCard(cardhold[i][1]);
      	}
      
   //dealer do not open his first card, so print 'x'
      else if(i==n_user){
     	printf("\ndealer's card: %c ",'X');
      	printCard(cardhold[n_user][1]);
     	}
      
   //after offerCards, print initial card status of players
      else if(i<n_user){
      	printf("\nplayer %d card: ",i);
      	printCard(cardhold[i][0]);
      	printCard(cardhold[i][1]);
      	}
      
      
   }

   return;
}


int getAction(int i,int count) {
   int action;
   //when player's cardSum is smaller than 17, print GO! And enter 0 into action
   if(cardSum[i]<17){
      printf("   :::GO!\n");
      action=0;
   	}
  //when player's cardSum is blackjack, not print
   else if(cardSum[i]==21&&count==2)
   	printf("");
    //when player's cardSum is 17 or bigger than 17, print STAY! And enter 1 into action
   else if(cardSum[i]>=17){
      printf("   :::STAY!");
      action=1;
   }

   return action;   
    }
   


//When pull new card, print player's card status
void printUserCardStatus(int user, int cardcnt) {
   int i;
	
  	printf("   -> card : ");
   	for (i=0;i<cardcnt;i++)
      printCard(cardhold[user][i]);
  	printf("\t ::: ");
}




// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
void calcStepResult(int user, int cnt) {   
   //when cardsum is 21 and pull count is 2, it prints Black Jack
   if(cardSum[user]==-1){
      printf("   :::Black Jack!congratulation, you win!!");
   }
   //when cardsum is bigger than 21, it prints 'DEAD' and sum of card numbers
   //print remaining capital and subtract value from last capital
   else if(cardSum[user]>21){
      printf("   :::DEAD(sum: %d)", cardSum[user]);
   }   


   }
   
//print a round's result
void checkResult(int count){
   int i;
   //print result(lose, blackjack, win) and perform the batting results
   for(i=0;i<n_user;i++){
      if(i==0){
         printf("\n   ->your result: ");
            //when blackjack win
			if(cardSum[i]==-1){
            	dollar[i]+=(2*bet[i]);
            	printf("Black Jack! win ($%d)",dollar[i]);
            }
            //if cardsum is more than dealer and cardsum is smaller than 21 -> win
			else if((cardSum[i]>=cardSum[n_user])&&(cardSum[i]<=21)){
            	dollar[i]+=bet[i];
            	printf("win(sum:%d) --> $%d\n", cardSum[0],dollar[i]);
               }
            //if dealer's cardsum is more than 21 and my cardsum is 21 or smaller than 21
			else if((cardSum[n_user]>21)&&(cardSum[i]<=21)){
            	dollar[i]+=bet[i];
            	printf("win(sum:%d) --> $%d\n", cardSum[0],dollar[i]);
			}
            //if my cardsum is smaller than dealer's cardsum
			else if(cardSum[i]<cardSum[n_user]){
             	dollar[i]-=bet[i];
            	printf("lose! (sum:%d) --> $%d",cardSum[0],dollar[i]);
            }
            //if my cardsum is overflow
			else if(cardSum[i]>21){
            	printf("lose due to overflow ($%d)",dollar[i]);
            }
            //if dealer's carsum is blackjack but my carsum is not blackjack
			else if(cardSum[n_user]==0&&cardSum[i]!=0){
            	dollar[i]-=bet[i];
                printf("lose! (sum:%d) --> $%d",cardSum[i],dollar[i]);
			}
            
         }
      else{
         printf("\n   ->%d'th player's result: ",i);
            //when blackjack win
			if(cardSum[i]==-1){
			 	dollar[i]+=(2*bet[i]);
               	printf("Black Jack! win ($%d)",dollar[i]);
            }
            //if dealer's cardsum is more than 21 and my cardsum is 21 or smaller than 21
			else if((cardSum[n_user]>21)&&(cardSum[i]<=21)){
            	dollar[i]+=bet[i];
            	printf("win(sum:%d) --> $%d\n", cardSum[i],dollar[i]);
			}
            //if cardsum is more than dealer and cardsum is smaller than 21 -> win
			else if((cardSum[i]>=cardSum[n_user])&&(cardSum[i]<=21)){
            	dollar[i]+=bet[i];
            	printf("win(sum:%d) --> $%d", cardSum[i],dollar[i]);
            }
            //if my cardsum is smaller than dealer's cardsum
			else if(cardSum[i]<cardSum[n_user]){
            	dollar[i]-=bet[i];
            	printf("lose! (sum:%d) --> $%d",cardSum[i],dollar[i]);
            }
            //if my cardsum is overflow
			else if(cardSum[i]>21){
            	printf("lose due to overflow ($%d)",dollar[i]);
            }
            //if dealer's carsum is blackjack but my carsum is not blackjack
            else if(cardSum[n_user]==0&&cardSum[i]!=0){
            	dollar[i]-=bet[i];
                printf("lose! (sum:%d) --> $%d",cardSum[i],dollar[i]);
			}
         
            
      }

   }
}
//print final winner according to capital remaining
//By compare all of players' capital
void checkWinner(void) {
   //int dollar[n_user];
   int max, i;
   int winner;
   
   max=dollar[0];
   winner = 0;
   for(i=0;i<n_user;i++)
   {
      if(dollar[i]>max)
      {
         max=dollar[i];
         winner=i;
      }
   }
   //if winner is me   
   if(winner==0)
      printf("\n\n      OH YEAH!!!!HAHAHA Final winner is you");
   //if winner is other player
   else
      printf("\n\n      Final winner is %d", winner);   
      
      
}

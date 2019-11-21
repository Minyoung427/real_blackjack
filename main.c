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


//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;                     
 
//player info
int dollar[N_MAX_USER];                  //dollars that each player has
int n_user;                           //number of users

//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];   //cards that currently the players hold
int cardSum[N_MAX_USER];               //sum of the cards
int bet[N_MAX_USER];                  //current betting 
int gameEnd = 0;                      //game end flag

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
   //declare assignment for 'for scentence'
   int i, j;
   int temp;
   //put card in the cardtray
   for(i=0; i<N_CARDSET*N_CARD; i++){
      
      CardTray[i]=i;
      cardSum[i]=0;
      
   }
   //mix cardtray by swap function
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
   //when card be pulled, plus 1 at cardIndex's number
   cardIndex++;
   
   return p_card;
}


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
   if(cardSum[user]==21&&cnt==2){
      printf("   :::Black Jack!congratulation, you win!!");
      //set the cardSum=0 when blackjack
	  cardSum[user] = 0;
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
			if((cardSum[i]==21)&&(count==2)){
            	cardSum[i]=0;
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
			if((cardSum[i]==21)&&(count==2)){
            	cardSum[i]=0;
			 	dollar[i]+=(2*bet[i]);
               	printf("Black Jack! win ($%d)",dollar[i]);
            }
            //if dealer's cardsum is more than 21 and my cardsum is 21 or smaller than 21
			else if((cardSum[n_user]>21)&&(cardSum[i]<=21)){
            	dollar[i]+=bet[i];
            	printf("win(sum:%d) --> $%d\n", cardSum[0],dollar[i]);
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
               	cardSum[i]=0;
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
                	cardSum[i]=0;
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

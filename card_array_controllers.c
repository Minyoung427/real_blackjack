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
int cardIndex = 0; 
int CardTray[N_CARDSET*N_CARD];
int cardSum[N_MAX_USER];               //sum of the cards


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



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define deckSize 104
int playerScore;
int dealerScore;
int playerCard;
int dealerCard;
int purse;
int deck[deckSize];
int card;
int playerAceTracker;
int dealerAceTracker;
int deckPosition = 0;

void shuffleDeck(){ // shufles a fresh deck of cards.

int tempNum;
	int rand1;
	int rand2;
	

	for(int i = 0; i < deckSize; i++){
		deck[i] = i;
	}

	for(int i = 0; i < 2 * deckSize; i++){
		int rand1 = rand() % 104;
		int rand2 = rand() % 104;
		tempNum = deck[rand1];
		deck[rand1] = deck[rand2];
		deck[rand2] = tempNum;
	}
}

void dealCard(bool Player){
	int suitNum;
	char cardNameArr[14][7] = {"NA", "Ace", "Duce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King",};
	char suitArr[4][10] = {"Clubs", "Hearts", "Spades", "Diamonds",}; // arrays for suit and card name
	suitNum = ((deck[deckPosition] / 13) % 4 );//finds the suit of the card
	card = (deck[deckPosition] % 13) + 1; //Draws card from the shuffled deck
	char *suit = suitArr[suitNum]; 
	char *cardName = cardNameArr[card];  // makes a character veriable for the name and suit of the current card
	
	
	if (card > 10){ //Accounts for the value of a face card
		card = 10;
	}
	
	if (Player == 0){
		printf("Dealer drew a %s of %s\n", cardName, suit);
		if (card == 1){ //Checks if card is an ace and assigns any ace as 11
			dealerAceTracker += 1;
			card == 11;
		}
		
		dealerScore += card;
		
		if (dealerScore > 21 && dealerAceTracker > 0){ //Checks if an ace puts the dealer over 21 and converts the ace to 1 if so
			dealerScore -= 10;
			dealerAceTracker -= 1;
		}
	}
	
	if (Player == 1){
		printf("Player drew a %s of %s\n", cardName, suit);
		if (card == 1){ //Checks if card is an ace and assigns any ace as 11
			playerAceTracker += 1;
			card == 11;
		}
		
		playerScore += card;
		
		if (playerScore > 21 && dealerAceTracker > 0){ //Checks if an ace puts the player over 21 and converts the ace to 1 if so
			playerScore -= 10;
			playerAceTracker -= 1;
		}
	}
		
	deckPosition += 1;
}

void main(){
	srand(time(NULL));
	shuffleDeck();
	dealCard(1);
	dealCard(1);
	printf("current score: %d", playerScore);
	
	
}
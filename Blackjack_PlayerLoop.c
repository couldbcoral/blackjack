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
int turnCount = 0;

void shuffleDeck(){ // shuffles a fresh deck of cards.

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
	
	
turnCount++;
	
	if (card > 10){ //Accounts for the value of a face card
		card = 10;
	}
	
	if (Player == 0){
		printf("Dealer drew a %s of %s\n", cardName, suit);
		if (card == 1){ //Checks if card is an ace and assigns any ace as 11
			dealerAceTracker += 1;
			card = 11;
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
			card = 11;
		}
		
		playerScore += card;
		
		if (playerScore > 21 && playerAceTracker > 0){ //Checks if an ace puts the player over 21 and converts the ace to 1 if so
			playerScore -= 10; 
			playerAceTracker -= 1; 
		}
	}
		
	deckPosition += 1;
}

void dealerTurn() {
	if (dealerScore <= 16) {
		dealCard(false);
	}
	else {
		return;
	}
}

void playerTurn() {
    int choice;

    while (1) {
        printf("Press 1 to hit or 2 to stand.\n");
        scanf("%d", &choice);

        while (choice != 1 && choice != 2) {
            printf("ERROR... Choose 1 to hit or 2 to stand.\n");
            scanf("%d", &choice);
        }

        if (choice == 1) {
            dealCard(true);
            printf("Player score: %d\n", playerScore);

            if (playerScore > 21) {
                printf("Player busts!\n");
                return;
            }
        } 
        else {
            return; // player stands
        }
    }
}


void compareScore(int playerScore, int dealerScore) {
	if (dealerScore == playerScore) {
		printf("Push!\n");
	}
	else if (dealerScore > playerScore) {
		printf("You lose!\n");
	}
	else if (dealerScore < playerScore) {
		printf("Hand won!\n");
	}
	return;
}
int main(){
	srand(time(NULL));
	shuffleDeck();
	dealCard(1);
	
	dealCard(0);
	dealCard(0);
	printf("Dealer shows: %d\n", dealerScore);
	dealCard(1);
	printf("current score: %d\n", playerScore);
	playerTurn();
	printf("Current score: %d\n", playerScore);
	if (playerScore >= 21) {
		printf("You lost!\n");
		
		return 0;
	}
	while (dealerScore <= 16) {
		dealCard(0);
		
	}
	printf("Dealer score: %d\n", dealerScore);
	compareScore(playerScore, dealerScore);
	
}
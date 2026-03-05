#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define deckSize 104
int playerScore;
int dealerScore;
int playerCard;
int dealerCard;
int purse;
int deck[deckSize];
int card;

void shufleDeck(){ // shufles a frsh deck of cards.

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

void main(){
	/*srand(time(NULL));
	shufleDeck();
	for(int i = 0; i < 104; i++){
		printf("%d, ", deck[i]);
	}
	test deck shufle
	*/
}
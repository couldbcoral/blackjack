#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <ncurses.h>

#define deckSize 208
int playerScore;
int dealerScore;
int playerCard;
int dealerCard;
int purse;
int deck[deckSize];
int card;
int dealcard;
int suitNum;
int dealsuitNum;
int playerAceTracker;
int dealerAceTracker;
int deckPosition = 0;
char cardNameArr[14][7] = {"NA", "Ace", "Duce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King",};
char suitArr[4][10] = {"Clubs", "Hearts", "Spades", "Diamonds",}; // arrays for suit and card name
char cardAskii[4][14][80] = {{"NA", "  _____ \n |A _  |\n | ( ) |\n |(_'_)|\n |  |  |\n |____V| \n\n","  _____  \n |2    | \n |  &  | \n |     | \n |  &  | \n |____Z| \n\n" , 
								"  _____  \n |3    | \n | & & | \n |  &  | \n |     | \n |____E| \n\n", "  _____  \n |4    | \n | & & | \n |     | \n | & & | \n |____h| \n\n", 
								"  _____  \n |5    | \n | & & | \n |  &  | \n | & & | \n |____S| \n\n", "  _____  \n |6    | \n |& & &| \n |     | \n |& & &| \n |____V| \n\n",
								"  _____  \n |7    | \n | & & | \n |& & &| \n | & & | \n |____L| \n\n", "  _____  \n |8    | \n |& & &| \n | & & | \n |& & &| \n |____8| \n\n", 
								"  _____  \n |9    | \n |& & &| \n |& & &| \n |& & &| \n |____6| \n\n", "  _____  \n |10 & | \n |& & &| \n |& & &| \n |& & &| \n |___0I| \n\n", 
								"  _____  \n |Q  ww| \n | & {(| \n |(.)%%| \n | |%%%| \n |_%%%O| \n\n", "  _____  \n |Q  ww| \n | & {(| \n |(.)%%| \n | |%%%| \n |_%%%O| \n\n", 
								"  _____  \n |K  WW| \n | & {)| \n |(.)%%| \n | |%%%| \n |_%%%>| \n\n"}, {"NA", "  _____ \n |A_ _ |\n |( v )|\n | \\ / |\n |  .  |\n |____0| \n\n", "  _____  \n |2    | \n |  v  | \n |     | \n |  v  | \n |____Z| \n\n", 
								"  _____  \n |3    | \n | v v | \n |  v  | \n |     | \n |____E| \n\n", "  _____  \n |4    | \n | v v | \n |     | \n | v v | \n |____h| \n\n", 
								"  _____  \n |5    | \n | v v | \n |  v  | \n | v v | \n |____S| \n\n", "  _____  \n |6    | \n |v v v| \n |     | \n |v v v| \n |____V| \n\n",
								"  _____  \n |7    | \n | v v | \n |v v v| \n | v v | \n |____L| \n\n", "  _____  \n |8    | \n |v v v| \n | v v | \n |v v v| \n |____8| \n\n", 
								"  _____  \n |9    | \n |v v v| \n |v v v| \n |v v v| \n |____6| \n\n", "  _____  \n |10 v | \n |v v v| \n |v v v| \n |v v v| \n |___0I| \n\n", 
								"  _____  \n |Q  ww| \n | v {(| \n |(.)%%| \n | |%%%| \n |_%%%O| \n\n", "  _____  \n |Q  ww| \n | v {(| \n |(.)%%| \n | |%%%| \n |_%%%O| \n\n", 
								"  _____  \n |K  WW| \n | v {)| \n |(.)%%| \n | |%%%| \n |_%%%>| \n\n"}, {"NA", "  _____ \n |A ^  |\n | /.\\ |\n |(_._)|\n |  |  |\n |____0| \n\n", "  _____  \n |2    | \n |  ^  | \n |     | \n |  ^  | \n |____Z| \n\n", 
								"  _____  \n |3    | \n | ^ ^ | \n |  ^  | \n |     | \n |____E| \n\n", "  _____  \n |4    | \n | ^ ^ | \n |     | \n | ^ ^ | \n |____h| \n\n", 
								"  _____  \n |5    | \n | ^ ^ | \n |  ^  | \n | ^ ^ | \n |____S| \n\n", "  _____  \n |6    | \n |^ ^ ^| \n |     | \n |^ ^ ^| \n |____^| \n\n",
								"  _____  \n |7    | \n | ^ ^ | \n |^ ^ ^| \n | ^ ^ | \n |____L| \n\n", "  _____  \n |8    | \n |^ ^ ^| \n | ^ ^ | \n |^ ^ ^| \n |____8| \n\n", 
								"  _____  \n |9    | \n |^ ^ ^| \n |^ ^ ^| \n |^ ^ ^| \n |____6| \n\n", "  _____  \n |10 ^ | \n |^ ^ ^| \n |^ ^ ^| \n |^ ^ ^| \n |___0I| \n\n", 
								"  _____  \n |Q  ww| \n | ^ {(| \n |(.)%%| \n | |%%%| \n |_%%%O| \n\n", "  _____  \n |Q  ww| \n | ^ {(| \n |(.)%%| \n | |%%%| \n |_%%%O| \n\n", 
								"  _____  \n |K  WW| \n | ^ {)| \n |(.)%%| \n | |%%%| \n |_%%%>| \n\n"}, {"NA", "  _____ \n |A ^  |\n | / \\ |\n | \\ / |\n |  v  |\n |____V| \n\n", "  _____  \n |2    | \n |  0  | \n |     | \n |  0  | \n |____Z| \n\n", 
								"  _____  \n |3    | \n | 0 0 | \n |  0  | \n |     | \n |____E| \n\n", "  _____  \n |4    | \n | 0 0 | \n |     | \n | 0 0 | \n |____h| \n\n", 
								"  _____  \n |5    | \n | 0 0 | \n |  0  | \n | 0 0 | \n |____S| \n\n", "  _____  \n |6    | \n |0 0 0| \n |     | \n |0 0 0| \n |____0| \n\n",
								"  _____  \n |7    | \n | 0 0 | \n |0 0 0| \n | 0 0 | \n |____L| \n\n", "  _____  \n |8    | \n |0 0 0| \n | 0 0 | \n |0 0 0| \n |____8| \n\n", 
								"  _____  \n |9    | \n |0 0 0| \n |0 0 0| \n |0 0 0| \n |____6| \n\n", "  _____  \n |10 0 | \n |0 0 0| \n |0 0 0| \n |0 0 0| \n |___0I| \n\n", 
								"  _____  \n |Q  ww| \n | 0 {(| \n |(.)%%| \n | |%%%| \n |_%%%O| \n\n", "  _____  \n |Q  ww| \n | 0 {(| \n |(.)%%| \n | |%%%%%%| \n |_%%%O| \n\n" , 
								"  _____  \n |K  WW| \n | 0 {)| \n |(.)%%| \n | |%%%| \n |_%%%>| \n\n"}};
char keyPressed;
void shuffleDeck(){ // shufles a fresh deck of cards.

int tempNum;
	int rand1;
	int rand2;
	

	for(int i = 0; i < deckSize; i++){
		deck[i] = i;
	}

	for(int i = 0; i < 2 * deckSize; i++){
		int rand1 = rand() % deckSize;
		int rand2 = rand() % deckSize;
		tempNum = deck[rand1];
		deck[rand1] = deck[rand2];
		deck[rand2] = tempNum;
	}
}

void dealCard(bool Player){
	suitNum = ((deck[deckPosition] / 13) % 4 );//finds the suit of the card
	card = (deck[deckPosition] % 13) + 1; //Draws card from the shuffled deck
	dealcard = card;
	dealsuitNum = suitNum;
	char *suit = suitArr[suitNum]; 
	char *cardName = cardNameArr[card];  // makes a character veriable for the name and suit of the current card
	int originalCard = card;
	
	if (card > 10){ //Accounts for the value of a face card
		card = 10;
	}
	
	if (Player == 0){
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
		printw("Player drew a %s of %s\n", cardName, suit);
		printw("%s", cardAskii[suitNum][originalCard]);
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

void compareScore(int playerScore, int dealerScore){
	if (dealerScore > 21){
		printw("Dealer Busts, Player Wins!\n");
	}
	else if (dealerScore > playerScore){
		printw("Dealer Wins!\n");
	}
	else if (dealerScore < playerScore){
		printw("Player Wins!\n");
	}
	else if (dealerScore == playerScore){
		printw("It's a Push!\n");
	}
	printw("\nPress the Spacebar to play again\n Press q to quit");
}

void main(){
	srand(time(NULL));
	shuffleDeck();
	initscr();            // Start ncurses mode
    cbreak();             // Line buffering disabled
    noecho();             // Don't echo() while we do getch
	scrollok(stdscr, TRUE);
	refresh();
	int suitNum;
	int numLoops = 1;
	printw("Press the Spacebar to begin Blackjack\n");
    while((keyPressed = getch()) != 'q'){
		dealCard(1);
		dealCard(1);
		printw("Players' hand is %d\n", playerScore);
		dealCard(0);
		printw("Dealer is showing a %s of %s\n", cardNameArr[dealcard], suitArr[dealsuitNum]);//Shows what the dealer drew earlier
		printw("%s", cardAskii[dealsuitNum][dealcard]);
		dealCard(0);
		printw("Please Press:\n1. Hit\n2. Stand\n");
		while((keyPressed = getch()) == '1'){
			dealCard(1);
			printw("Players' hand is %d\n", playerScore);
		
			if (playerScore > 21){
				printw("You Bust!");
				printw("\nPress the Spacebar to play again\n Press q to quit");
			}
		}
		while((keyPressed = getch()) == '2'){
			printw("Dealer is showing a %s of %s\n", cardNameArr[dealcard], suitArr[dealsuitNum]);//Shows what the dealer drew earlier
			printw("%s", cardAskii[dealsuitNum][dealcard]);
			printw("Dealers' hand is %d\n", dealerScore);
		
			while (dealerScore < 17){
				dealCard(0);
				printw("Dealer is showing a %s of %s\n", cardNameArr[dealcard], suitArr[dealsuitNum]);//Shows what the dealer drew earlier
				printw("%s", cardAskii[dealsuitNum][dealcard]);
				printw("Dealers' hand is %d\n", dealerScore);
			}
		
			compareScore(playerScore, dealerScore);
		}
	
	//printw("%d", numLoops);
	//numLoops ++;
	playerScore = 0;
	dealerScore = 0;
	}		// Wait for final key press
    endwin();  // End ncurses mode
}
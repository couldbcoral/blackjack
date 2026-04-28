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
		printw("Dealer drew a %s of %s\n", cardName, suit);
		printw("%s", cardAskii[suitNum][dealcard]);
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

void main(){
	srand(time(NULL));
	shuffleDeck();
	/*dealCard(1);
	dealCard(1);
	printf("current score: %d", playerScore);
	*/
	
	
	initscr();            // Start ncurses mode
    cbreak();             // Line buffering disabled
    noecho();             // Don't echo() while we do getch
	scrollok(stdscr, TRUE);
   // keypad(stdscr, TRUE); // Enable arrow keys

 


    //while((keyPressed = getch()) == 'ERR') {
    //}
	
	refresh();
	/*char cardAskii[4][14][80] = {{"NA", "  _____ \n |A _  |\n | ( ) |\n |(_'_)|\n |  |  |\n |____V| \n\n","  _____  \n |2    | \n |  &  | \n |     | \n |  &  | \n |____Z| \n\n" , 
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
	
	*/

    /* Example of string input
    echo(); // Re-enable echoing for string input
    printw("\n\nEnter your name: ");
    getstr(str);
    printw("Hello, %s!", str);
    refresh();
	*/
	//printw("%s", cardAskii[0][3]);
	/* The 2 of diamonds
    printw("  _____  \n |2    | \n |  ^  | \n |     | \n |  ^  | \n |____Z| \n\n");
	// 3
    printw("  _____  \n |3    | \n | ^ ^ | \n |  ^  | \n |     | \n |____E| \n\n");
	// 4
    printw("  _____  \n |4    | \n | ^ ^ | \n |     | \n | ^ ^ | \n |____h| \n\n");
	// 5
    printw("  _____  \n |5    | \n |^ ^  | \n |  ^  | \n |  ^ ^| \n |____S| \n\n");
	// 6
    printw("  _____  \n |6    | \n |^ ^ ^| \n |     | \n |^ ^ ^| \n |____V| \n\n");
	// 7
    printw("  _____  \n |7    | \n | ^ ^ | \n |^ ^ ^| \n | ^ ^ | \n |____L| \n\n");
	// 8
    printw("  _____  \n |8    | \n |^ ^ ^| \n | ^ ^ | \n |^ ^ ^| \n |____8| \n\n");
	// 9
    printw("  _____  \n |9    | \n |^ ^ ^| \n |^ ^ ^| \n |^ ^ ^| \n |____6| \n\n");
	// 10
    printw("  _____  \n |10 ^ | \n |^ ^ ^| \n |^ ^ ^| \n |^ ^ ^| \n |___0I| \n\n");
	// Jack
    printw("  _____  \n |J  ww| \n | ^ {)| \n |(.)%% | \n | | %% | \n |__%%%%[| \n\n");
	// Queen
    printw("  _____  \n |Q  ww| \n | ^ {(| \n |(.)%%%%| \n | |%%%%%%| \n |_%%%%%%O| \n\n");
	// King
    printw("  _____  \n |K  WW| \n | ^ {)| \n |(.)%%%%| \n | |%%%%%%| \n |_%%%%%%>| \n\n");
	// The Ace of diamonds
    printw("  _____  \n |A .  | \n | /.\\ | \n |(_._)| \n |  |  | \n |____V| \n\n");
	*/
	int suitNum;
	int numLoops = 1;
    while((keyPressed = getch()) != 'q'){
	//printw("%d", keyPressed);
	
	/*if (keyPressed == 99) suitNum = 0;
	if (keyPressed == 104) suitNum = 1;
	if (keyPressed == 115) suitNum = 2;
	if (keyPressed == 100) suitNum = 3;
	if (keyPressed > 48 && keyPressed < 62){ 
	card = ((int) keyPressed - 48);
	printw("%s", cardAskii[suitNum][card]);
	}
	//printw("%s", cardptr);
	*/
	dealCard(1);
	dealCard(0);
	printw("Dealer drew a %s of %s\n", cardNameArr[dealcard], suitArr[dealsuitNum]);
	printw("%s", cardAskii[dealsuitNum][dealcard]);
	
	printw("%d", numLoops);
	numLoops ++;
	
	}		// Wait for final key press
    endwin();  // End ncurses mode
	//printf("your typed: %c", keyPressed);
	
	
}
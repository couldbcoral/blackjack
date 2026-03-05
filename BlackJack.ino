int PlayerScore = 0;
int DealerScore = 0;
int DealerAceTracker = 0;
int PlayerAceTracker = 0;
int PlayerBust = 0;
int DealerBust = 0;
int Stand = 0;
int Wins = 0;
int Losses = 0;
#include <LiquidCrystal.h>

const int rs = 10, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(2));
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0,1);
  lcd.print("S");
  lcd.setCursor(15,1);
  lcd.print("H");
  lcd.setCursor(3,0);
  lcd.print(":D");
  lcd.setCursor(11,0);
  lcd.print("P:");
  lcd.setCursor(7,0);
  lcd.print("-");

}
//Deals a card to either dealer or player depending on if the input is a 0 or 1 respectively.
void dealCard(bool Player){
  int Card = (random(1, 13));
  if (Card > 10){
    Card = 10;
  }
  
  //deals 1 card to dealer and checks if it is an ace or not.
  if (Player == 0){
    DealerScore += Card;
    if (Card == 1){
    DealerAceTracker++;
    Card = 11;
    }
    //checks if the dealer has an ace and is over 21 and if so turnes the ace from an 11 to a 1.
    if (DealerScore > 21 && DealerAceTracker > 0){
      DealerScore -= 10;
      DealerAceTracker --;
    }
  }
    //deals card to player and checks if it is an ace or not.
    if (Player == 1){
    PlayerScore += Card;
    if (Card == 1){
    PlayerAceTracker++;
    Card = 11;
    }
    //checks if the player has an ace and is over 21 and if so it turnes the ace from an 11 to a 1.
    if (PlayerScore > 21 && PlayerAceTracker > 0){
      PlayerScore -= 10;
      PlayerAceTracker --;
    

    }

    }
}

void loop() {
PlayerScore = 0;
DealerScore = 0;
PlayerAceTracker = 0;
DealerAceTracker = 0;
PlayerBust = 0;
DealerBust = 0;
Stand = 0;
//deals starting cards and shows you one of the dealers and your score
dealCard(0);
  if(DealerScore < 10){
        lcd.setCursor(1,0);
        lcd.print(" ");
      }
  lcd.setCursor(0,0);
  lcd.print(DealerScore);
  dealCard(0);
  dealCard(1);
  dealCard(1);
  lcd.setCursor(14,0);
  if(PlayerScore < 10){
        lcd.print(" ");
        lcd.setCursor(15,0);
      }
      lcd.print(PlayerScore);
//gives the player the option to hit or stand and waits for them to press a button. 
  lcd.setCursor(1,1);
  lcd.print("|Hit or Stand|");
  while(Stand + PlayerBust == 0){
    //if player hits the Hit button deals them a card shows their score and checks for a bust.
    if(digitalRead(12) == HIGH){
      while(digitalRead(12) > 0){
        delay(50);
      }
      dealCard(1);
      lcd.setCursor(14,0);
      if(PlayerScore < 10){
        lcd.print(" ");
        lcd.setCursor(15,0);
      }
      lcd.print(PlayerScore);
      if(PlayerScore > 21){
        PlayerBust = 1;
      }
    }
    //if player hits the Stand button it ends their turn and lets the dealer play out.
    if(digitalRead(11) == HIGH){
      while(digitalRead(11) > 0){
        delay(50);
      }
      lcd.setCursor(2, 1);
      lcd.print("  Stand   ");
    Stand = 1;
    }
  }
  delay(500);
  //checks to see if the player busted and if so tells you so and shows you what the dealer had.
  if(PlayerBust == 1){
    lcd.setCursor(0,0);
    lcd.println(DealerScore);
    lcd.setCursor(2,1);
    lcd.print("You BUSTED");
    PlayerScore = 0;
  }
  //if player did not bust it starts the Dealer logic.
  if(PlayerBust == 0){
    if(DealerScore > 17){
      lcd.setCursor(0,0);
      lcd.print(DealerScore);
    }
    //keeps dealing the dealer cards untill it either busts or reaches above 16.
    while(DealerScore < 17 && DealerBust == 0){
      delay(500);
      if(DealerScore < 10){
        lcd.setCursor(1,0);
        lcd.print(" ");
      }
      lcd.setCursor(0,0);
      lcd.print(DealerScore);
      dealCard(0);
      if (DealerScore > 21){
        delay(1000);
        DealerBust = 1;
        lcd.setCursor(0,0);
        lcd.print(DealerScore);
        lcd.setCursor(2,2);
        lcd.print("Dealer Bust");
        DealerScore = 0;
      }
      else{
        lcd.setCursor(0,0);
        lcd.print(DealerScore);
      }
      delay(1000);
    }
  }
  //checks to see how the game ended and displays the correct ending text.
  lcd.setCursor(2,1);
  if(DealerBust + PlayerBust == 0){
  }
  
  if (PlayerScore > DealerScore){
    lcd.print(" You Win  ");
    Wins++;
  }
  if (PlayerScore < DealerScore){
    lcd.print(" You Lose ");
    Losses++;
  }
  if(PlayerScore == DealerScore) {
    lcd.println("You Pushed");
  }
  lcd.setCursor(6,0);
  if(Losses > 9){
    lcd.setCursor(5,0);
  }
  //prints your overall wins and losses.
  lcd.print(Losses);
  lcd.setCursor(7,0);
  lcd.print("-");
  lcd.setCursor(8,0);
  lcd.print(Wins);
  delay(1500);
}

/*
Authors: Wesley Toney, John Umble, Nick Gillot, James Leach
Course: COMP 220
Date: 9/25/2014
Description: The main driver file for Project 2, this file simulates the card game 
"Kings on the Corners".
*/

//initialization
#include <iostream>
#include "Card.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "Column.h"

using std::cout;
using std::endl;
using std::cin;
using std::ios;
using std::string;
using std::vector;
using std::random_shuffle;
using std::rand;
using std::srand;


//waits 1.5 seconds
void delay(){
	Sleep(1500);
}


//Board class definition. Contains capacity for shuffling and value/suit conversion.
//Also contains the board columns and deck.
class Board{
public:
	Board();
	void deckShuffle();
	Value intToValue(int intValue);
	Suit intToSuit(int intSuit);
	char valueToChar(Value v);
	char suitToChar(Suit s);
	Column columns[8];
	Column deck;
};

//Constructor, builds the deck
Board::Board() {
	Value valueName;
	Suit suitName;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			valueName = intToValue(j);
			suitName = intToSuit(i);
			Card c(valueName, suitName);
			deck.addCard(c);
		}
	}
	deckShuffle();
	
	//take four off the top of the deck and put them at the four adjacent columns, not corners
	columns[1].addCard(deck.getTop());
	deck.removeCard(deck.getTop());
	columns[3].addCard(deck.getTop());
	deck.removeCard(deck.getTop());
	columns[4].addCard(deck.getTop());
	deck.removeCard(deck.getTop());
	columns[6].addCard(deck.getTop());
	deck.removeCard(deck.getTop());
}

//Shuffles the deck
void Board::deckShuffle(){
	deck.shuffle();
}

//Returns corresponding value to an integer between 0 and 12
Value Board::intToValue(int intValue) {
	switch(intValue) {
	case 0: return ace; break;
	case 1: return deuce; break;
	case 2: return trey; break;
	case 3: return four; break; 
	case 4: return five; break;
	case 5: return six; break;
	case 6: return seven; break;
	case 7: return eight; break;
	case 8: return nine; break;
	case 9: return ten; break;
	case 10: return jack; break;
	case 11: return queen; break;
	case 12: return king; break;
	}
}

//Returns corresponding Suit from an integer in range 0-4
Suit Board::intToSuit(int intSuit) {
	switch(intSuit) {
	case 0: return clubs; break;
	case 1: return diamonds; break;
	case 2: return hearts; break;
	case 3: return spades; break; 
	}
}

//Returns corresponding char from a Value 
char Board::valueToChar(Value v){
	switch(v){
		case ace: return 'A'; break;
		case deuce: return '2'; break;
		case trey: return '3'; break;
		case four: return '4'; break; 
		case five: return '5'; break;
		case six: return '6'; break;
		case seven: return '7'; break;
		case eight: return '8'; break;
		case nine: return '9'; break;
		case ten: return 'T'; break;
		case jack: return 'J'; break;
		case queen: return 'Q'; break;
		case king: return 'K'; break;
	}
}

//Returns corresponding char from a Suit 
char Board::suitToChar(Suit s){
	switch(s){
		case clubs: return 'C'; break;
		case diamonds: return 'D'; break;
		case hearts: return 'H'; break;
		case spades: return 'S'; break; 
	}
}



//Returns true if card arguments are two different
bool areDifferentColors(Card c1, Card c2){
	if (c1.getSuit() == clubs && c2.getSuit() == diamonds) {return true;}
	else if (c1.getSuit() == clubs && c2.getSuit() == hearts) {return true;}
	else if (c1.getSuit() == spades && c2.getSuit() == diamonds) {return true;}
	else if (c1.getSuit() == spades && c2.getSuit() == hearts) {return true;}
	else if (c1.getSuit() == diamonds && c2.getSuit() == clubs) {return true;}
	else if (c1.getSuit() == diamonds && c2.getSuit() == spades) {return true;}
	else if (c1.getSuit() == hearts && c2.getSuit() == clubs) {return true;}
	else if (c1.getSuit() == hearts && c2.getSuit() == spades) {return true;}
	else {return false;}
}

//Checks if moving one card onto another is a valid move.
bool isValidMove(Card source, Card dest){
	if (((dest.getValue()-source.getValue()==1))&&(areDifferentColors(source,dest))){
		return 1; // if source is 1 less than dest and they are not the same color
	}
	return 0;
}

//Checks if moving one card onto a column is a valid move.
bool isValidMove(Card source, Column dest, bool corner){

	if(dest.size()==0&&corner){
		if (source.getValue()==12){
		return 1;
		}
		else{
			return 0;
		}
	}
	if(dest.size()==0&&!corner){
		return 1;
	}


	if ((dest.getBottom().getValue()-source.getValue()==1)&&(areDifferentColors(source,dest.getBottom()))){
		return 1; // if source is 1 less than dest and they are not the same suit
		}
	//cout<<"we fell through";
	//system("pause");
	return 0;
}

//Checks if moving one column onto another is a valid move.
bool isValidMove(Column source, Column dest){
	if(dest.size()==0&&source.getTop().getValue()==12){
		return 1;
	}
	return isValidMove(source.getTop(), dest.getBottom());
}

//Draws the current board state to the screen.
void drawBoard(Board b){
	cout<<"1----2----3----+\n";

	if(b.columns[0].size()>1) cout<<"| "<<b.valueToChar(b.columns[0].getTop().getValue())<<b.suitToChar(b.columns[0].getTop().getSuit())<<" ";
	else cout<<"|    ";
	if(b.columns[1].size()>1) cout<<"| "<<b.valueToChar(b.columns[1].getTop().getValue())<<b.suitToChar(b.columns[1].getTop().getSuit())<<" ";
	else cout<<"|    ";
	if(b.columns[2].size()>1) cout<<"| "<<b.valueToChar(b.columns[2].getTop().getValue())<<b.suitToChar(b.columns[2].getTop().getSuit())<<" |\n";
	else cout<<"|    |\n";

	if(b.columns[0].size()==1) cout<<"| "<<b.valueToChar(b.columns[0].getBottom().getValue())<<b.suitToChar(b.columns[0].getBottom().getSuit())<<" ";
	else cout<<"| // ";
	if(b.columns[1].size()==1) cout<<"| "<<b.valueToChar(b.columns[1].getBottom().getValue())<<b.suitToChar(b.columns[1].getBottom().getSuit())<<" ";
	else cout<<"| // ";
	if(b.columns[2].size()==1) cout<<"| "<<b.valueToChar(b.columns[2].getBottom().getValue())<<b.suitToChar(b.columns[2].getBottom().getSuit())<<" |\n";
	else cout<<"| // |\n";

	if(b.columns[0].size()>1) cout<<"| "<<b.valueToChar(b.columns[0].getBottom().getValue())<<b.suitToChar(b.columns[0].getBottom().getSuit())<<" ";
	else cout<<"|    ";
	if(b.columns[1].size()>1) cout<<"| "<<b.valueToChar(b.columns[1].getBottom().getValue())<<b.suitToChar(b.columns[1].getBottom().getSuit())<<" ";
	else cout<<"|    ";
	if(b.columns[2].size()>1) cout<<"| "<<b.valueToChar(b.columns[2].getBottom().getValue())<<b.suitToChar(b.columns[2].getBottom().getSuit())<<" |\n";
	else cout<<"|    |\n";

	cout<<"4----+----5----+\n";

	if(b.columns[3].size()>1) cout<<"| "<<b.valueToChar(b.columns[3].getTop().getValue())<<b.suitToChar(b.columns[3].getTop().getSuit())<<" ";
	else cout<<"|    ";
	cout<<"|K   ";
	if(b.columns[4].size()>1) cout<<"| "<<b.valueToChar(b.columns[4].getTop().getValue())<<b.suitToChar(b.columns[4].getTop().getSuit())<<" |\n";
	else cout<<"|    |\n";

	if(b.columns[3].size()==1) cout<<"| "<<b.valueToChar(b.columns[3].getBottom().getValue())<<b.suitToChar(b.columns[3].getBottom().getSuit())<<" ";
	else cout<<"| // ";
	cout<<"|O  T";
	if(b.columns[4].size()==1) cout<<"| "<<b.valueToChar(b.columns[4].getBottom().getValue())<<b.suitToChar(b.columns[4].getBottom().getSuit())<<" |\n";
	else cout<<"| // |\n";

	if(b.columns[3].size()>1) cout<<"| "<<b.valueToChar(b.columns[3].getBottom().getValue())<<b.suitToChar(b.columns[3].getBottom().getSuit())<<" ";
	else cout<<"|    ";
	cout<<"|   C";
	if(b.columns[4].size()>1) cout<<"| "<<b.valueToChar(b.columns[4].getBottom().getValue())<<b.suitToChar(b.columns[4].getBottom().getSuit())<<" |\n";
	else cout<<"|    |\n";

	cout<<"6----7----8----+\n";

	if(b.columns[5].size()>1) cout<<"| "<<b.valueToChar(b.columns[5].getTop().getValue())<<b.suitToChar(b.columns[5].getTop().getSuit())<<" ";
	else cout<<"|    ";
	if(b.columns[6].size()>1) cout<<"| "<<b.valueToChar(b.columns[6].getTop().getValue())<<b.suitToChar(b.columns[6].getTop().getSuit())<<" ";
	else cout<<"|    ";
	if(b.columns[7].size()>1) cout<<"| "<<b.valueToChar(b.columns[7].getTop().getValue())<<b.suitToChar(b.columns[7].getTop().getSuit())<<" |\n";
	else cout<<"|    |\n";

	if(b.columns[5].size()==1) cout<<"| "<<b.valueToChar(b.columns[5].getBottom().getValue())<<b.suitToChar(b.columns[5].getBottom().getSuit())<<" ";
	else cout<<"| // ";
	if(b.columns[6].size()==1) cout<<"| "<<b.valueToChar(b.columns[6].getBottom().getValue())<<b.suitToChar(b.columns[6].getBottom().getSuit())<<" ";
	else cout<<"| // ";
	if(b.columns[7].size()==1) cout<<"| "<<b.valueToChar(b.columns[7].getBottom().getValue())<<b.suitToChar(b.columns[7].getBottom().getSuit())<<" |\n";
	else cout<<"| // |\n";

	if(b.columns[5].size()>1) cout<<"| "<<b.valueToChar(b.columns[5].getBottom().getValue())<<b.suitToChar(b.columns[5].getBottom().getSuit())<<" ";
	else cout<<"|    ";
	if(b.columns[6].size()>1) cout<<"| "<<b.valueToChar(b.columns[6].getBottom().getValue())<<b.suitToChar(b.columns[6].getBottom().getSuit())<<" ";
	else cout<<"|    ";
	if(b.columns[7].size()>1) cout<<"| "<<b.valueToChar(b.columns[7].getBottom().getValue())<<b.suitToChar(b.columns[7].getBottom().getSuit())<<" |\n";
	else cout<<"|    |\n";

	cout<<"+----+----+----+\n\n";
}

//Displays the rules.
void displayRules(){
	cout<<"\nAt the beginning of the game every player is dealt 7 cards. At the\n"<<
		"start of every turn, the player must draw a card from the top of the "<<
		"deck.\n\nThe goal of the game is to play cards from your hand onto one \n"<<
		"of the columns. The card played must be next lower in rank and\n"<<
		"opposite in color to the current card.  You can play any card onto \n"<<
		"empty columns around the straight sides of the deck, but only kings may\n"<<
		"be played to begin the corners of the deck. You may also stack columns.  \nIf you cannot "<<
		"make any more moves, end your turn. \n\nThe game ends when someone plays "<<
		"all the cards in their hand.\n\n";
}


//Player class. Contains hands, card movement functionality
class Player{
	public:
		Player();
		void showHand();
		void place(Card crd, Column &clmn); // places a card on a column
		void place(Column &clmn1, Column &clmn2); // places column2 on column1
		void endTurn();//ends player's turn
		void draw(Column deck);
		bool pass; //maybe make this private? Must be initialized to 0 in constructor
		vector<Card> hand;
	private:
};

//Default constructor.
Player::Player() {
	pass = false;
}

//Outputs the contents of the player's hand to the screen.
void Player::showHand() // start of showHand function
{
	
	for (int i=0; i<hand.size(); i++) cout<<i+1<<") "<<hand.at(i).name()<<endl;
	cout<<endl;
}

//Places a card from the player's hand in a column.
void Player::place(Card crd, Column &clmn)
{
	int i=0;
	for (i; i<hand.size(); i++)
	{
		if (hand.at(i).name() == crd.name()) // if a card in the hand == crd
			break;
	}

	clmn.addCard(hand.at(i)); 
	hand.erase(hand.begin() + i);
}

//Moves one column onto another.
void Player::place(Column &clmn1, Column &clmn2)
{
	for (int i=0; i<clmn1.size(); i++)
		clmn2.addCard(clmn1.getCard(i));

	clmn1.clear();
}

//Ends the player's turn (deprecated).
void Player::endTurn()
{
	pass = true;
}

//Draws a card.
void Player::draw(Column deck)
{
	Card drawn = deck.getTop();
	hand.push_back(drawn);
	deck.removeCard(drawn);
}

//aiPlayer class. Contains logic for the AI player.
class aiPlayer: public Player{
public:
	bool validLocation[8];
	void actionsLoop(Board &b);
	void findValidLocations(Card source, Board &b);
	void clearValidLocations();
	bool victory();
	bool takeTurn(Board &b);
private:
};

//THe actual AI.
void aiPlayer::actionsLoop(Board &b){

	draw(b.deck);//draw card
	b.deck.removeCard(b.deck.getTop());
	cout<<"Computer player drew a card. He has "<<hand.size()<<" cards in hand."<<"\n";
	delay();
	clearValidLocations();//initialize valid location array
	for(int i=0; i<8; i++){
		if(b.columns[i].size()!=0) findValidLocations(b.columns[i].getBottom(),b);//find valid destinations for columns
	}
	for(int i=0; i<8; i++){
		validLocation[i]=0;
		for(int j=0;j<8;j++){
			if(b.columns[j].size()==0) validLocation[j]=0;//Don't put a column onto itself
			if(validLocation[j]){
				validLocation[j]=0;
				place(b.columns[i],b.columns[j]); //Place a column
				cout<<"Computer player moved column "<<i+1<<" onto column "<<j+1<<".\n";
				delay();
				i=0;
				break;
			}
		}
			for(int k=0; k<hand.size(); k++){
				findValidLocations(hand.at(k),b);//find valid destinations for cards
				for(int l=0;l<8;l++){
					if(validLocation[l]){
						validLocation[l]=0;
						cout<<"Computer player played a "<<hand.at(k).name()<<" on column "<<l+1<<".\n";
						delay();
						place(hand[k],b.columns[l]);//Play a valid card
						i=0;//Restart loop to ensure thoroughness
						k=0;
						l=0;
						break;
					}
				}
			}
	}
	delay();
	cout<<"Computer player passed the turn.\n";
	delay();
	delay();
	system("cls");
}

//Finds valid locations for a card to be placed onto the board.
void aiPlayer::findValidLocations(Card source, Board &b){
	for(int i=0;i<8;i++){
		validLocation[i]=0;
		bool corner=0;
		if(i==0||i==2||i==5||i==7) corner=1;
		if(isValidMove(source,b.columns[i],corner)){
			validLocation[i]=1;
		}
	}
}

//Resets list of valid locations.
void aiPlayer::clearValidLocations(){
	for(int i=0;i<8;i++){
		validLocation[i]=0;
	}
}

//Returns 1 if hand size = 0 (deprecated)
bool aiPlayer::victory(){
	return(hand.size()==0);
}

//Takes turn (deprecated)
bool aiPlayer::takeTurn(Board &b){
	actionsLoop(b);
	return(victory());
}



//realPlayer class. Contains input functionality.
class realPlayer: public Player{
public:
	void actionsLoop(Board &b);
	int displayMenu();
	int chooseFromCardsInHand();
	int chooseLocation();
private:
};

//Allows choosing of one card from your hand.
int realPlayer::chooseFromCardsInHand()
{
	int chosenCard = 0;
	showHand();
	do{
	cout << "Pick a card from your hand (1-"<< hand.size() << ")\n>>";
	cin >> chosenCard;
	if(chosenCard<1||chosenCard>hand.size()) cout<<"Sorry, invalid choice.\nMake sure you choose an integer between 1 and "<<hand.size()<<".\n";
	}while(chosenCard<1||chosenCard>hand.size());
	return chosenCard-1;
}

//Allows choosing of one column on the board.
int realPlayer::chooseLocation()
{
       int location = 0;
	   do{
       cout << "Choose which column you are referring to, 1 being top-left, 8 being bottom-right.\n" << endl;
       cin >> location;
	   location--;
	   if (location<0||location>7) cout<<"Please choose a valid column!\n";
	   }while (location<0||location>7);
       return location;
}

//Contains input functionality.
void realPlayer::actionsLoop(Board &b){
	drawBoard(b); //draws the board
	draw(b.deck); //draws a card 
	cout<<"It's your turn.\n";
	cout<<"You drew a "<<b.deck.getTop().name()<<".\n";
	b.deck.removeCard(b.deck.getTop());
	
	int choice=0; //variable initialization
	int dest=0;
	int sourceCol=0;
	bool corner=0;
	Card source;

	while(choice!=5){//main input loop
		choice=displayMenu();
		switch(choice){
		case 1://Places a card from your hand onto the board
			drawBoard(b);
			source=hand[chooseFromCardsInHand()];
			dest=chooseLocation();
			corner=0;
			if(dest==0||dest==2||dest==5||dest==7) corner=1;

			if(isValidMove(source, b.columns[dest], corner)){
				place(source,b.columns[dest]);
				system("cls");
				drawBoard(b);
			}
			else{
				system("cls");
				drawBoard(b);
				cout<<"Sorry, not a valid move.\n";
			}
			break;

		case 2://Moves one column onto another column.
			drawBoard(b);
			do{
			cout<<"Choose first location.\n";
			sourceCol=chooseLocation();
			cout<<"Choose second location.\n";
			dest=chooseLocation();
			if(sourceCol==dest) cout<<"Please choose locations that are not identical.\n";
			if(b.columns[dest].size()==0) cout<<"Don't just shuffle columns around, you goof!\n";
			if(b.columns[sourceCol].size()==0) cout<<"You can't move an empty column, silly goose.\n";
			}while((sourceCol==dest)&&(b.columns[dest].size()==0)&&(b.columns[sourceCol].size()==0));

			if(isValidMove(b.columns[sourceCol], b.columns[dest])){
				place(b.columns[sourceCol],b.columns[dest]);
				system("cls");
				drawBoard(b);
			}
			else{
				system("cls");
				drawBoard(b);
				cout<<"Sorry, not a valid move.\n";
			}
			break;

		case 3://Shows your hand.
			drawBoard(b);
			showHand();
			system("pause");
			system("cls");
			drawBoard(b);
			break;

		case 4://Draws the board.
			drawBoard(b);
			break;
		}
		
	}
}

//Outputs turn menu.
int realPlayer::displayMenu(){
	int choice=0;
		cout<<"What would you like to do?\n";
		cout<<"  -1) play a card from your hand\n";
		cout<<"  -2) move a column\n";
		cout<<"  -3) look at your hand\n";
		cout<<"  -4) look at the board\n";
		cout<<"  -5) pass\n";
		cout<<">>";

		while(choice<1||choice>5){
			cin>>choice;
			if(choice<1||choice>5) cout<<"Sorry, please enter a valid integer in range 1-5";
		}
		system("cls");
		return choice;
}


//Outputs main menu.
int mainMenu(){
	cout<<"Welcome to KINGS IN CORNERS\nan ESCAPE POD 4 production\n\n";

	int input=0;
	do{
	cout<<"What would you like to do?\n";
	cout<<"  -1) Start a game\n";
	cout<<"  -2) Display the rules\n";
	cout<<"  -3) Quit\n>>";
	cin>>input;
	if(input<1||input>3) cout<<"\nPlease enter a valid value in range 1 through 3";
	}while(input<1||input>3);
	return input;
}

//Outputs turn menu (deprecated)
int turnMenu()
{
	int answer;
	do{
		cout<<"Would you like to do:\n\n"
			<<"\t1. Place a card\n\t2. Move a column\n\t3. Show Hand\n\t4. Show Board\n\t5. End Turn\n\n";
		cin>>answer;
	}while(answer < 1 || answer > 3); // drops out when answer is between 1 and 3 inclusive
	return answer;
}

//Main driver function.
int main()
{
	//init
	srand(time(0));
	Board b;
	realPlayer human;
	aiPlayer ai;
	string winner;

	//draw initial hands
for(int i=0;i<7;++i){
	human.draw(b.deck);
	b.deck.removeCard(b.deck.getTop());
	ai.draw(b.deck);
	b.deck.removeCard(b.deck.getTop());
	}

	int mode=0;
	while(mode!=3){
		mode=mainMenu();
		system("cls");
		
		switch (mode){
		case 1://run game
			while(true){
				human.actionsLoop(b);
				if(human.hand.size()==0){
					winner="YOU!";
					break;
				}
				ai.actionsLoop(b);
				if(ai.hand.size()==0){
					winner="YOUR COMPUTER!";
					break;
				}	
			}
			cout<<"THE WINNER IS: "<<winner<<"\n";
			break;


		case 2:
			displayRules();//show rules
			system("pause");
			system("cls");
		}
	}
	return 0;
}
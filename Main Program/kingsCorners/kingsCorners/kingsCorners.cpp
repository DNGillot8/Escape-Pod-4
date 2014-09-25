// kingsCorners.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Card.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::endl;
using std::cin;
using std::ios;
using std::string;
using std::vector;
using std::random_shuffle;
using std::rand;
using std::srand;

class Column {
public:
	//void checkIfValid(); //make sure alternating colors, might not be needed
	Column(vector<Card> c);
	Column();
	//Column(int suitInt, int valueInt);
	void addCard(Card c);
	void removeCard(Card c);
	Card getTop() const; //returns the top card of the column
	Card getBottom() const; //returns the bottom card of the column
	Card getCard(int i) const; //returns the card at index i
	void shuffle();
	int size() const;
	void clear();
private:
	vector<Card> cards;
};

Column::Column(vector<Card> c) {
	cards = c;
}

Column::Column() {
	vector<Card> c;
	cards = c;
}

//Column::Column(int suitInt, int valueInt) {
//	Card c(suitInt, valueInt);
//
//}

void Column::addCard(Card c) {
	cards.push_back(c);
}

//maybe don't need
void Column::removeCard(Card c) {
	cards.pop_back();
}

//probably don't need
Card Column::getCard(int i) const {
	return cards.at(i);
}

Card Column::getTop() const {
	return cards.at(cards.size() - 1);
}

Card Column::getBottom() const {
	return cards.at(0);
}

void Column::clear() {
	cards.clear();
}

void Column::shuffle() {
	random_shuffle(cards.begin(), cards.end());
}

int Column::size() const {
	return cards.size();
}

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
	columns[2].addCard(deck.getTop());
	deck.removeCard(deck.getTop());
	columns[4].addCard(deck.getTop());
	deck.removeCard(deck.getTop());
	columns[5].addCard(deck.getTop());
	deck.removeCard(deck.getTop());
	columns[7].addCard(deck.getTop());
	deck.removeCard(deck.getTop());
}

void Board::deckShuffle(){
	deck.shuffle();
}

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

Suit Board::intToSuit(int intSuit) {
	switch(intSuit) {
	case 0: return clubs; break;
	case 1: return diamonds; break;
	case 2: return hearts; break;
	case 3: return spades; break; 
	}
}

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

char Board::suitToChar(Suit s){
	switch(s){
		case clubs: return 'C'; break;
		case diamonds: return 'D'; break;
		case hearts: return 'H'; break;
		case spades: return 'S'; break; 
	}
}



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

bool isValidMove(Card source, Card dest){
	if ((dest.getValue()-source.getValue()==1)&&(areDifferentColors(source,dest))){
		return 1; // if source is 1 less than dest and they are not the same color
	}
	return 0;
}

bool isValidMove(Card source, Column dest){
	if ((dest.getTop().getValue()-source.getValue()==1)&&(areDifferentColors(source,dest.getTop()))){
		return 1; // if source is 1 less than dest and they are not the same suit
	}
	return 0;
}

bool isValidMove(Column source, Column dest){
	return isValidMove(source.getTop(), dest.getBottom());
}


int playerCount(){
	int count=0;
	do{
		cout<<"How many human players want to play (1-4)?\n";
		cin>>count;
	} while (count<=1&&count>=4);
	return count;
}

void drawBoard(Board b){
	cout<<"1----2----3----+\n";

	if(b.columns[1].size()>1) cout<<"| "<<b.valueToChar(b.columns[1].getBottom().getValue())<<b.suitToChar(b.columns[1].getBottom().getSuit())<<" ";
	else cout<<"|    ";
	if(b.columns[2].size()>1) cout<<"| "<<b.valueToChar(b.columns[2].getBottom().getValue())<<b.columns[2].getBottom().getSuit()<<" ";
	else cout<<"|    ";
	if(b.columns[3].size()>1) cout<<"| "<<b.valueToChar(b.columns[3].getBottom().getValue())<<b.columns[3].getBottom().getSuit()<<" |\n";
	else cout<<"|    |\n";

	if(b.columns[1].size()==1) cout<<"| "<<b.columns[1].getTop().getValue()<<b.columns[1].getTop().getSuit()<<" ";
	else cout<<"| // ";
	if(b.columns[2].size()==1) cout<<"| "<<b.columns[2].getTop().getValue()<<b.columns[2].getTop().getSuit()<<" ";
	else cout<<"| // ";
	if(b.columns[3].size()==1) cout<<"| "<<b.columns[3].getTop().getValue()<<b.columns[3].getTop().getSuit()<<" |\n";
	else cout<<"| // |\n";

	if(b.columns[1].size()>1) cout<<"| "<<b.columns[1].getTop().getValue()<<b.columns[1].getTop().getSuit()<<" ";
	else cout<<"|    ";
	if(b.columns[2].size()>1) cout<<"| "<<b.columns[2].getTop().getValue()<<b.columns[2].getTop().getSuit()<<" ";
	else cout<<"|    ";
	if(b.columns[3].size()>1) cout<<"| "<<b.columns[3].getTop().getValue()<<b.columns[3].getTop().getSuit()<<" |\n";
	else cout<<"|    |\n";

	cout<<"4----+----5----+\n";

	if(b.columns[4].size()>1) cout<<"| "<<b.columns[4].getBottom().getValue()<<b.columns[4].getBottom().getSuit()<<" ";
	else cout<<"|    ";
	cout<<"| ]< ";
	if(b.columns[5].size()>1) cout<<"| "<<b.columns[5].getBottom().getValue()<<b.columns[5].getBottom().getSuit()<<" |\n";
	else cout<<"|    |\n";

	if(b.columns[4].size()==1) cout<<"| "<<b.columns[4].getBottom().getValue()<<b.columns[4].getBottom().getSuit()<<" ";
	else cout<<"| // ";
	cout<<"|() T";
	if(b.columns[5].size()>1) cout<<"| "<<b.columns[5].getBottom().getValue()<<b.columns[5].getBottom().getSuit()<<" |\n";
	else cout<<"| // |\n";

	if(b.columns[4].size()>1) cout<<"| "<<b.columns[4].getBottom().getValue()<<b.columns[4].getBottom().getSuit()<<" ";
	else cout<<"|    ";
	cout<<"| 'C ";
	if(b.columns[5].size()>1) cout<<"| "<<b.columns[5].getBottom().getValue()<<b.columns[5].getBottom().getSuit()<<" |\n";
	else cout<<"|    |\n";

	cout<<"6----7----8----+\n";

	if(b.columns[6].size()>1) cout<<"| "<<b.columns[6].getBottom().getValue()<<b.columns[6].getBottom().getSuit()<<" ";
	else cout<<"|    ";
	if(b.columns[7].size()>1) cout<<"| "<<b.columns[7].getBottom().getValue()<<b.columns[7].getBottom().getSuit()<<" ";
	else cout<<"|    ";
	if(b.columns[8].size()>1) cout<<"| "<<b.columns[8].getBottom().getValue()<<b.columns[8].getBottom().getSuit()<<" |\n";
	else cout<<"|    |\n";

	if(b.columns[6].size()==1) cout<<"| "<<b.columns[6].getTop().getValue()<<b.columns[6].getTop().getSuit()<<" ";
	else cout<<"| // ";
	if(b.columns[7].size()==1) cout<<"| "<<b.columns[7].getTop().getValue()<<b.columns[7].getTop().getSuit()<<" ";
	else cout<<"| // ";
	if(b.columns[8].size()==1) cout<<"| "<<b.columns[8].getTop().getValue()<<b.columns[8].getTop().getSuit()<<" |\n";
	else cout<<"| // |\n";

	if(b.columns[6].size()>1) cout<<"| "<<b.columns[6].getTop().getValue()<<b.columns[6].getTop().getSuit()<<" ";
	else cout<<"|    ";
	if(b.columns[7].size()>1) cout<<"| "<<b.columns[7].getTop().getValue()<<b.columns[7].getTop().getSuit()<<" ";
	else cout<<"|    ";
	if(b.columns[8].size()>1) cout<<"| "<<b.columns[8].getTop().getValue()<<b.columns[8].getTop().getSuit()<<" |\n";
	else cout<<"|    |\n";

	cout<<"+----+----+----+\n";
}

void reportWinner(int winner){
	cout<<"Player"<<winner<<"is the winner!!!";
}

void displayRules(){
	cout<<"PUT RULES HERE\n";
}



class Player{
	public:
		Player();
		void showHand();
		void place(Card crd, Column &clmn); // places a card on a column
		void place(Column &clmn1, Column &clmn2); // places column2 on column1
		void endTurn();//ends player's turn
		//void spy(player spiedOn);//spy on other players' hands?
		void draw(Column deck);
		bool pass; //maybe make this private? Must be initialized to 0 in constructor
		vector<Card> hand;
	private:
};

Player::Player() {
	pass = false;
}

void Player::showHand() // start of showHand function
{
	
	for (int i=0; i<hand.size(); i++)
		cout<<hand.at(i).getValue()<<" of "<<hand.at(i).getSuit()<<endl;
}

void Player::place(Card crd, Column &clmn)
{
	int i=0;
	for (i; i<hand.size(); i++)
	{
		if ((hand.at(i).getSuit() == crd.getSuit()) && (hand.at(i).getValue() == crd.getValue())) // if a card in the hand == crd
			break;
	}

	clmn.addCard(hand.at(i)); // adds card to column from hand
	hand.erase(hand.begin() + i); // removes element from hand at position i
}

void Player::place(Column &clmn1, Column &clmn2)
{
	for (int i=0; i<clmn2.size(); i++)
		clmn1.addCard(clmn2.getCard(i));

	clmn2.clear();
}

void Player::endTurn()
{
	pass = true;
}

void Player::draw(Column deck)
{
	Card drawn = deck.getTop();
	hand.push_back(drawn);
	deck.removeCard(drawn);
}


class aiPlayer: public Player{
public:
	//void takeTurn(); //try and eventually implement this
	bool validLocation[8];
	void actionsLoop(Board b);
	void findValidLocations(Card source, Board b);
	bool victory();
	bool takeTurn(Board b);
private:
};

void aiPlayer::actionsLoop(Board b){

	draw(b.deck);//draw
	cout<<"Computer player drew a card.\n";

	for(int i=0; i<8; i++){//find valid column moves
		findValidLocations(b.columns[i].getBottom(),b);
		for(int j=0;j<8;j++){
			if(validLocation[j]){
				place(b.columns[i],b.columns[j]);
				cout<<"Computer player moved\n";//<<cardname\n
				validLocation[j]=0;
				i=0;
				break;
			}
		}
			for(int k=0; k<hand.size(); k++){//find valid card moves
				findValidLocations(hand.at(k),b);
				for(int l=0;l<8;l++){
					if(validLocation[l]){
						place(hand[k],b.columns[k]);
						hand.erase(hand.begin()+k);//what is this error??
						cout<<"Computer player played a\n";//<<cardname\n
						i=0;
						k=0;
						break;
					}
				}
			}
	}
}

void aiPlayer::findValidLocations(Card source, Board b){
	for(int i=0;i<8;i++){
		validLocation[i]=0;
		if(isValidMove(source,b.columns[i])){
			validLocation[i]=1;
		}
	}
}

bool aiPlayer::victory(){
	return(hand.size()==0);
}

bool aiPlayer::takeTurn(Board b){
	actionsLoop(b);
	return(victory());
}



class realPlayer: public Player{
public:
	//void takeTurn(); //try and eventually implement this
	void actionsLoop(Board b);
	int displayMenu();
	int chooseFromCardsInHand();
	int chooseLocation();
private:
};

int realPlayer::chooseFromCardsInHand()
{
	int chosenCard = 0;
	showHand();
	cout << "pick a card from the ones in your hand, 1-"<< hand.size() << endl;
	cin >> chosenCard;
	return chosenCard-1;
}

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


void realPlayer::actionsLoop(Board b){
	drawBoard(b);
	cout<<"It's your turn.\n";
	int choice=displayMenu();
	int dest=0;
	int sourceCol=0;
	Card source;

	while(choice!=5){

		switch(choice){
		case 1:
			source=hand[chooseFromCardsInHand()];//menu
			dest=chooseLocation();//menu
			if(isValidMove(source, b.columns[dest])){
				place(source,b.columns[dest]);
			}
			else{
				cout<<"Sorry, not a valid move.\n";
			}
			break;

		case 2:
			cout<<"Choose first location.\n";
			sourceCol=chooseLocation();
			cout<<"Choose second location.\n";
			dest=chooseLocation();
			if(isValidMove(b.columns[sourceCol], b.columns[dest])){
				place(source,b.columns[dest]);
			}
			else{
				cout<<"Sorry, not a valid move.\n";
			}
			break;

		case 3:
			showHand();
			break;

		case 4:
			drawBoard(b);
			break;
		}
		choice=displayMenu();
	}
}


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

		return choice;
}

int mainMenu(){
	cout<<"Welcome to KINGS IN CORNERS\nan ESCAPE POD 4 production\n\n";

	int input=0;
	do{
	cout<<"What would you like to do?\n";
	cout<<"  -1) Start a game\n";
	cout<<"  -2) Display the rules\n";
	cout<<"  -3) Quit\n";
	cin>>input;
	if(input<1||input>3) cout<<"\nPlease enter a valid value in range 1 through 3";
	}while(input<1||input>3);
	return input;
}

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

/*int gameLoop(){   //game loop ideas
	switch (realPlayers){
	case 1:
		realPlayer p1;
		aiPlayer p2, p3, p4;
		break;
	case 2:
		realPlayer p1, p2;
		aiPlayer p3, p4;
		break;
	case 3:
		realPlayer p1, p2, p3;
		aiPlayer p4;
		break;
	case 4:
		realPlayer p1, p2, p3, p4;
		break;
	}

	int victory=0;
	while(!victory){
				//player 1 turn
		int playerChoice = turnMenu();
			
			switch (playerChoice) {
			case 1:
					//create and then drawCard() in player class
			case 2:
					int card = 0;
					int location = 0;
					cout << "enter the card and the place to move it to: card column" << endl;
					cin>>card;
					cin>>location;
					//call place(card,location) in player class
			case 3:
					int column1;
					int column2;
					cout << "enter the column's location and the columns new location, column column" << endl;
					cin>>column1;
					cin>>column2;
					//call moveColumn(column1, column2) in player class
			case 4:
					//call showhand() function in player class
			case 5:
					//not sure how to flash the board
			case 6:
					//break
	}
	return victory; //eventually, return winner's name
	
	}
	
}*/


int main()
{
	srand(time(0));
	Board b;
	realPlayer human; //constructors?
	aiPlayer ai;

	int mode=0;
	while(mode!=3){
		mode=mainMenu();
		system("cls");
		switch (mode){
		case 1:
			while(true){
				human.actionsLoop(b);
				ai.actionsLoop(b);
			}
		case 2:
			displayRules();
			system("pause");
			system("cls");
		}
	}
	return 0;
}
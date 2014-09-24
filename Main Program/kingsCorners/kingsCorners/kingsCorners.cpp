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


/*
class Player {
public:
	void showHand();
	void place(Card crd, Column clmn); // places a card on a column
	void place(Column clmn1, Column clmn2); // places a column on another column
private:
	vector<Card> hand; // we don't really need this
};


void Player::showHand() // start of showHand function
{
	for (size_t i=0; i<hand.size(); i++) {
		cout<< hand.at(i).getValue() << " of " << hand.at(i).getSuit() << endl;
	}
}

void Player::place(Card crd, Column clmn) {

}

void Player::place(Column clmn1, Column clmn2) {

}
*/


bool areDifferentColors(Card c1, Card c2){
	return 0;// this needs to be written
}

bool isValidMove(Card source, Card dest){
	if ((dest.getValue()-source.getValue()==1)&&(areDifferentColors(source,dest))){
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

void drawBoard(Column c1, Column c2, Column c3, Column c4, Column c5, Column c6, Column c7, Column c8){
	cout<<"1----2----3----+";

	if(c1.size()>1) cout<<"| "<<c1.getBottom().getValue()<<c1.getBottom().getSuit()<<" ";
	else cout<<"|    ";
	if(c2.size()>1) cout<<"| "<<c2.getBottom().getValue()<<c2.getBottom().getSuit()<<" ";
	else cout<<"|    ";
	if(c3.size()>1) cout<<"| "<<c3.getBottom().getValue()<<c3.getBottom().getSuit()<<" |";
	else cout<<"|    ";

	if(c1.size()==1) cout<<"| "<<c1.getTop().getValue()<<c1.getTop().getSuit()<<" ";
	else cout<<"| // ";
	if(c2.size()==1) cout<<"| "<<c2.getTop().getValue()<<c2.getTop().getSuit()<<" ";
	else cout<<"| // ";
	if(c3.size()==1) cout<<"| "<<c3.getTop().getValue()<<c3.getTop().getSuit()<<" |";
	else cout<<"| // ";

	if(c1.size()>1) cout<<"| "<<c1.getTop().getValue()<<c1.getTop().getSuit()<<" ";
	else cout<<"|    ";
	if(c2.size()>1) cout<<"| "<<c2.getTop().getValue()<<c2.getTop().getSuit()<<" ";
	else cout<<"|    ";
	if(c3.size()>1) cout<<"| "<<c3.getTop().getValue()<<c3.getTop().getSuit()<<" |";
	else cout<<"|    ";

	cout<<"4----5----6----+";

	if(c4.size()>1) cout<<"| "<<c4.getBottom().getValue()<<c4.getBottom().getSuit()<<" ";
	else cout<<"|    ";
	cout<<"| ]< |";
	if(c5.size()>1) cout<<"| "<<c5.getBottom().getValue()<<c5.getBottom().getSuit()<<" ";
	else cout<<"|    ";

	if(c4.size()>1) cout<<"| "<<c4.getBottom().getValue()<<c4.getBottom().getSuit()<<" ";
	else cout<<"|    ";
	cout<<"|() T|";
	if(c5.size()>1) cout<<"| "<<c5.getBottom().getValue()<<c5.getBottom().getSuit()<<" ";
	else cout<<"|    ";

	if(c4.size()>1) cout<<"| "<<c4.getBottom().getValue()<<c4.getBottom().getSuit()<<" ";
	else cout<<"|    ";
	cout<<"| 'C |";
	if(c5.size()>1) cout<<"| "<<c5.getBottom().getValue()<<c5.getBottom().getSuit()<<" ";
	else cout<<"|    ";

	cout<<"7----8----9----+";

	if(c6.size()>1) cout<<"| "<<c6.getBottom().getValue()<<c6.getBottom().getSuit()<<" ";
	else cout<<"|    ";
	if(c7.size()>1) cout<<"| "<<c7.getBottom().getValue()<<c7.getBottom().getSuit()<<" ";
	else cout<<"|    ";
	if(c8.size()>1) cout<<"| "<<c8.getBottom().getValue()<<c8.getBottom().getSuit()<<" |";
	else cout<<"|    ";

	if(c6.size()==1) cout<<"| "<<c6.getTop().getValue()<<c6.getTop().getSuit()<<" ";
	else cout<<"| // ";
	if(c7.size()==1) cout<<"| "<<c7.getTop().getValue()<<c7.getTop().getSuit()<<" ";
	else cout<<"| // ";
	if(c8.size()==1) cout<<"| "<<c8.getTop().getValue()<<c8.getTop().getSuit()<<" |";
	else cout<<"| // ";

	if(c6.size()>1) cout<<"| "<<c6.getTop().getValue()<<c6.getTop().getSuit()<<" ";
	else cout<<"|    ";
	if(c7.size()>1) cout<<"| "<<c7.getTop().getValue()<<c7.getTop().getSuit()<<" ";
	else cout<<"|    ";
	if(c8.size()>1) cout<<"| "<<c8.getTop().getValue()<<c8.getTop().getSuit()<<" |";
	else cout<<"|    ";

	cout<<"+----+----+----+";
}

void reportWinner(int winner){
	cout<<"Player"<<winner<<"is the winner!!!";
}

void displayRules(){
	cout<<"PUT RULES HERE\n";
}



class Player{
public:
	void showHand();
	void place(Card crd, Column clmn); // places a card on a column
	void place(Column clmn1, Column clmn2); // places column2 on column1
	void endTurn();//ends player's turn
	//void spy(player spiedOn);//spy on other players' hands?
	void draw(Column deck);
	bool pass; //maybe make this private? Must be initialized to 0 in constructor
private:
	vector<Card> hand; 
};

void Player::showHand() // start of showHand function
{
	
	for (int i=0; i<hand.size(); i++)
		cout<<hand.at(i).getValue()<<" of "<<hand.at(i).getSuit()<<endl;
}

void Player::place(Card crd, Column clmn)
{
	clmn.addCard(crd);
}

void Player::place(Column clmn1, Column clmn2)
{
	for (int i=0; clmn2.size();i++)
	{
		clmn1.addCard(clmn2.getCard(i)); 
	}
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
	void actionsLoop();
private:
};

void aiPlayer::actionsLoop(){
}


class realPlayer: public Player{
public:
	void actionsLoop();
	int displayMenu();
private:
};

void realPlayer::actionsLoop(){
	int choice=displayMenu();
	while(choice!=3){
		if(choice==1){
			Card source=chooseFromCardsInHand();//menu
			Card dest=chooseLocation();//menu
			if(isValidMove(source, dest)){
				
			}
		else{

			}
		}
	}
}

int realPlayer::displayMenu(){
	int choice=0;
		cout<<"What would you like to do?\n";
		cout<<"  -1) play a card from your hand\n";
		cout<<"  -2) move a column\n";
		cout<<"  -3) pass";

		while(choice<1||choice>3){
			cin>>choice;
			if(choice<1||choice>3) cout<<"Sorry, please enter a valid integer in range 1-3";
		}

		return choice;
}

int main()
{
	srand(time(0));

	int mode=0;
	while(mode!=3){
		mode=mainMenu();
		system("cls");

		switch (mode){
		case 1:
			int players=playerCount;
			int victory=gameLoop(players);
			system("cls");
			reportWinner(victory);
			break;
		case 2:
			displayRules();
			break;
		}
	
	return 0;
	}
}

//game loop ideas
/*
int gameLoop(int realPlayers){
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
		p1.actionsLoop();
		p2.actionsLoop();
		p3.actionsLoop();
		p4.actionsLoop();
	}
	return victory; //eventually, return winner's name
	
}
*\
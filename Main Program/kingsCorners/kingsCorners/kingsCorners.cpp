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
	cards.clear;
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

class Player{
public:
	void showHand();
	void place(Card crd, Column clmn); // places a card on a column
	void place(Column clmn1, Column clmn2); // places column2 on column1
	void endTurn();//ends player's turn
	//void spy(player spiedOn);//spy on other players' hands?
	void draw();
	bool pass = 0; //maybe make this private?
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
		clmn1.addCard(clmn2.at(i));  
	}
}

void Player::endTurn()
{
	pass = true;
}

void Player::draw()
{
	Card drawn = deck.getTop()
	hand.pushBack() = drawn;
	deck.removeCard(drawn);
}

int playerCount(){
	int count=0;
	do{
		cout<<"How many human players want to play (1-4)?\n";
		cin>>count;
	} while (count<=1&&count>=4);
	return count;
}

void reportWinner(int winner){
	cout<<"Player"<<winner<<"is the winner!!!";
}

void displayRules(){
	//display the rules
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
			int players=playerCount();
			victory=gameLoop(players);
			system("cls");
			reportWinner(victory);
			break;
		case 2:
			displayRules();
			break;
	}
	
	return 0;
}


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
	int playerChoice = 0;
	while(!victory){
		//player 1 turn
		for (int i = 1; i <= realPlayers, i++)
		{
			cout << "player " << i << "it is your turn, what would you like to do?" << endl;
			cout << "1. draw card" << endl <<
					"2. place card" << endl <<
					"3. move column" << endl <<
					"4. show hand" << endl <<
					"5. show board" << endl <<
					"6. end turn" << endl;

			switch (playerChoice) {
				case 1
					//create and then drawCard() in player class
				case 2
					int card = 0;
					int location = 0;
					cout << "enter the card and the place to move it to: card column" << endl;
					cin>>card;
					cin>>location;
					//call place(card,location) in player class
				case 3
					int column1;
					int column2;
					cout << "enter the column's location and the columns new location, column column" << endl;
					cin>>column1;
					cin>>column2;
					//call moveColumn(column1, column2) in player class
				case 4
					//call showhand() function in player class
				case 5
					//not sure how to flash the board
				case 6
					//break
		}
		//take player turns
		//on win, set victory to number of victorious player
	}
	return victory; //eventually, return winner's name
	
}





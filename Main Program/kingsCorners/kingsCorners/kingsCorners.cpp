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


int main()
{
	//srand(time(0));
	Player p;
	p.showHand();
	return 0;
}

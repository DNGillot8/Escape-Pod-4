/*
Authors: Wesley Toney, John Umble, Nick Gillot, James Leach
Course: COMP 220
Date: 9/25/2014
Description: This file contains the column class for our implementation
of the card game  "Kings on the Corners".
*/

//init
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

//Constructor which makes a new column based on a vector
Column::Column(vector<Card> c) {
	cards = c;
}

//Default constructor
Column::Column() {
	vector<Card> c;
	cards = c;
}

//Adds a card to a column
void Column::addCard(Card c) {
	cards.push_back(c);
}

//Removes a card from a column
void Column::removeCard(Card c) {
	for(int i=0;i<cards.size();i++){
		if(cards.at(i).name()==c.name())
			cards.erase(cards.begin()+i);
	}
}

//Returns card at a certain location in a column
Card Column::getCard(int i) const {
	return cards.at(i);
}

//Returns top card in the column
Card Column::getTop() const {
	return cards.at(0);
}

//Returns bottom card in the column
Card Column::getBottom() const {
	return cards.at(cards.size() - 1);
}

//Removes all cards in the column
void Column::clear() {
	cards.clear();
}

//Shuffles the column
void Column::shuffle() {
	random_shuffle(cards.begin(), cards.end());
}

//Returns size of column's cards vector
int Column::size() const {
	return cards.size();
}
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

using std::cout;
using std::endl;
using std::cin;
using std::ios;
using std::string;
using std::vector;
using std::random_shuffle;
using std::rand;
using std::srand;

//the Column class- contains numerous card-based functions in a convenient wrapper around a vector
class Column {
public:
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
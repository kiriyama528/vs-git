
#include <iostream>
#include <string>
#include <vector>

#include <algorithm>

#include "Card.h"
#include "Deck.h"
#include "CardList.h"



Deck::Deck() {
	// do nothing
}


Deck::Deck(const vector<Card*> _cards_shadow) {
	load(_cards_shadow);
}

Deck::Deck(CardList &cl) {
	load(cl.shadow());
}

Deck::~Deck() {
	cards_shadow.clear();
}

int Deck::load(const vector<Card*> _cards_shadow) {
	copy(_cards_shadow.begin(), _cards_shadow.end(), back_inserter(cards_shadow));

	return cards_shadow.size();
}

Card* Deck::draw() {
	if (cards_shadow.empty()) return NULL;

	// �R�D�́�(Top) �� vector��[0]
	Card *c = cards_shadow[0];
	cards_shadow.erase(cards_shadow.begin());

	return c;
}

int Deck::shuffle() {
	random_shuffle(cards_shadow.begin(), cards_shadow.end());

	return cards_shadow.size();
}

int Deck::putTop(Card *c) {
	cards_shadow.insert(cards_shadow.begin(), c);

	return cards_shadow.size();
}

int Deck::putBottom(Card *c) {
	cards_shadow.push_back(c);

	return cards_shadow.size();
}

int Deck::searchIdx(string _name) {
	for (int i = 0; i < cards_shadow.size(); i++) {
		if (_name == cards_shadow[i]->get_name()) {
			return i;
		}
	}
	return -1;
}

Card* Deck::searchDraw(string _name) {
	for (int i = 0; i < cards_shadow.size(); i++) {
		if (_name == cards_shadow[i]->get_name()) {
			Card *c = cards_shadow[i];
			cards_shadow.erase(cards_shadow.begin() + i);
			return c;
		}
	}
	return NULL;
}



#include <iostream>
#include <string>
#include <vector>

#include "Card.h"
#include "CardList.h"




CardList::CARD_CLASS CardList::cardClassBranch(const char* str) {
	if (strcmp(str, "Card") == 0) {
		return CARD;
	}
	else if (strcmp(str, "Rivals") == 0) {
		return RIVALS;
	}
	else {
		return UNKNOWN;
	}
}

CardList::CardList() {
	// do nothing
}


CardList::CardList(string filename) {
	load(filename);
}

CardList::~CardList() {
	// �����Fvector<Card> cards
	for (unsigned int i = 0; i < cards.size(); i++) {
		delete cards[i]; // ���Ԃ̍폜
	}
	cards.clear(); // �|�C���^vector�̏�����
}


// #class Card    <- �ǂݍ��� class�B�w�b�_�[�͐擪��#
// card_name1,ability1,img_name1
// card_name2,ability2,img_name2
// card_name3,ability3,img_name3

bool CardList::load(string filename) {
#define BUFFER_SIZE 2048
	ifstream ifs(filename);

	// �t�@�C���`�F�b�N
	if (ifs.fail()) {
		fprintf(stderr, " Error > �J�[�h���X�g�t�@�C�����ǂݍ��߂܂���\n"
			"          filename : %s\n", filename.c_str());
		return false;
	}

	char buffer[BUFFER_SIZE];
	CARD_CLASS card_class;
	while (ifs.getline(buffer, BUFFER_SIZE)) {
		// �w�b�_�[����
		if (buffer[0] == '#') {
			if (strstr(buffer, "#class")) {
				card_class = cardClassBranch(&buffer[7]);
			}
			continue;
		}

		// �J�[�h�ǂݍ��ݏ���
		switch (card_class) {
		case CARD:
			cards.emplace_back(new Card(buffer));
			break;
		case RIVALS:
			// �� �܂�Rivals�N���X�͍���ĂȂ��̂ŃR�����g�A�E�g
			// cards.emplace_back(new Rivals(buffer));
			break;
		default:
			fprintf(stderr, " ERROR : �J�[�h���X�g�t�@�C���œǂݍ��݃J�[�h�N���X���w�肳��Ă��܂���\n");
			break;
		}
	}

	ifs.close(); // fix me ? �����������炢��Ȃ�����

	return true;
}


const vector<Card*> CardList::shadow() {
	return cards;
}
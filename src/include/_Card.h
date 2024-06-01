#pragma once
#include <iostream>
//�޶�������
//����ö�ٲ�Ӧ����.h�У����ǽṹ��Ҫ������д������
//ö�����Ͳ�֧��ǰ������
enum class Suit {
	HEARTS, DIAMONDS, CLUBS, SPADES
};

enum class Rank {
	TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,\
	JACK, QUEEN, KING, ACE
};

struct Card {
	Suit suit;
	Rank rank;
	Card(Suit s, Rank r);
	Card(const Card& c);
	~Card();

};
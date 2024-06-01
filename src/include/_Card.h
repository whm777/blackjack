#pragma once
#include <iostream>
//限定作用域
//正常枚举不应该在.h中，但是结构体要用所以写道这里
//枚举类型不支持前向声明
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
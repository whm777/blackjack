#pragma once
#include<iostream>
#include <string>
#include <vector>
#include"Card.h"
#include<algorithm>
#include<map>
#include "Player.h"

/*
游戏规则类：用于设定有游戏边界，用于判断是否合法，
1.游戏玩家数量，
2.玩家的下注是否合法，
3.比较牌型大小
*/

// 定义牌型的优先级
enum class PokerHand {
	ROYAL_FLUSH,
	STRAIGHT_FLUSH,
	FOUR_OF_A_KIND,
	FULL_HOUSE,
	FLUSH,
	STRAIGHT,
	THREE_OF_A_KIND,
	TWO_PAIR,
	ONE_PAIR,
	HIGH_CARD
};


class GameRule
{
public:
	//对比两个玩家手牌 
	static int32_t compareHands(std::vector<Player>& players);
	//bool checkBetting();
	static PokerHand getMaxPokerHand(const std::vector<Card>& hand);
private:
	static bool isRoyalFlush(const std::vector<Card>& hand);  //皇家同花顺
	static bool isStraightFlush(const std::vector<Card>& hand);//同花顺
	static bool isFourKind(const std::vector<Card>& hand);		//四条
	static bool isFullHouse(const std::vector<Card>& hand);		//葫芦
	static bool isFlush(const std::vector<Card>& hand);			//同花
	static bool isStraight(const std::vector<Card>& hand);		//顺子
	static bool isThreeKind(const std::vector<Card>& hand);		//三条
	static bool isTowPair(const std::vector<Card>& hand);		//两对
	static bool isOnePair(const std::vector<Card>& hand);		//一对
	static Rank getHighCard(const std::vector<Card>& hand);		//高牌

};


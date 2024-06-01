#pragma once
#include<iostream>
#include <string>
#include <vector>
#include"Card.h"
#include<algorithm>
#include<map>
#include "Player.h"

/*
��Ϸ�����ࣺ�����趨����Ϸ�߽磬�����ж��Ƿ�Ϸ���
1.��Ϸ���������
2.��ҵ���ע�Ƿ�Ϸ���
3.�Ƚ����ʹ�С
*/

// �������͵����ȼ�
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
	//�Ա������������ 
	static int32_t compareHands(std::vector<Player>& players);
	//bool checkBetting();
	static PokerHand getMaxPokerHand(const std::vector<Card>& hand);
private:
	static bool isRoyalFlush(const std::vector<Card>& hand);  //�ʼ�ͬ��˳
	static bool isStraightFlush(const std::vector<Card>& hand);//ͬ��˳
	static bool isFourKind(const std::vector<Card>& hand);		//����
	static bool isFullHouse(const std::vector<Card>& hand);		//��«
	static bool isFlush(const std::vector<Card>& hand);			//ͬ��
	static bool isStraight(const std::vector<Card>& hand);		//˳��
	static bool isThreeKind(const std::vector<Card>& hand);		//����
	static bool isTowPair(const std::vector<Card>& hand);		//����
	static bool isOnePair(const std::vector<Card>& hand);		//һ��
	static Rank getHighCard(const std::vector<Card>& hand);		//����

};


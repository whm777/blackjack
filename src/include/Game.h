#pragma once
#include <iostream>
#include <vector>
#include "PokerTable.h"
#include "GameRule.h"
#include "Player.h"


/*
��Ϸ�����ࣺ��Ϸ��������̣�������Ϸ�����׶εĵ��ȣ�
1.������Ϸ��Һ�������
2.������Ϸ�׶ν��
3.�ٴ�����Һ������������Ϸ����ִ�е�ǰ�׶Σ�
4.�׶ν���������ⲿ��Ϸ���--˭Ӯ˭��
*/


class Game
{
private:
	bool isFirshGame;	//�Ƿ��ǵ�һ����Ϸ
	const int32_t licensingStageCardNUM = 2;
	const int32_t flippingStageCardNUM = 3;
	const int32_t transferStageCardNUM = 1;
public:
	Game();
	~Game();

	void initialStage(std::vector<Player>& players, bool isFirstGame);	//��ʼ�׶�
	void licensingStage(PokerTable& pt, std::vector<Player>& players);	//���ƽ׶�
	int32_t bettingStage(std::vector<Player>& players, int big_blind_index, int& current_bet, int big_blind_bet, int small_blind_bet);	//��ע�׶�
	void flippingStage(PokerTable& pt, std::vector<Player>& players);	//���ƽ׶�
	int32_t bettingStageagain(std::vector<Player>& players, int& current_bet);	//�ٴ���ע�׶�
	void transferStage(PokerTable& pt, std::vector<Player>& players);	//ת�ƽ׶�
	void rivercardStage(PokerTable& pt, std::vector<Player>& players);	//���ƽ׶�
	int32_t comparisonStage();	//���ƽ׶�
};


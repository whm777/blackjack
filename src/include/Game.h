#pragma once
#include <iostream>
#include <vector>
#include "PokerTable.h"
#include "GameRule.h"
#include "Player.h"


/*
游戏过程类：游戏的主体过程，负责游戏各个阶段的调度，
1.传入游戏玩家和牌桌，
2.传出游戏阶段结果
3.再传入玩家和牌桌后调用游戏规则执行当前阶段，
4.阶段结束后告诉外部游戏结果--谁赢谁输
*/


class Game
{
private:
	bool isFirshGame;	//是否是第一次游戏
	const int32_t licensingStageCardNUM = 2;
	const int32_t flippingStageCardNUM = 3;
	const int32_t transferStageCardNUM = 1;
public:
	Game();
	~Game();

	void initialStage(std::vector<Player>& players, bool isFirstGame);	//起始阶段
	void licensingStage(PokerTable& pt, std::vector<Player>& players);	//发牌阶段
	int32_t bettingStage(std::vector<Player>& players, int big_blind_index, int& current_bet, int big_blind_bet, int small_blind_bet);	//下注阶段
	void flippingStage(PokerTable& pt, std::vector<Player>& players);	//翻牌阶段
	int32_t bettingStageagain(std::vector<Player>& players, int& current_bet);	//再次下注阶段
	void transferStage(PokerTable& pt, std::vector<Player>& players);	//转牌阶段
	void rivercardStage(PokerTable& pt, std::vector<Player>& players);	//河牌阶段
	int32_t comparisonStage();	//比牌阶段
};


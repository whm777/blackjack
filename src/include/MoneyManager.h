#pragma once

#if 0
/*
资金管理类，把资金由这个类的对象管理，
TODO:之后再写吧，
*/
#include "Player.h"
#include <fstream>
#include <sstream>

class MoneyManager
{
public:
	MoneyManager(const std::vector<int>& initial_bet);
	~MoneyManager();
	
	void placeMoney(int32_t player_id, int32_t betMoney);
	void collectBet(int32_t player_id, int32_t betMoney);
	void printBet() const;
private:
	std::vector<Player> players;
	const std::string filename = "chip_data.txt";	//保存筹码数据的文件
	
	void loadChipsFromFile();	//从文件加载筹码数据
	void saveChipsToFile();		//保存筹码数据到文件
};

#endif
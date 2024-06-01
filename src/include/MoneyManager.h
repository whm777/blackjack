#pragma once

#if 0
/*
�ʽ�����࣬���ʽ��������Ķ������
TODO:֮����д�ɣ�
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
	const std::string filename = "chip_data.txt";	//����������ݵ��ļ�
	
	void loadChipsFromFile();	//���ļ����س�������
	void saveChipsToFile();		//����������ݵ��ļ�
};

#endif
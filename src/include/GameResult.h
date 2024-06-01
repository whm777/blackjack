#pragma once
#include <iostream>
#include <time.h>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>


class GameResult
{
private:
	time_t gametime;
	bool gameresult;
	int32_t money_change;
public:
	GameResult();
	GameResult(const GameResult& gr);
	~GameResult();

	time_t getgametime();
	std::string getgametime(time_t gt);
	bool getgameresult();
	int32_t getmoney_change();

	int setgametime();
	void setgameresult(bool gr);
	int32_t setmoney_change(int32_t mc);
};


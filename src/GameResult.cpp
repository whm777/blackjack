#include "GameResult.h"
GameResult::GameResult()
{}

GameResult::GameResult(const GameResult& gr)
{}

GameResult::~GameResult()
{}

time_t GameResult::getgametime()
{
	return this->gametime;  //返回时间戳
}

std::string GameResult::getgametime(time_t gt)
{
	std::tm* timeinfo = std::localtime(&gt); // 转换为本地时间
	std::ostringstream oss;
	oss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S"); // 格式化时间
	return oss.str(); // 返回格式化后的时间字符串
}

bool GameResult::getgameresult()
{
	return this->gameresult;
}

int32_t GameResult::getmoney_change()
{
	return this->money_change;
}

int GameResult::setgametime()
{
	this->gametime = std::time(nullptr);
}

void GameResult::setgameresult(bool gr)
{
	this->gameresult = gr;
}
int32_t GameResult::setmoney_change(int32_t mc)
{
	this->money_change = mc;
}
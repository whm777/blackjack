#include "GameResult.h"
GameResult::GameResult()
{}

GameResult::GameResult(const GameResult& gr)
{}

GameResult::~GameResult()
{}

time_t GameResult::getgametime()
{
	return this->gametime;  //����ʱ���
}

std::string GameResult::getgametime(time_t gt)
{
	std::tm* timeinfo = std::localtime(&gt); // ת��Ϊ����ʱ��
	std::ostringstream oss;
	oss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S"); // ��ʽ��ʱ��
	return oss.str(); // ���ظ�ʽ�����ʱ���ַ���
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
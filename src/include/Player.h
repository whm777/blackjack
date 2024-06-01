#pragma once
#include "People.h"
#include "GameResult.h"
#include "Card.h"
#include "Money.h"
#include <vector>
#include <string>

enum class PlayerRole {
	SMALL_BLIND,	//小盲注
	BIG_BLIND,		//大盲注
	DEALER,			//庄家
	PLAYER			//普通玩家
};

class Player:private People
{
private:
	uint32_t id;	//用户id
	GameResult gr;//游戏结果
	Money m;//资金
	uint32_t bet; //兑换筹码--资金交给金钱管理类处理
	bool folded;	//是否放弃
	bool GOD;//作弊模式
	PlayerRole prole;	//玩家角色

	std::vector<Card> playercard;//手牌
	std::string rool;

	int32_t cleangr();//游戏结束后清除上一次游戏结果，在获得手牌前调用

public:
	Player(const std::string name, const uint32_t moneystart);
	~Player();

	int32_t setpalyercard(Card pc);//获得手牌
	void setGOD();//设置作弊模式
	//int setplayername(string name);
	void setgameresult(GameResult gr);//设置游戏结果
	void setfolded(bool sf);	//设置是否放弃
	void setprole(PlayerRole pr);	//设置玩家角色

	std::vector<Card> getplayercard();//查看手牌
	bool getGOD();//查看是否开启作弊模式
	std::string getplayername();//查看用户名
	GameResult getgameresult();//查看游戏结果
	bool getfolded();	//获取用户是否放弃
	uint32_t getplayerid();	//获取玩家id
	PlayerRole getprole();		//获取玩家角色


	void setbet(uint32_t bt);	//下注
	uint32_t getplayermoneynow();	//获取当前玩家的筹码--从MoneyManager查看剩余筹码
	void cashBet();	//兑换筹码--将资金交给MonyeManager管理
	uint32_t getbet();	//获取下的赌注--从moneymanager查看本次下注的金额


	int32_t discard();//结束后弃牌
	int32_t betting(uint32_t btmoney);//下注
};


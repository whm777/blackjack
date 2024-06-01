#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<random>
#include "Card.h"
class PokerTable
{
private:
	uint32_t cardtotalenum;  //桌面总扑克数
	uint32_t decknum;		//扑克副数  TODO:只需要一副扑克
	uint32_t usedcardnum;	//打出的扑克数
	std::vector<Card> tablecard;//桌面上打出的扑克
	std::stack<Card> unusedcard;//桌面上剩余的未使用扑克
	uint32_t tablemoney;
	std::vector<Card> initcard;

	void shuffle();//洗牌
	void createallpoker();//获取扑克副数后创建扑克
	void createonepoker();//创建一副扑克
public:
	PokerTable();
	PokerTable(const PokerTable & pt);
	~PokerTable();

	int setcardtotalenum(uint32_t setcardtotalenum);  //桌面总的卡牌数
	int setdecknum(uint32_t decknum);  //设置扑克副数
	int setusedcardnum(uint32_t usedcarddnum);  //设置未使用的扑克数。

	uint32_t getcardtotalenum();	//获取桌面的卡牌数
	uint32_t getdecknum();	//获取扑克副数
	uint32_t getusedcardnum();	//获取已经打出的扑克数
	std::vector<Card> gettablecard();	//获取桌面打出卡牌
	std::stack<Card> getunusedcard();	//获取未使用的扑克
	
	void showtablecard(std::vector<Card>& showtbcard, uint32_t cardnum);	//展示桌面的牌

	Card dealingcard();   //发牌
	uint32_t betting(uint32_t money);   //桌面的赌注


};

 
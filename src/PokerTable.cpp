#include "PokerTable.h"
PokerTable::PokerTable()
{}

PokerTable::PokerTable(const PokerTable& pt)
{}

PokerTable::~PokerTable()
{}

//桌面总的卡牌数
int PokerTable::setcardtotalenum(uint32_t setcardtotalenum)  
{
	if (setcardtotalenum <= 0)
	{
		return -1;
	}
	this->cardtotalenum = setcardtotalenum;
	return 0;
}


//设置扑克副数
int PokerTable::setdecknum(uint32_t decknum)
{
	if (decknum <= 0)
	{
		return -1;
	}
	this->decknum = decknum;
	return 0;
}

//设置未使用的扑克数。
int PokerTable::setusedcardnum(uint32_t usedcardnum)  
{
	if (usedcardnum <= 0)
	{
		return -1;
	}
	this->usedcardnum = usedcardnum;



	return 0;
}

//获取桌面的卡牌数
uint32_t PokerTable::getcardtotalenum()
{
	return this->cardtotalenum;
}

//获取扑克副数
uint32_t PokerTable::getdecknum()
{
	return this->decknum;
}

//获取已经打出的扑克数
uint32_t PokerTable::getusedcardnum()
{
	return this->usedcardnum;
}

//获取桌面的卡牌
std::vector<Card> PokerTable::gettablecard()
{
	return this->tablecard;
}

//获取未使用的扑克
std::stack<Card> PokerTable::getunusedcard()
{
	return this->unusedcard;
}

void PokerTable::showtablecard(std::vector<Card>& showtbcard, uint32_t cardnum)
{
	for(int i = 0; i<cardnum; ++i)
	{
		Card tmp_card = this->unusedcard.top();
		this->unusedcard.pop();
		showtbcard.push_back(tmp_card);
	}
}

//发牌,每次调用发一张牌
Card PokerTable::dealingcard()
{
	if (this->unusedcard.empty())
	{
		//LOG
		std::cout << "unusedcard is empty" << std::endl;
		//TODO
		//NEED RETURN
	}else
	{
		Card tmp_card = this->unusedcard.top();
		this->unusedcard.pop();
		return tmp_card;
	}
}

//桌面的赌注
//TODO：这里有问题，财物应该是一个单独的管理类。
uint32_t PokerTable::betting(uint32_t money)
{
	return this->tablemoney = this->tablemoney + money;
}

//洗牌
void PokerTable::shuffle()
{
	//判断是否是第一次玩牌
	if (this->cardtotalenum != this->tablecard.size())
	{
		std::cout << "不是第一次玩牌，不可以洗牌" << std::endl;
		//TODO:LOG
	}
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	std::shuffle(this->initcard.begin(), this->initcard.end(), std::default_random_engine());

	this->unusedcard = std::stack<Card>();

	while (!this->unusedcard.empty()) {
		this->unusedcard.pop();
	}
	for (auto it = this->initcard.rbegin(); it != this->initcard.rend(); ++it) {
		this->unusedcard.push(*it);
	}
}


void PokerTable::createonepoker()
{
	//这个for循环放到一个函数里更好
	for (Suit s : {Suit::CLUBS, Suit::DIAMONDS, Suit::HEARTS, Suit::SPADES})
	{
		for (Rank r : {Rank::ACE, Rank::EIGHT, Rank::FIVE, Rank::FOUR, Rank::JACK,
			Rank::KING, Rank::NINE, Rank::QUEEN, Rank::SEVEN, Rank::SIX, Rank::TEN,
			Rank::THREE, Rank::TWO})
		{
			Card c(s, r);
			this->initcard.push_back(c);
		}
	}
}


//获取扑克副数后创建扑克
void PokerTable::createallpoker()
{
	if (this->decknum <= 0)
	{
		//TODO:LOG
		std::cout << "还没有创建扑克" << std::endl;
		return;
	}
	for(int i = 1; i <= this->decknum ; i++)
	{ 
		this->createonepoker();
	}
}
#include "PokerTable.h"
PokerTable::PokerTable()
{}

PokerTable::PokerTable(const PokerTable& pt)
{}

PokerTable::~PokerTable()
{}

//�����ܵĿ�����
int PokerTable::setcardtotalenum(uint32_t setcardtotalenum)  
{
	if (setcardtotalenum <= 0)
	{
		return -1;
	}
	this->cardtotalenum = setcardtotalenum;
	return 0;
}


//�����˿˸���
int PokerTable::setdecknum(uint32_t decknum)
{
	if (decknum <= 0)
	{
		return -1;
	}
	this->decknum = decknum;
	return 0;
}

//����δʹ�õ��˿�����
int PokerTable::setusedcardnum(uint32_t usedcardnum)  
{
	if (usedcardnum <= 0)
	{
		return -1;
	}
	this->usedcardnum = usedcardnum;



	return 0;
}

//��ȡ����Ŀ�����
uint32_t PokerTable::getcardtotalenum()
{
	return this->cardtotalenum;
}

//��ȡ�˿˸���
uint32_t PokerTable::getdecknum()
{
	return this->decknum;
}

//��ȡ�Ѿ�������˿���
uint32_t PokerTable::getusedcardnum()
{
	return this->usedcardnum;
}

//��ȡ����Ŀ���
std::vector<Card> PokerTable::gettablecard()
{
	return this->tablecard;
}

//��ȡδʹ�õ��˿�
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

//����,ÿ�ε��÷�һ����
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

//����Ķ�ע
//TODO�����������⣬����Ӧ����һ�������Ĺ����ࡣ
uint32_t PokerTable::betting(uint32_t money)
{
	return this->tablemoney = this->tablemoney + money;
}

//ϴ��
void PokerTable::shuffle()
{
	//�ж��Ƿ��ǵ�һ������
	if (this->cardtotalenum != this->tablecard.size())
	{
		std::cout << "���ǵ�һ�����ƣ�������ϴ��" << std::endl;
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
	//���forѭ���ŵ�һ�����������
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


//��ȡ�˿˸����󴴽��˿�
void PokerTable::createallpoker()
{
	if (this->decknum <= 0)
	{
		//TODO:LOG
		std::cout << "��û�д����˿�" << std::endl;
		return;
	}
	for(int i = 1; i <= this->decknum ; i++)
	{ 
		this->createonepoker();
	}
}
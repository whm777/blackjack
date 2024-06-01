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
	uint32_t cardtotalenum;  //�������˿���
	uint32_t decknum;		//�˿˸���  TODO:ֻ��Ҫһ���˿�
	uint32_t usedcardnum;	//������˿���
	std::vector<Card> tablecard;//�����ϴ�����˿�
	std::stack<Card> unusedcard;//������ʣ���δʹ���˿�
	uint32_t tablemoney;
	std::vector<Card> initcard;

	void shuffle();//ϴ��
	void createallpoker();//��ȡ�˿˸����󴴽��˿�
	void createonepoker();//����һ���˿�
public:
	PokerTable();
	PokerTable(const PokerTable & pt);
	~PokerTable();

	int setcardtotalenum(uint32_t setcardtotalenum);  //�����ܵĿ�����
	int setdecknum(uint32_t decknum);  //�����˿˸���
	int setusedcardnum(uint32_t usedcarddnum);  //����δʹ�õ��˿�����

	uint32_t getcardtotalenum();	//��ȡ����Ŀ�����
	uint32_t getdecknum();	//��ȡ�˿˸���
	uint32_t getusedcardnum();	//��ȡ�Ѿ�������˿���
	std::vector<Card> gettablecard();	//��ȡ����������
	std::stack<Card> getunusedcard();	//��ȡδʹ�õ��˿�
	
	void showtablecard(std::vector<Card>& showtbcard, uint32_t cardnum);	//չʾ�������

	Card dealingcard();   //����
	uint32_t betting(uint32_t money);   //����Ķ�ע


};

 
#pragma once
#include "People.h"
#include "GameResult.h"
#include "Card.h"
#include "Money.h"
#include <vector>
#include <string>

enum class PlayerRole {
	SMALL_BLIND,	//Сäע
	BIG_BLIND,		//��äע
	DEALER,			//ׯ��
	PLAYER			//��ͨ���
};

class Player:private People
{
private:
	uint32_t id;	//�û�id
	GameResult gr;//��Ϸ���
	Money m;//�ʽ�
	uint32_t bet; //�һ�����--�ʽ𽻸���Ǯ�����ദ��
	bool folded;	//�Ƿ����
	bool GOD;//����ģʽ
	PlayerRole prole;	//��ҽ�ɫ

	std::vector<Card> playercard;//����
	std::string rool;

	int32_t cleangr();//��Ϸ�����������һ����Ϸ������ڻ������ǰ����

public:
	Player(const std::string name, const uint32_t moneystart);
	~Player();

	int32_t setpalyercard(Card pc);//�������
	void setGOD();//��������ģʽ
	//int setplayername(string name);
	void setgameresult(GameResult gr);//������Ϸ���
	void setfolded(bool sf);	//�����Ƿ����
	void setprole(PlayerRole pr);	//������ҽ�ɫ

	std::vector<Card> getplayercard();//�鿴����
	bool getGOD();//�鿴�Ƿ�������ģʽ
	std::string getplayername();//�鿴�û���
	GameResult getgameresult();//�鿴��Ϸ���
	bool getfolded();	//��ȡ�û��Ƿ����
	uint32_t getplayerid();	//��ȡ���id
	PlayerRole getprole();		//��ȡ��ҽ�ɫ


	void setbet(uint32_t bt);	//��ע
	uint32_t getplayermoneynow();	//��ȡ��ǰ��ҵĳ���--��MoneyManager�鿴ʣ�����
	void cashBet();	//�һ�����--���ʽ𽻸�MonyeManager����
	uint32_t getbet();	//��ȡ�µĶ�ע--��moneymanager�鿴������ע�Ľ��


	int32_t discard();//����������
	int32_t betting(uint32_t btmoney);//��ע
};


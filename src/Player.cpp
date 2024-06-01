#include "Player.h"
Player::Player(const std::string name , const uint32_t moneystart): People(name), m(moneystart), GOD(false)
{}

Player::~Player()
{}


int32_t Player::setpalyercard(Card pc)
{
	playercard.push_back(pc);
	return 0;
}

void Player::setGOD()
{
	if (this->GOD == false)
	{
		this->GOD = true;
	}
	else
	{
		this->GOD = false;
	}
}
void Player::setgameresult(GameResult gr)
{
	this->gr = gr;
}

std::vector<Card> Player::getplayercard()
{
	return this->playercard;
}
bool Player::getGOD()
{
	return this->GOD;
}
std::string Player::getplayername()
{
	return this->getname();
}

GameResult Player::getgameresult()
{
	return this->gr;
}

int32_t Player::discard()
{
	this->playercard.erase(this->playercard.begin(), this->playercard.end());
}
int32_t Player::betting(uint32_t btmoney)
{
	if (btmoney == 0)
		return -1;
	uint32_t moneynow = m.getmoneynow();
	if (btmoney > moneynow)
	{
		return -2;
	}
	moneynow = moneynow - btmoney;
	m.setmoneynow(moneynow);
	return 0;
	
}


void Player::setfolded(bool sf)
{
	this->folded = sf;
}

bool Player::getfolded()
{
	return this->folded;
}

uint32_t Player::getplayermoneynow()
{
	return this->m.getmoneynow();
}

uint32_t Player::getplayerid()
{
	return this->id;
}

void Player::setprole(PlayerRole pr)
{//ÉèÖÃÍæ¼Ò½ÇÉ«
	this->prole = pr;
}

PlayerRole Player::getprole()
{
	return this->prole;
}



void Player::setbet(uint32_t bt)
{
	this->bet += bt;
}

uint32_t  Player::getbet()
{
	return this->bet;
}
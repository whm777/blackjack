#include "Money.h"
Money::Money(const uint32_t& ms): money_start(ms)
{}
Money::Money(const Money& m):money_start(m.money_start)
{}
Money::~Money()
{}

uint32_t Money::getmoneystart()
{
	return this->money_start;
}
uint32_t Money::getmoneynow()
{
	return this->money_now;
}

#if 0
void Money::setmoneystart(uint32_t ms)
{
	this->money_start = ms;
}
#endif

void Money::setmoneynow(uint32_t mn)
{
	this->money_now = mn;
}
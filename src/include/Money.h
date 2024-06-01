#pragma once
#include <iostream>
class Money
{
private:
	const uint32_t money_start;
	uint32_t money_now;
public:
	Money(const uint32_t& ms);
	Money(const Money & m);
	~Money();

	uint32_t getmoneystart();
	uint32_t getmoneynow();

	void setmoneystart(uint32_t ms);
	void setmoneynow(uint32_t mn);
};


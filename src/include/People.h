#pragma once
#include <iostream>
#include <string>
struct People
{
private:
	std::string name;
public:
	People(const std::string & n);
	People(const People& p);
	~People();
	const std::string getname() const;
};


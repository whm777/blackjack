#include "People.h"
People::People(const std::string& n) : name(n)
{
}
People::People(const People& p) : name(p.name)
{}

People::~People()
{}
const std::string People::getname() const
{
	return this->name;
}
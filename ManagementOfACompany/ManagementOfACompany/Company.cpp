#include "Company.h"


Company::Company(std::string nameOfABoss)
{
	Employee b(nameOfABoss);
	boss = new Node(b);
}

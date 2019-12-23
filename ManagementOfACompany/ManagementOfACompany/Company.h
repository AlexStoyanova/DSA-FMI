#ifndef COMPANY_H
#define COMPANY_H
#include <iostream>
#include <string>
#include <vector>

class Company
{
private:
	struct Employee
	{
		std::string name;
		Employee(std::string name) : name(name) {}
	};

	struct Node
	{
		Employee empl;
		std::vector<Node*> subordinates;
		Node(Employee em) : empl(em){}
	};

private:
	void copyFrom(const Company& other);
	void clear();
	
	bool isLeaf(Node* elem);
	void addLeaf(Node* start, Node* newEmp, std::string name);
	void removeLeaf(Node* start, std::string name);
	int maxHeightFromEmployee(Node* start);
	int maxHeightForEmployeeSubord(std::vector<Node*> subord);
	int maxElemHelp(std::vector<int> arr);
	void removeVertex(Node* start, std::string name);
	void transferOfSubord(Node* newEmp, std::vector<std::string> subord);
	bool isEmployeeInCompany(Node* start, std::string name);
	bool isEmployeeDifferentFromFirstLevel(std::string name);
	void hireEmployee(Node* start, std::string name, std::vector<std::string> subord);
	void findBossOfTheBoss(Node* start, Node*& bossOfTheBoss, std::string name);
	std::vector<std::string> directSubExceptBoss(Node* start, std::string name);
	std::vector<std::string> allSub(Node* empl);
	void findEmployee(Node* start, Node*& empl, std::string name);
	std::string findDirBoss(Node* start, std::string name);

public:
	Node* boss;

	Company(std::string nameOfABoss);
	Company(const Company& other);
	Company& operator=(const Company& rhs);
	~Company();

	void appointmentWithoutSubordinates(std::string nameOfANewMember, std::string nameOfHisBoss);
	void appointmentWithSubordinates(std::string nameOfANewMember, std::string nameOfHisBoss, std::vector<std::string> subord);
	void firingEmployeeWithoutSubordinates(std::string nameOfAnEmployee);
	void firingEmployeeWithSubordinates(std::string nameOfAnEmployee);
	void hiringEmployee(std::string nameOfAnEmployee, std::vector<std::string> subord);

	std::vector<std::string> directSubordinatesOf(std::string nameOfAnEmployee);
	std::vector<std::string> allSubordinatesOf(std::string nameOfAnEmployee);
	std::string directBoss(std::string nameOfAnEmployee);

	
};

#endif
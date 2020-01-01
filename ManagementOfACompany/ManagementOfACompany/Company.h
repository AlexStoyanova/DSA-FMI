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
	void copyHelp(Node* ours, Node* theirs);
	void addLeafConstant(Node* ours, const std::string& newEmpl);
	void clearHelp(Node* start);
	void clear();
	
	bool isLeaf(const Node* elem) const;
	void addLeaf(Node* start, Node* newEmp, const std::string& name);
	void removeLeaf(Node* start, const std::string& name);

	int maxHeightFromEmployee(Node* start) const;
	int maxHeightForEmployeeSubord(const std::vector<Node*>& subord) const;
	int maxElemHelp(const std::vector<int>& arr) const;

	void removeVertex(Node* start, const std::string& name);

	void transferOfSubord(Node* newEmp, const std::vector<std::string> subord);

	bool isEmployeeInCompany(Node* start, const std::string& name);
	bool isEmployeeDifferentFromFirstLevel(const std::string& name) const;

	void hireEmployee(Node* start, const std::string& name, const std::vector<std::string> subord);
	void findBossOfTheBoss(Node* start, Node*& bossOfTheBoss, const std::string& name) const;

	std::vector<std::string> directSubExceptBoss(Node* start, const std::string& name) const;
	std::vector<std::string> allSub(Node* empl) const;

	void findEmployee(Node* start, Node*& empl, const std::string& name) const;
	std::string findDirBoss(Node* start, const std::string& name) const;

public:
	Node* boss;

	Company(const std::string nameOfABoss);
	Company(const Company& other);
	Company& operator=(const Company& rhs);
	~Company();

	void appointmentWithoutSubordinates(const std::string& nameOfANewMember, const std::string& nameOfHisBoss);
	void appointmentWithSubordinates(const std::string& nameOfANewMember, const std::string& nameOfHisBoss, const std::vector<std::string> subord);
	void firingEmployeeWithoutSubordinates(const std::string& nameOfAnEmployee);
	void firingEmployeeWithSubordinates(const std::string& nameOfAnEmployee);
	void hiringEmployee(const std::string& nameOfAnEmployee, const std::vector<std::string> subord);

	std::vector<std::string> directSubordinatesOf(const std::string& nameOfAnEmployee) const;
	std::vector<std::string> allSubordinatesOf(const std::string& nameOfAnEmployee) const;
	std::string directBoss(const std::string& nameOfAnEmployee) const;

};

#endif
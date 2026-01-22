#pragma once
#include <string>

class Member {
private:
	int memberId;
	std::string name;
public:
	Member();
	Member(int id, std::string n);
	int getMemberId () const;
	std::string getName() const;
	void display() const;
};
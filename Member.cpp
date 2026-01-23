#include <string>
#include "Member.h"
#include <iostream>

Member::Member() {
	memberId = -1;
	name = "";
}

Member::Member(int id, std::string n) {
	memberId = id;
	name = n;
}

int Member::getMemberId() const {
	return memberId;
}
std::string Member::getName() const {
	return name;
}
void Member::display() const {
	std::cout << memberId << ", " << name << std::endl;
}
/*
------------------------------------------------------------
Hendi Wong Jia Ming (S10270162K)
------------------------------------------------------------
*/
#pragma once
#include "Member.h"
class MemberList {
private:
	struct Node {
		Member item;
		Node* next;
	};

	Node* firstNode;
	int size;

public:
	MemberList();
	~MemberList();
	bool addMember(Member member);
	void removeMember(int memberId);
	Member* findById(int memberId);
	void displayAll();
	void loadFromCSV(const std::string& filename);
};
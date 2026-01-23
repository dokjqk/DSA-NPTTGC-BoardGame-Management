#include "MemberList.h"
#include <iostream>

MemberList::MemberList() {
	firstNode = nullptr;
	size = 0;
}
MemberList::~MemberList() {
	Node* currentNode = firstNode;
	while (currentNode != nullptr) {
		Node* deleteNode = currentNode;
		currentNode = currentNode->next;
		delete deleteNode;
	}
	firstNode = nullptr;
	size = 0;
}
bool MemberList::addMember(Member member) {

	if (findById(member.getMemberId()) != nullptr) {
		return false;
	}

	Node* newNode = new Node;
	newNode->item = member;
	newNode->next = nullptr;

	if (firstNode == nullptr) {
		firstNode = newNode;
		size++;
		return true;
	}

	Node* currentNode = firstNode;
	while (currentNode->next != nullptr) {
		currentNode = currentNode->next;
	}

	currentNode->next = newNode;
	size++;
	return true;
}

void MemberList::removeMember(int memberId) {
	if (firstNode == nullptr) {
		return;
	}

	Node* currentNode = firstNode;
	Node* previousNode = nullptr;
	while (currentNode != nullptr) {
		if (currentNode->item.getMemberId() == memberId) {
			break;
		}
		previousNode = currentNode;
		currentNode = currentNode->next;
	}
	if (currentNode == nullptr) {
		return;
	}
	if (previousNode == nullptr) {
		firstNode = currentNode->next;
	}
	else {
		previousNode->next = currentNode->next;
	}
	delete currentNode;
	size--;
}

Member* MemberList::findById(int memberId) {
	Node* currentNode = firstNode;
	while (currentNode != nullptr) {
		if (currentNode->item.getMemberId() == memberId) {
			return &(currentNode->item);
		}
		currentNode = currentNode->next;
	}
	return nullptr;
}

void MemberList::displayAll() {
	if (firstNode == nullptr) {
		std::cout << "No members found.\n";
		return;
	}
	Node* currentNode = firstNode;
	while (currentNode != nullptr) {
		currentNode->item.display();
		currentNode = currentNode->next;
	}
}
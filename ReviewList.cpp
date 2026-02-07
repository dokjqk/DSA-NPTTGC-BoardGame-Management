#include "ReviewList.h"

ReviewList::ReviewList() {
    firstNode = nullptr;
}

ReviewList::~ReviewList() {
    while (firstNode != nullptr) {
        ReviewNode* temp = firstNode;
        firstNode = firstNode->next;
        delete temp;
    }
}

void ReviewList::addReview(Review review) {
    ReviewNode* newNode = new ReviewNode;
    newNode->item = review;
    newNode->next = nullptr;

    if (firstNode == nullptr) {
        firstNode = newNode;
        return;
    }

    ReviewNode* currentNode = firstNode;
    while (currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }
    currentNode->next = newNode;
}


void ReviewList::displayAll() {
    ReviewNode* currentNode = firstNode;
    while (currentNode != nullptr) {
        currentNode->item.display();
        currentNode = currentNode->next;
    }
}
#pragma once
#include "Review.h"

class ReviewList {
private:
    struct ReviewNode {
        Review item;
        ReviewNode* next;
    };

    ReviewNode* firstNode;

public:
    ReviewList();
    ~ReviewList();
    void addReview(Review review);
    void displayAll();
    void sortByRatingDesc();
};

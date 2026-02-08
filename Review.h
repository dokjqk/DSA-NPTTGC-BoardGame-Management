/*
------------------------------------------------------------
Hendi Wong Jia Ming (S10270162K)
------------------------------------------------------------
*/
#pragma once
#include <string>

class Review {
private:
	int memberId;
	int rating;
	std::string comment;

public:
	Review();
	Review(int memberId, int rating, std::string comment);

	int getMemberId() const;
	int getRating() const;
	void display() const;
};
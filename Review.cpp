#include "Review.h"
#include <iostream>
#include <string>

	Review::Review() {
		memberId = -1;
		rating = 0;
		comment = "";
	}
	Review::Review(int mId, int r, std::string c) {
		memberId = mId;
		rating = r;
		comment = c;
	}

	int Review::getMemberId() const {
		return memberId;
	}

	int Review::getRating() const {
		return rating;
	}

	void Review::display() const {
		std::cout << "Member " << memberId
			<< " | Rating: " << rating
			<< " | " << comment << std::endl;
	}
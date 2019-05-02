#pragma once

#include <string>

namespace bullpgia {

	struct answer{
		int bull; int pgia;

		bool operator==(const answer other){	
			return (this->bull==other.bull && this->pgia==other.pgia);
		}

		friend std::ostream& operator <<(std::ostream&, const bullpgia::answer&);
	};

	inline std::ostream& operator <<(std::ostream& os, const bullpgia::answer& ans){
		return os << std::to_string(ans.bull) << "," + std::to_string(ans.pgia);
	}
	
	const answer calculateBullAndPgia(const std::string choice, const std::string guess);

	int calculateBull(const std::string choice, const std::string guess);
}

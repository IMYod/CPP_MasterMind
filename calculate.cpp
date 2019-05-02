#include "calculate.hpp"
#include <string>
#include <iostream>
using std::string, std::to_string;

namespace bullpgia {
	const answer calculateBullAndPgia(const string choice, const string guess){
		uint length = choice.length();
		int bools=0, pgia=0;
		uint choiceCount[11]; //count i digits in choice
		uint guessCount[11]; //count i digits in guess
		for (int i=0; i<11; ++i) { //intilize the arrays
			choiceCount[i] = 0;
			guessCount[i] = 0;
		}

		for (int i=0; i<length; ++i) {
			if (choice[i] == guess[i]) //check bool
				bools++;
			choiceCount[choice[i]-'0']++; //The index choice[i] as int
			guessCount[guess[i]-'0']++; //The index guess[i] as int
		}
		
		int sumBullAndPgia = 0;
		for (int i=0; i<11; ++i) {
			sumBullAndPgia += std::min(choiceCount[i], guessCount[i]);
		}
		
		answer ans_clalculte;
		ans_clalculte.bull = bools;
		ans_clalculte.pgia = sumBullAndPgia - bools;
		return ans_clalculte;
	}

	int calculateBull(const string choice, const string guess){
		int bools=0;
		uint length = choice.length();
		for (int i=0; i<length; ++i)
			if (choice[i] == guess[i]) //check bool
				bools++;
		return bools;
	}
}

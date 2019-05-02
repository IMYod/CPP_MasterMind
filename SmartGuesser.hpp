#pragma once
#include "Guesser.hpp"
#include "calculate.hpp"
#include <unordered_set>


/**
 * ConstantGuesser is a guesser that always guesses the same string. 
 */
class SmartGuesser: public bullpgia::Guesser {
	private:
		std::unordered_set<std::string> myset;
		std::unordered_set<std::string> newSet; //using in learn function
		std::string lastGuess;

		bool left = false;
		bool right = false;
		void createRight(std::string);		

		std::string guessPossible();
		std::string guessByEfficiency();
		std::string guessByEfficiencyFast();
		std::string guessByMinOccur();
		std::string leftGuess();

	public:
		std::string guess() override;
		void startNewGame(uint theLength) override;
		void learn(bullpgia::answer response) override;
};

std::string numToGuess(int num, uint length);



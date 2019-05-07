#include "SmartGuesser.hpp"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <bits/stdc++.h>


using std::string, std::to_string, std::unordered_set, bullpgia::answer;

string SmartGuesser::guess() {

	string guess;
	
	if (myset.size()<=2){
		guess = guessPossible();
	}
	else if (counter = 0){ //first guess
		guess = "";
		if (left) {
			for (int i=0; i<length/2; i++)
				guess += to_string(i);
			string dontCare = "";
			for (int i=0; i<length - length/2; ++i)
				dontCare = dontCare + ":";
			guess += dontCare;
		}
		else if (right){
			guess = guessPossible().substr(0, length/2);
			for (int i=0; i<length - length/2; i++)
				guess += to_string(i);			
		}
		else{
			for (int i=0; i<length; i++)
				guess += to_string(i);
		}
	}
	else if (left)
		guess = leftGuess();

	else if (myset.size()*pow(10.0, length) < 100000) 
		guess = guessByEfficiency();
	else
		guess = guessByEfficiencyFast();
	
	this->lastGuess = guess;

	//std::cout << "size of set is: " << myset.size() << "\tguess: " << guess << std::endl;
	counter++;
	return guess;
}

void SmartGuesser::startNewGame(uint theLength) {
	counter = 0;
	length = theLength;
	if (length >6)
		left = true;
	lastGuess="-1";
}

void SmartGuesser::learn(answer response) {

	//if number in myset is match to the response -> insert it to the new set

	if (left) {
		if (response.bull == length/2){ //true for the left guess
			createRight(lastGuess.substr(0,length/2));
			return;
		}
		
		if (counter == 1){ //first insertion
			string dontCare = "";
			for (int i=0; i<length - length/2; ++i)
				dontCare = dontCare + ":";	

			myset.clear();
			for (int i=0; i<pow(10.0,length/2); ++i){
				string posChoice = numToGuess(i,theLength/2) + dontCare;
				if (response.bull + length/2 == bullpgia::calculateBullAndPgia(posChoice, lastGuess).bull)
					newSet.insert(posChoice);
			}
		}
		
		else {

			myset.erase(lastGuess);
			for ( auto it = myset.begin(); it != myset.end(); ++it ){
				if (response.bull + length/2 == bullpgia::calculateBullAndPgia(*it, lastGuess).bull)
					newSet.insert(*it);
			}

			myset=newSet;
			newSet.clear();

			if (newSet.size()==1){
				createRight((*newSet.begin()).substr(0,length/2));
			}
		}
	}

	else { //not left
		if (counter == 1){ //first insertion
			for (int i=0; i<pow(10.0,theLength); ++i){
				string posChoice = numToGuess(i,theLength);
				if (response.bull + length/2 == bullpgia::calculateBullAndPgia(posChoice, lastGuess).bull)
					newSet.insert(posChoice);
			}
		}
		
		myset.erase(lastGuess);
		for ( auto it = myset.begin(); it != myset.end(); ++it ){
			if (response==bullpgia::calculateBullAndPgia(*it, lastGuess)){
				newSet.insert(*it);
			}
		}

		myset=newSet;
		newSet.clear();
	}

	//std::cout << "response: " << response << std::endl;
}

void SmartGuesser::createRight(string leftString){
	//std::cout << "left string is: " << leftString << std::endl;
	myset.clear();
	for (int i=0; i<pow(10.0,length - length/2); ++i)
		this->myset.insert(leftString + numToGuess(i,length - length/2));
	left = false;
	right = true;
	lastGuess = "-1";
}

//convert number to guess type by padding "0"
string numToGuess(int num, uint length){
	string guess = to_string(num);
	int numOfZeros = length - guess.length();
	for (int i=0; i<numOfZeros; ++i){
		guess = "0" + guess;
	}
	return guess;
}

//strategy: guess any possible number
string SmartGuesser::guessPossible() {
	return *myset.begin();
}

//strategy: secret...
struct countDigits{char digit; int counter;};
bool cdCompare(countDigits left, countDigits right) {return left.counter < right.counter;}

string SmartGuesser::guessByMinOccur() {
	countDigits occurs[10];
	for (int i=0; i<10; ++i){
		occurs[i].counter=0;
		occurs[i].digit = '0'+i;
	}
	
	for (auto it = myset.begin(); it != myset.end(); ++it )
		for (int i=0; i<(*it).length(); ++i)
			occurs[(*it)[i] -'0'].counter++;

	/*for (int i=0; i<10; ++i){
		std::cout << "The digit " << occurs[i].digit << " occurs " << occurs[i].counter << " times" << std::endl;
	}*/
	
	std::sort(occurs, occurs+10, cdCompare); //doesn't work
	string guess = "";
	for (int i=0; i<length; ++i){
		guess += occurs[i].digit;
	}

	if (guess==lastGuess)
		return guessPossible();

	std::vector<int> arr;
	for (int i=0; i<length; ++i)
		arr.push_back(i);
	
	string randGuess="";
	std::random_shuffle(arr.begin(), arr.end());
	for (std::vector<int>::iterator i=arr.begin(); i!=arr.end(); ++i)
		randGuess += occurs[(*i)].digit;

	//std::cout << "Occur guess: " << randGuess << std::endl;
	return randGuess;
}

//strategy: secret...
string SmartGuesser::guessByEfficiency() {
	int maxNumber = pow(10.0, length);
	int possibleReply[length+1][length+1];
	
	int minOfMaximums = maxNumber; //very high number
	string bestGuess = "-1";


	for (int i=0; i<maxNumber; ++i){
		for (int j=0; j<=length; ++j)
			for (int k=0; k<=length; ++k)
				possibleReply[j][k]=0;

		string iAsString = numToGuess(i,length);
		for (auto it = myset.begin(); it != myset.end(); ++it ){
			answer posReply = bullpgia::calculateBullAndPgia(*it, iAsString);
			possibleReply[posReply.bull][posReply.pgia]++;		
		}

		int maxForI = 0;		
		for (int j=0; j<=length; ++j)
			for (int k=0; k<=length; ++k)
				if (possibleReply[j][k] > maxForI)
					maxForI = possibleReply[j][k];
		
		if (maxForI < minOfMaximums){
			minOfMaximums = maxForI;
			bestGuess = iAsString;
		}
	}
	//std::cout << "Efficiency guess: " << bestGuess << std::endl;
	return bestGuess;
}


//strategy: secret...
string SmartGuesser::guessByEfficiencyFast() {
	int maxNumber = pow(10.0, length);
	int possibleReply[length+1][length+1];
	
	int minOfMaximums = INT_MAX; //very high number
	string bestGuess = "-1";

	auto start = time(0);
	for (auto itGuess = myset.begin(); itGuess != myset.end(); ++itGuess){
		if (time(0) - start > 0.15)
			break;
		for (int j=0; j<=length; ++j)
			for (int k=0; k<=length; ++k)
				possibleReply[j][k]=0;

		for (auto it = myset.begin(); it != myset.end(); ++it ){
			answer posReply = bullpgia::calculateBullAndPgia(*it, *itGuess);
			possibleReply[posReply.bull][posReply.pgia]++;		
		}

		int maxForI = 0;		
		for (int j=0; j<=length; ++j)
			for (int k=0; k<=length; ++k)
				if (possibleReply[j][k] > maxForI)
					maxForI = possibleReply[j][k];
		
		if (maxForI < minOfMaximums){
			minOfMaximums = maxForI;
			bestGuess = *itGuess;
		}
	}
	//std::cout << "Fast Efficiency guess: " << bestGuess << std::endl;
	return bestGuess;
}

string SmartGuesser::leftGuess() {
	int possibleReply[length+1];
	
	int minOfMaximums = 999999; //very high number
	string bestGuess = "-1";

	auto start = time(0);
	for (auto itGuess = myset.begin(); itGuess != myset.end(); ++itGuess){
		if (time(0) - start > 0.15){
			break;
		}
		for (int j=0; j<=length; ++j)
				possibleReply[j]=0;

		for (auto it = myset.begin(); it != myset.end(); ++it ){
			int posReply = bullpgia::calculateBull(*it, *itGuess);
			possibleReply[posReply]++;		
		}

		int maxForI = 0;		
		for (int j=0; j<=length; ++j)
			if (possibleReply[j] > maxForI)
				maxForI = possibleReply[j];
		
		if (maxForI < minOfMaximums){
			minOfMaximums = maxForI;
			bestGuess = *itGuess;
		}
	}
	//std::cout << "Fast Efficiency guess: " << bestGuess << std::endl;
	return bestGuess;
}









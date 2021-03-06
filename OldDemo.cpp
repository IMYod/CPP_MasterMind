/**
 * A demo program for bull-pgia.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-04
 */


#include <iostream>
using namespace std;

#include "play.hpp"
#include "DummyChoosers.hpp"
#include "DummyGuessers.hpp"
#include "SmartGuesser.hpp"
using namespace bullpgia;

int main() {
	/*ConstantChooser c1234{"1234"}, c12345{"12345"}, c9999{"9999"};
	ConstantGuesser g1234{"1234"}, g12345{"12345"}, g9999{"9999"};
	cout << play(c1234, g1234, 4, 100) << endl;  // prints 1 - guesser wins in one turn.
	cout << play(c1234, g9999, 4, 100) << endl;  // prints 101 - guesser loses by running out of turns 
	cout << play(c1234, g12345, 4, 100) << endl;  // prints 101 - guesser loses technically by making an illegal guess (too long).
	cout << play(c12345, g1234, 4, 100) << endl;  // prints 0 - chooser loses technically by choosing an illegal number (too long).

	RandomChooser rc;
	RandomGuesser rg;
	for (uint i=0; i<100; ++i) {
		cout << play(rc, rg, 2, 100) << endl;  // guesser should often win but sometimes lose.
	}*/

	SmartGuesser smarty;
/*	int sum = 0;
	for (uint i=0; i<100; ++i) {
		sum += play(rc, smarty, 4, 100);  // smarty should always win in at most 10 turns!
	}
	cout << "average is:" << sum/100.0 << endl;*/

	int max = 0;
	for (int i=0; i<=9999; ++i){
		if (i%100 == 0)
			cout << "max=" << max << ", i=" << i << endl;
		ConstantChooser cc(numToGuess(i,4));
		int turns = play(cc, smarty, 4, 100);  // smarty should always win in at most 10 turns!
		if (turns > max)
			max = turns;
	}

	cout << "total max=" << max << endl;

	return 0;
}


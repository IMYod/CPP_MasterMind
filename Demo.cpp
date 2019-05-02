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
	ConstantChooser c1234{"1234"}, c12345{"12345"}, c9999{"9999"}, c99999996{"99999996"};
	ConstantGuesser g1234{"123&"}, g12345{"12345"}, g9999{"9999"};

	RandomChooser rc;
	RandomGuesser rg;
	/*for (uint i=0; i<100; ++i) {
		cout << play(rc, rg, 2, 100) << endl;  // guesser should often win but sometimes lose.
	}*/

	SmartGuesser smarty;
	/*for (uint i=0; i<10; ++i) {
		cout << play(rc, smarty, 8, 100) << endl;
	}*/

	int sum = 0;
	for (uint i=0; i<100; ++i) {
		sum += play(rc, smarty, 4, 100);  // smarty should always win in at most 10 turns!
		cout << "average is:" << 1.0*sum/(i+1) << endl << endl;
	}
	//cout << "average is:" << sum/100.0 << endl;

	return 0;
}


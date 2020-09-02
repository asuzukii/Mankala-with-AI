#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Board b(3, 2);
	//assert(b.holes() == 3 && b.totalBeans() == 12 &&
		//b.beans(SOUTH, POT) == 0 && b.beansInPlay(SOUTH) == 6);
	cout << b.holes() << endl;
	cout << b.totalBeans() << endl;
	cout << b.beans(SOUTH, POT) << endl;
	cout << b.beansInPlay(SOUTH);
	/*b.setBeans(SOUTH, 1, 1);
	b.moveToPot(SOUTH, 2, SOUTH);
	assert(b.totalBeans() == 11 && b.beans(SOUTH, 1) == 1 &&
		b.beans(SOUTH, 2) == 0 && b.beans(SOUTH, POT) == 2 &&
		b.beansInPlay(SOUTH) == 3);
	Side es;
	int eh;
	b.sow(SOUTH, 3, es, eh);
	assert(es == NORTH && eh == 3 && b.beans(SOUTH, 3) == 0 &&
		b.beans(NORTH, 3) == 3 && b.beans(SOUTH, POT) == 3 &&
		b.beansInPlay(SOUTH) == 1 && b.beansInPlay(NORTH) == 7);
	cout << "Passed all tests" << endl;*/
}
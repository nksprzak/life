#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Life.h"

int main()
{
	using namespace std;

	//parse(cin);

	cout << "*** Life<ConwayCell> 21x13 ***" << endl;

	Life<ConwayCell> test(21,13);
	test.parseFile(cin);
	test.printGrid();
	//cout << test.alive_neighs(0,0);

	//free(test);
	//delete test;

	//test.grid[8][5];

	cout << "*** Life<ConwayCell> 20x29 ***" << endl;

	//t2.printGrid();




	Life<ConwayCell> t2(20,29);
	t2.parseFile(cin);
	t2.printGrid();



	cout << "*** Life<ConwayCell> 109x69 ***" << endl;

	Life<ConwayCell> t3(109,69);
	t3.parseFile(cin);
	t3.printGrid();

	cout << "*** Life<FredkinCell> 20x20 ***" << endl;
	Life<FredkinCell> t4(20,20);
	t4.parseFile(cin);
	t4.printGrid();

	cout << "*** Life<Cell> 20x20 ***" << endl;
	Life<Cell> t5(20,20);
	cout<<"parsing"<<endl;
	t5.parseFile(cin);
	cout<<"running"<<endl;
	t5.run();
	return 0;
}
#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Life.h"

int main()
{
	using namespace std;

	//parse(cin);

	/*cout << "*** Life<ConwayCell> 21x13 ***" << endl;

	Life<ConwayCell> test(21,13);
	test.parseFile(cin);
	test.run();
	
	cout << "*** Life<ConwayCell> 20x29 ***" << endl;


	Life<ConwayCell> t2(20,29);
	t2.parseFile(cin);
	t2.run();


	cout << "*** Life<ConwayCell> 109x69 ***" << endl;

	Life<ConwayCell> t3(109,69);
	t3.parseFile(cin);
	t3.run();

	cout << "*** Life<FredkinCell> 20x20 ***" << endl;
	Life<FredkinCell> t4(20,20);
	t4.parseFile(cin);
	t4.run();

	cout << "*** Life<Cell> 20x20 ***" << endl;
	Life<Cell> t5(20,20);
	t5.parseFile(cin);
	t5.run();

	cout << "*** Life<ConwayCell> 109x69 ***"*/

	while(cin)
	{
		//Life<T>
		string cell_type;
		int row, col, iterations,frequecy;
		cin >> cell_type;
		cin >> row;
		cin >> col;
		cin >> iterations;
		cin >> frequecy;
		if(row == 0 || col == 0)
		{
			return 0;
		}
		//cout << cell_type;

		if(cell_type == "ConwayCell")
		{
			cout << "*** ConwayCell<" << row <<","<<col <<"> ***\n";
			Life<ConwayCell> test(row,col);

			test.parseFile(cin);
			test.run(iterations, frequecy);
		}
		if(cell_type == "FredkinCell")
		{
			cout << "*** FredkinCell<" << row <<","<<col <<"> ***\n";
			Life<FredkinCell> test(row,col);
			test.parseFile(cin);
			test.run(iterations, frequecy);
		}
		if(cell_type == "Cell")
		{
			cout << "*** Cell<" << row <<","<<col <<"> ***\n";
			Life<Cell> test(row,col);
			test.parseFile(cin);
			test.run(iterations, frequecy);
		}


	}
	return 0;
}
#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Life.h"

int main()
{
	using namespace std;

	while(cin)
	{
		string cell_type;
		int row, col, iterations,frequecy;
		cin >> cell_type;
		cin >> row;
		cin >> col;
		cin >> iterations;
		cin >> frequecy;
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
#include <cassert>    // assert
#include <cstddef>    // ptrdiff_t, size_t
#include <new>        // bad_alloc, new
#include <stdexcept>  // invalid_argument
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>

#ifndef Life_h
#define Life_h

using namespace std;

class AbstractCell
{
protected:
	bool alive;
	char status; //for Conway status is * or . fredkin its - or (int),+
public:
	virtual int num_alive(int x, int y)=0;
	virtual int num_dead(int x, int y)=0;
	//virtual void execute();
};

class Cell
{
private:
	AbstractCell* p;
public:
	Cell() {};

};

class ConwayCell: public AbstractCell
{
public:
	int num_alive(int x, int y);
	int num_dead(int x, int y);

	ConwayCell() {};
};

class FredkinCell: public AbstractCell
{
private:
	int age;
public:
	int num_alive(int x, int y);
	int num_dead(int x, int y);
};


template <typename T>
class Life
{

private:
	vector<vector<T> > grid;
	int _x;
	int _y;

public:
	void execute(int steps);
	void printGrid();




	Life<T>(int x, int y){
		_x = x;
		_y = y;
		for(int i = 0; i < x; i++)
		{
			vector<T> a;
			for(int j = 0; j < y; j++)
			{
				a = vector<T>(x);
			}
			grid.push_back(a);
		}
	};

};

#endif // Life_h


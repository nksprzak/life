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

};

class FredkinCell: public AbstractCell
{
private:
	int age;
};


template <typename T>
class Life
{

private:
	vector<vector<T> > grid;

};

#endif // Life_h


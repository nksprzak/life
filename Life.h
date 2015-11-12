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

	FredkinCell() {};
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
	void parse(istream& r)
	{
		string s;
		string::size_type sz;
		getline(r,s);
		string cell_type = s;
		cout << s << endl;
		getline(r,s);
		int rows = stoi(s,&sz);
		cout << rows << endl;;
		getline(r,s);
		int cols = stoi(s,&sz);
		cout << cols << endl;;
		getline(r,s);
		int iterations = stoi(s,&sz);
		cout << iterations << endl;
		getline(r,s);
		int num_of_prints = stoi(s,&sz);
		
		/*if(cell_type == "ConwayCell") Life<ConwayCell> w(rows,cols);
		if(cell_type == "FredkinCell") Life<FredkinCell> w(rows,cols);
		else Life<Cell> w(rows,cols);*/
		//Life<Cell> w(rows,cols);
		int rs = 0;
		int cs = 0;
		while(getline(r,s) && !s.empty())
		{
			char buf;
			
			stringstream in(s);
			while(in >> buf)
			{
				ConwayCell a();
				grid[rs][cs] = a;
				/*ConwayCell a();
				w.grid[rs][cs] = a;*/
				cout << rs << cs << endl;
				cs++;
			}
			cs = 0;
			rs++;

		}
	}



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


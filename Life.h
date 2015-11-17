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
	char status;
	
public:
	virtual bool isAlive() {return alive;};
	
};

class Cell
{
private:
	AbstractCell* p;
public:
	Cell() {

	};


	bool isAlive() {return p->isAlive();};

};

class ConwayCell: public AbstractCell
{
public:
	/*int num_alive(int x, int y);
	int num_dead(int x, int y);*/

	ConwayCell() {
		status = '*';
	};

	ConwayCell(char b) {
		status = b;
		if(b == '*') alive = true;
		else alive = false;
	};

	friend std::ostream& operator << (std::ostream& os, const ConwayCell& sp)
	{
		os << sp.status;
		return os;
	}
};

class FredkinCell: public AbstractCell
{
private:
	int age;
public:
	/*int num_alive(int x, int y);
	int num_dead(int x, int y);
	*/
	FredkinCell() {};
	FredkinCell(char s) {
		status = s;
		if(s == '-') alive = false;
		else alive = true;
		//ab ge = a;
	};
	friend std::ostream& operator << (std::ostream& os, const FredkinCell& sp)
	{
		os << sp.status;
		return os;
	}
};


template <typename T>
class Life
{

private:
	vector<vector<T> > grid;

	vector<T> cells;
	int _x;
	int _y;

public:
	void execute(int steps);
	void parseFile(istream& r)
	{
		//T f;
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
		
		
		int rs = 0;
		int cs = 0;
		//if(cell_type = )
		/*for(int i =0; i < _y; i++)
		{
			T f('&');
			grid[0][i] = f;
		}*/
		while(getline(r,s) && !s.empty())
		{
			char buf;
			
			stringstream in(s);
			while(in >> buf)
			{
				T f(buf);
				grid[rs][cs] = f;
				cs++;
			}
			cs = 0;
			rs++;

		}
	}
	int alive_neighs(int x, int y)
	{
		//replace x & y with the value youre looking at 
		//were gunna check (x-1,y-1)(x,y-1),(x+1,y-1)
		//				   (x -1, y)        (x+1,y)
		//				   (x -1,y+1)(x,y+1)(x+1,y+1)
		int count = 0;
		int x_less = x -1 ; int y_less = y -1;
		int x_more = x + 1; int y_more = y + 1;
		//cout << grid[x][y] << endl;
		if(x_less >= 0 && y_less >= 0)
		{
			//cout << ""
			//cout << grid[x_less][y_less].isAlive() << endl;
			if(grid[x_less][y_less].isAlive()) count++;
		}
		if(x_less >= 0 && y >= 0)
		{
			//cout << grid[x_less][y].isAlive() << endl;
			if(grid[x_less][y].isAlive()) count++;
		}
		if(x_less >= 0 && y_more < _y)
		{
			//cout << x_more << y_less << endl;
			//cout << grid[x_more][y_less] << endl;
			if(grid[x_less][y_more].isAlive()) count++;
		}
		if(x >= 0 && y_less >= 0)
		{
			//cout << grid[x][y_less].isAlive() << endl;
			if(grid[x][y_less].isAlive()) count++;
		}
		if(x >= 0 && y_more < _y)
		{
			//cout << grid[x][y_more].isAlive() << endl;
			if(grid[x][y_more].isAlive()) count++;
		}
		if(x_more < _x && y_less >= 0)
		{
			//cout << grid[x_more][y_less].isAlive() << endl;
			if(grid[x_more][y_less].isAlive()) count++;
		}
		if(x_more < _x && y >= 0)
		{
			//cout << grid[x_more][y].isAlive() << endl;
			if(grid[x_more][y].isAlive()) count++;
		}
		if(x_more < _x && y_more < _y)
		{
			//cout << grid[x_more][y_more].isAlive() << endl;
			if(grid[x_more][y_more].isAlive()) count++;
		}
		return count;

	}


	void printGrid()
	{
		for(int i = 0; i < this->_x; ++i)
		{
			for(int j = 0 ; j < this->_y; ++j)
			{
				cout << grid[i][j];
			}
			cout << endl;
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
				a = vector<T>(y);
			}
			grid.push_back(a);
		}
	};

};




#endif // Life_h


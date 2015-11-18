#include <cassert>    // assert
#include <cstddef>    // ptrdiff_t, size_t
#include <new>        // bad_alloc, new
#include <stdexcept>  // invalid_argument
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>

#include "gtest/gtest.h"

#ifndef Life_h
#define Life_h

using namespace std;

class FredkinCell;

class AbstractCell
{
protected:
	bool alive;
	char status;

	FRIEND_TEST(TestConwayContructor, conway1);
	FRIEND_TEST(TestConwayContructor, conway2);
	FRIEND_TEST(TestFredkinConstructor, fred_con1);
	FRIEND_TEST(TestFredkinConstructor, fred_con2);
	FRIEND_TEST(TestFredkinConstructor, fred_con3);
	FRIEND_TEST(TestConwayExecute, c_exe1);
	FRIEND_TEST(TestConwayExecute, c_exe2);
	FRIEND_TEST(TestConwayExecute, c_exe3);
	FRIEND_TEST(TestFredkinExecute, f_exe1);
	FRIEND_TEST(TestFredkinExecute, f_exe2);
	FRIEND_TEST(TestFredkinExecute, f_exe3);

public:
	virtual bool isAlive() {return alive;};
	virtual char isStatus(){return status;}
	virtual void cell_Execute(int neighs){};
	
};

class Cell
{
private:
	AbstractCell* p;
	char status;

	FRIEND_TEST(TestCellConstructor, con1);
	FRIEND_TEST(TestCellConstructor, con2);
	FRIEND_TEST(TestCellConstructor, con3);
	FRIEND_TEST(TestCellAlive, ali1);
	FRIEND_TEST(TestCellAlive, ali2);
	FRIEND_TEST(TestCellAlive, ali3);
	FRIEND_TEST(TestCellExecute, c_exe1);
	FRIEND_TEST(TestCellExecute, c_exe2);
	FRIEND_TEST(TestCellExecute, c_exe3);

public:
	Cell(){};

	Cell(char b);

	bool isAlive() {return p->isAlive();};

	char isStatus() {return p->isStatus();};

	void cell_Execute(int n);
	
	friend std::ostream& operator << (std::ostream& os, const Cell& sp)
	{
		os << sp.status;
		return os;
	}

	

};

class ConwayCell: public AbstractCell
{
public:
	
	ConwayCell() 
	{
		status = '*';
	};

	ConwayCell(char b) 
	{
		status = b;
		if(b == '*') alive = true;
		else alive = false;
	};

	void cell_Execute(int n);

	friend std::ostream& operator << (std::ostream& os, const ConwayCell& sp)
	{
		os << sp.status;
		return os;
	}
};

class FredkinCell: public AbstractCell
{
private:
	char age;
public:
	FredkinCell() {};
	FredkinCell(char s) {
		status = s;
		age = 48;
		if(s == '-') alive = false;
		else alive = true;
	};
	void cell_Execute(int n);
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
	string cell_type;
	int iterations;
	int num_of_prints;
	int population;

public:
	void parseFile(istream& r)
	{
		string s;
		string::size_type sz;
		getline(r,s);
		cell_type = s;
		getline(r,s);
		//int rows = stoi(s,&sz);
		getline(r,s);
		//int cols = stoi(s,&sz);
		getline(r,s);
		iterations = stoi(s,&sz);
		getline(r,s);
		num_of_prints = stoi(s,&sz);	
		int rs = 0;
		int cs = 0;
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
	
		if(x_less >= 0 && y_less >= 0 && grid[x][y].isStatus() == '.' || grid[x][y].isStatus() == '*' )
		{
			if(grid[x_less][y_less].isAlive()) count++;
		}
		if(x_less >= 0 && y >= 0)
		{
			if(grid[x_less][y].isAlive()) count++;
		}
		if(x_less >= 0 && y_more < _y && grid[x][y].isStatus() == '.' || grid[x][y].isStatus() == '*' )
		{
			if(grid[x_less][y_more].isAlive()) count++;
		}
		if(x >= 0 && y_less >= 0)
		{
			if(grid[x][y_less].isAlive()) count++;
		}
		if(x >= 0 && y_more < _y)
		{
			if(grid[x][y_more].isAlive()) count++;
		}
		if(x_more < _x && y_less >= 0 && grid[x][y].isStatus() == '.' || grid[x][y].isStatus() == '*' )
		{
			if(grid[x_more][y_less].isAlive()) count++;
		}
		if(x_more < _x && y >= 0)
		{
			if(grid[x_more][y].isAlive()) count++;
		}
		if(x_more < _x && y_more < _y && grid[x][y].isStatus() == '.' || grid[x][y].isStatus() == '*' )
		{
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
	
	void execute()
	{
		vector<vector<int> > cells_neighs(_x,vector<int>(_y));
		for(int i = 0; i < _x; i++)
		{
			vector<int> buf;
			for(int j =0 ; j < _y; j++)
			{
				cells_neighs[i][j] = alive_neighs(i,j);
			}
		}
		for(int i = 0; i < _x; i++)
		{
			for(int j =0 ; j < _y; j++)
			{
				grid[i][j].cell_Execute(cells_neighs[i][j]);
			}
		}
	}

	void run()
	{
		cout << "Generation = 0, Population = " << getPopulation() <<endl;
		printGrid();
		cout << endl;
		for(int i = 1; i <= iterations; i++)
		{
			execute();
			if(i%num_of_prints == 0)
			{
				
				cout << "Generation = " << i << ", " << "Population = " << getPopulation() << endl;
				printGrid();
				cout << endl;
			} 
			population = 0;
		}
	}

	int getPopulation()
	{
		population = 0;
		for(int i = 0; i < _x; i++)
		{
			for(int j = 0; j < _y; j++)
			{
				if(grid[i][j].isStatus()!='.'&&grid[i][j].isStatus()!='-') population++;
			}
		}
		return population;
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


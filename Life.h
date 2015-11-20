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
	virtual ~AbstractCell(); 
	virtual AbstractCell* clone() = 0;

};

class ConwayCell: public AbstractCell
{
public:
	
	ConwayCell() 
	{
		status = '*';
		alive = false;
	};

	ConwayCell(char b) 
	{
		//cout<<"create conway"<<endl;
		status = b;
		if(b == '*') alive = true;
		else alive = false;
	};

	AbstractCell* clone();
	virtual ~ConwayCell() {};

	void cell_Execute(int n);
	bool isAlive();
	char isStatus();
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
	FredkinCell() {
		age = 48;
		alive = true;
		status = '-';
	};
	FredkinCell(char s) {
		//cout<<"create fred"<<endl;
		status = s;
		age = 48;
		if(s == '-') alive = false;
		else alive = true;
	};
	virtual ~FredkinCell() {};
	AbstractCell* clone();
	bool isAlive();
	char isStatus();
	void cell_Execute(int n);
	friend std::ostream& operator << (std::ostream& os, const FredkinCell& sp)
	{
		os << sp.status;
		return os;
	}
};

class Cell
{
private:
	AbstractCell* p;
	//Since cell doesnt inherit from Abstract cell status
	//needs to be added in order to properly parse the file
	//char status;

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
	Cell(){
		p = new FredkinCell('-');
	};
	Cell(AbstractCell* ac)
	{
		p = ac;
	}
	Cell(const Cell& c) 
	{
		p = c.p->clone();
	}
	Cell(char b);
	~Cell(){delete p;}
	bool isAlive() {//cout<<p<<endl;
		return p->isAlive();};
	//the status of the cell is used in computing live neighbors
	char isStatus() {return p->isStatus();};
	void cell_Execute(int n);


	Cell& operator =(const Cell& c)
	{
		delete p;
		p = c.p->clone();
		return *this;
	}
	friend std::ostream& operator << (std::ostream& os, const Cell& sp)
	{
		os << sp.p->isStatus();
		return os;
	}

	

};

template <typename T>
class Life
{

private:
	vector<vector<T> > grid;
	vector<Cell> cells;
	int _x;
	int _y;
	string cell_type;
	int iterations;
	int num_of_prints;
	int population;

	FRIEND_TEST(TestLifeConstructor, life1);
	FRIEND_TEST(TestLifeConstructor, life2);
	FRIEND_TEST(TestLifeConstructor, life3);
	FRIEND_TEST(TestLifeParse, parse1);
	FRIEND_TEST(TestLifeParse, parse2);
	FRIEND_TEST(TestLifeParse, parse3);
	FRIEND_TEST(TestLifeExecute, l_exe1);
	FRIEND_TEST(TestLifeExecute, l_exe2);
	FRIEND_TEST(TestLifeExecute, l_exe3);

public:
	
/*Reads the input file and generates the generation 0 graph*/

	//typename typedef std::vector< T>::iterator iterator;


	std::vector<Cell>::iterator begin()
	{
		return cells.begin();
	}

	std::vector<Cell>::iterator end()
	{
		return cells.end();
	}

	Cell& at(int index)
	{
		return cells[index];
	}

	//Cell& at(int index);

	void parseFile(istream& r)
	{
		string s;
		int rs =0;
		int cs = 0;
		getline(r,s);
		while(getline(r,s) && !s.empty())
		{
			char buf;
			stringstream in(s);
			while(in >> buf)
			{
				T f(buf);
				Cell h(buf);
				grid[rs][cs] = f;
				cells.push_back(h);
				cs++;	
			}
			cs = 0;
			rs++;
		}
	}
	/*Checks a potential of 8 neighbors for a conway cell and
	4 neighbors for a fredkin cell. The type of cell is determined 
	by life asking the status of the cell and determining the type 
	from the returned value. Graph incies are verified before access
	to deal with corner and edge cases, the number of alive neighbors
	is then returned to the game of Life*/ 
	int alive_neighs(int x, int y)
	{
		
		int count = 0;
		int x_less = x -1 ; int y_less = y -1;
		int x_more = x + 1; int y_more = y + 1;
		//NW neighbor
		if(x_less >= 0 && y_less >= 0 && (grid[x][y].isStatus() == '.' || grid[x][y].isStatus() == '*' ))
		{
			if(grid[x_less][y_less].isAlive()) count++;
		}
		//N neighbor
		if(x_less >= 0 && y >= 0)
		{
			if(grid[x_less][y].isAlive()) count++;
		}
		//NE neighbor		
		if(x_less >= 0 && y_more < _y && (grid[x][y].isStatus() == '.' || grid[x][y].isStatus() == '*' ))
		{
			if(grid[x_less][y_more].isAlive()) count++;
		}
		//W neighbor
		if(x >= 0 && y_less >= 0)
		{
			if(grid[x][y_less].isAlive()) count++;
		}
		//E neighbor
		if(x >= 0 && y_more < _y)
		{
			if(grid[x][y_more].isAlive()) count++;
		}
		//SW neighbor
		if(x_more < _x && y_less >= 0 && (grid[x][y].isStatus() == '.' || grid[x][y].isStatus() == '*' ))
		{
			if(grid[x_more][y_less].isAlive()) count++;
		}
		//S neighbor
		if(x_more < _x && y >= 0)
		{
			if(grid[x_more][y].isAlive()) count++;
		}
		//SE neighbor
		if(x_more < _x && y_more < _y && (grid[x][y].isStatus() == '.' || grid[x][y].isStatus() == '*' ))
		{
			if(grid[x_more][y_more].isAlive()) count++;
		}
		return count;
	}

	/*Prints the current board state*/
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
	/*Moves the game of life 1 generation*/
	void execute()
	{
		vector<vector<int> > cells_neighs(_x,vector<int>(_y));
		//int holder;
		//Creates a grid of # of live neighbors for each cell
		for(int i = 0; i < _x; i++)
		{
			vector<int> buf;
			for(int j =0 ; j < _y; j++)
			{
				cells_neighs[i][j] = alive_neighs(i,j);
				//holder = cells_neighs[i][j];
			}
		}
		/*Tells each cell to execute based on its number of live neighbors.
		cells handle their own execution*/
		for(int i = 0; i < _x; i++)
		{
			for(int j =0 ; j < _y; j++)
			{
				grid[i][j].cell_Execute(cells_neighs[i][j]);

			}
		}
	}
	/*Executes the game of life experiment @param iter is total 
	* generations required @param nums is how many generations 
	* run before printing the board
	*/
	void run(int iter, int nums)
	{
		cout << "Generation = 0, Population = " << getPopulation() <<endl;
		printGrid();
		cout << endl;
		for(int i = 1; i <= iter; i++)
		{
			execute();
			if(i%nums == 0)
			{
				cout << "Generation = " << i << ", " << "Population = " << getPopulation() << endl;
				printGrid();
				cout << endl;
			} 
			population = 0;
		}
	}
	/* returns the current number
	* of live cells 
	*/
	int getPopulation()
	{
		population = 0;
		for(int i = 0; i < _x; i++)
		{
			for(int j = 0; j < _y; j++)
			{
				if(grid[i][j].isAlive()) population++;
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
			a = vector<T>(y);
			grid.push_back(a);
		}
	};
};




#endif // Life_h


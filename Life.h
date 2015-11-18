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

class FredkinCell;

class AbstractCell
{
protected:
	bool alive;
	char status;
	
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
	/*int num_alive(int x, int y);
	int num_dead(int x, int y);*/

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

	void cell_Execute(int n)
	{
		if(alive)
		{
			if(n < 2 || n > 3)
			{
				alive = false;
				status = '.';	
			} 
		}
		else
		{
			if(n == 3)
			{
				alive = true;
				status = '*';
			} 
		}
	}

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
	friend std::ostream& operator << (std::ostream& os, const FredkinCell& sp)
	{
		os << sp.status;
		return os;
	}
	void cell_Execute(int n)
	{
		if(alive)
		{
			if(n == 0 || n == 2 || n == 4)
			{
				 alive = false;
				 status = '-';
			}
			else
			{
				age++;
				if( age <= 57 && age >= 48)
				{
					status = age;
				}
				else
				{
					status = '+';
				}
			} 
		}
		else
		{
			if(n== 1 || n== 3)
			{
				alive = true;
				age = 48;
				status = '0';	
			} 
		}
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

public:
	void execute(int steps);
	void parseFile(istream& r)
	{
		string s;
		string::size_type sz;
		getline(r,s);
		cell_type = s;
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
		if(x_less >= 0 && y_less >= 0 && grid[x][y].isStatus() == '.' || grid[x][y].isStatus() == '*' )
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
		if(x_less >= 0 && y_more < _y && grid[x][y].isStatus() == '.' || grid[x][y].isStatus() == '*' )
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
		if(x_more < _x && y_less >= 0 && grid[x][y].isStatus() == '.' || grid[x][y].isStatus() == '*' )
		{
			//cout << grid[x_more][y_less].isAlive() << endl;
			if(grid[x_more][y_less].isAlive()) count++;
		}
		if(x_more < _x && y >= 0)
		{
			//cout << grid[x_more][y].isAlive() << endl;
			if(grid[x_more][y].isAlive()) count++;
		}
		if(x_more < _x && y_more < _y && grid[x][y].isStatus() == '.' || grid[x][y].isStatus() == '*' )
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
	
	void execute()
	{
		vector<vector<int> > cells_neighs(_x,vector<int>(_y));
		for(int i = 0; i < _x; i++)
		{
			vector<int> buf;
			for(int j =0 ; j < _y; j++)
			{
				cells_neighs[i][j] = alive_neighs(i,j);
				//cout << alive_neighs(i,j);
				//cout << type(T);
			}
			//cout << endl;
		}
		cout << endl;
		for(int i = 0; i < _x; i++)
		{
			for(int j =0 ; j < _y; j++)
			{
				grid[i][j].cell_Execute(cells_neighs[i][j]);
			}
		}
		printGrid();
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

	//string type(){return cell_type;};

};




#endif // Life_h


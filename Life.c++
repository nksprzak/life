#include "Life.h"


int ConwayCell::num_alive(int x, int y)
{
	for(int r = 0; r < x; r++)
	{
		for(int c = 0; c < y; c++)
		{

		}
	}
}

int ConwayCell::num_dead(int x, int y)
{
	return 0;
}

template <typename T>
void Life<T>::printGrid()
{
	for(int i = 0; i < this->_x; ++i)
	{
		for(int j = 0 ; j < this->_y; ++j)
		{
			//wwcout >> grid[i][j]->status;
		}
		cout << endl;
	}
}

/*
int main()
{
	Life<Cell> a(8,8);
	a.printGrid();
	
	return 0;
}*/
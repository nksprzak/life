#include "Life.h"

Cell::Cell(char b)
{
	status = b;
	if(b=='*'||b=='.') p = new ConwayCell(b);
	else p = new FredkinCell(b);
}

void Cell::cell_Execute(int n)
	{
		p->cell_Execute(n);
		status = p->isStatus();
		if(status =='2')
		{
			p = new ConwayCell('*');
			status = '*';
		} 
	};


/*int ConwayCell::num_alive(int x, int y)
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
}*/
/*template <typename T>
void Life<T>::parseFile(istream& r)
	{
		
	}*/

/*
int main()
{
	Life<Cell> a(8,8);
	a.printGrid();
	
	return 0;
}*/
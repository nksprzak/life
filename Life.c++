#include "Life.h"

AbstractCell::~AbstractCell(){}

Cell::Cell(char b)
{
	
	status = b;
	//The status of the generic cell is used to determine
	//The type of cell to be created
	if(b=='*'||b=='.') p = new ConwayCell(b);
	else p = new FredkinCell(b);
	cout<<"creating cell p = "<<p<<endl;
}

void Cell::cell_Execute(int n)
{
	//Requires a cell to call its own execution since fredkin and Conway cells 
	//exhibit special behaviors
	p->cell_Execute(n);
	status = p->isStatus();
	if(status =='2')
	{
		//In the case of a Cell if a fredkin cell would turn to age 2, it becomes a conway cell
		//Needs memory management here
		cout<<"DELETING P "<<p<<endl;
		delete p;
		status = '*';
		p = new ConwayCell(status);
		cout<<"NEW P "<<p<<endl;		
	} 
}

void FredkinCell::cell_Execute(int n)
{
	if(alive)
	{
		//Fredkin cells die with 0,2, or 4 neighbors
		if(n == 0 || n == 2 || n == 4)
		{
			alive = false;
			status = '-';
		}
		else
		{
			age++;
			//Use character comparision to determine age 0-9
			if( age <= 57 && age >= 48)	status = age;
			else status = '+';
		} 
	}
	else
	{
		//revival of a dead cell with 1 or 3 neighbors
		if(n== 1 || n== 3)
		{
			alive = true;
			age = 48;
			status = '0';	
		} 
	}
}
bool FredkinCell::isAlive()
{
	if(status != '-') return true;
	return false;
}
char FredkinCell::isStatus()
{
	return status;
}

bool ConwayCell::isAlive()
{
	return status == '*';
}
char ConwayCell::isStatus()
{
	return status;
}
AbstractCell* ConwayCell::clone()
{
	return new ConwayCell(status);;
}
AbstractCell* FredkinCell::clone()
{
	return new FredkinCell(status);;
}
void ConwayCell::cell_Execute(int n)
{
	if(alive)
	{
		//Conway cells die with 1 or 0 alive neighbors or with more than 3 neighbors
		if(n < 2 || n > 3)
		{
			alive = false;
			status = '.';	
		} 
	}
	else
	{
		//dead cells are only revived with 3 live neighbors
		if(n == 3)
		{
			alive = true;
			status = '*';
		} 
	}
}
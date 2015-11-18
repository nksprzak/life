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
}

void FredkinCell::cell_Execute(int n)
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
			if( age <= 57 && age >= 48)	status = age;
			else status = '+';
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

void ConwayCell::cell_Execute(int n)
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
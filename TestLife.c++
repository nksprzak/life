#include <algorithm>
#include <sstream>
#include <string>
#include <typeinfo>

#include "gtest/gtest.h"

#include "Life.h"

TEST(TestCellConstructor, con1)
{
	Cell test = Cell('t');
	ASSERT_EQ('t',test.p->isStatus());
}
TEST(TestCellConstructor, con2)
{
	Cell test = Cell('z');
	ASSERT_EQ('z',test.p->isStatus());
}
TEST(TestCellConstructor, con3)
{
	Cell test = Cell('s');
	ASSERT_EQ('s',test.p->isStatus());
}

TEST(TestCellAlive, ali1)
{
	Cell test = Cell('*');
	
	ASSERT_TRUE(test.isAlive());
}
TEST(TestCellAlive, ali2)
{
	Cell test = Cell('0');
	
	ASSERT_TRUE(test.isAlive());
}
TEST(TestCellAlive, ali3)
{
	Cell test = Cell('.');
	
	ASSERT_FALSE(test.isAlive());
}
TEST(TestCellStatus, stat1)
{
	Cell test = Cell('-');
	ASSERT_EQ('-',test.isStatus());
}
TEST(TestCellStatus, stat2)
{
	Cell test = Cell('*');
	ASSERT_EQ('*',test.isStatus());
}
TEST(TestCellStatus, stat3)
{
	Cell test = Cell('0');
	ASSERT_EQ('0',test.isStatus());
}

TEST(TestCellExecute, c_exe1)
{
	Cell test = Cell('*');
	test.cell_Execute(0);
	ASSERT_EQ(test.isAlive(),false);

}
TEST(TestCellExecute, c_exe2)
{
	Cell test = Cell('.');
	test.cell_Execute(3);
	ASSERT_EQ(test.isAlive(),true);
}
TEST(TestCellExecute, c_exe3)
{
	Cell test = Cell('-');
	test.cell_Execute(1);
	ASSERT_EQ(test.isAlive(),true);
}
TEST(TestCellPrint, c_print1)
{
	Cell test = Cell('-');
	ostringstream o;
	o << test;
	ASSERT_EQ(o.str(),"-");
}
TEST(TestCellPrint, c_print2)
{
	Cell test = Cell('*');
	ostringstream o;
	o << test;
	ASSERT_EQ(o.str(),"*");
}
TEST(TestCellPrint, c_print3)
{
	Cell test = Cell('0');
	ostringstream o;
	o << test;
	ASSERT_EQ(o.str(),"0");
}
TEST(TestConwayContructor, conway1)
{
	ConwayCell test = ConwayCell('*');
	ASSERT_EQ(test.status,'*');
}
TEST(TestConwayContructor, conway2)
{
	ConwayCell test = ConwayCell('.');
	ASSERT_EQ(test.status,'.');
}
TEST(TestConwayExecute, c_exe1)
{
	ConwayCell test = ConwayCell('*');
	test.cell_Execute(0);
	ASSERT_FALSE(test.alive);
}
TEST(TestConwayExecute, c_exe2)
{
	ConwayCell test = ConwayCell('.');
	test.cell_Execute(3);
	ASSERT_TRUE(test.alive);
}
TEST(TestConwayExecute, c_exe3)
{
	ConwayCell test = ConwayCell('*');
	test.cell_Execute(4);
	ASSERT_FALSE(test.alive);
}
TEST(TestConwayPrint, c_print1)
{
	ConwayCell test = ConwayCell('*');
	ostringstream o;
	o << test;
	ASSERT_EQ(o.str(),"*");
}
TEST(TestConwayPrint, c_print2)
{
	ConwayCell test = ConwayCell('.');
	ostringstream o;
	o << test;
	ASSERT_EQ(o.str(),".");
}
TEST(TestFredkinConstructor, fred_con1)
{
	FredkinCell test = FredkinCell('0');
	ASSERT_EQ(test.status,'0');
}
TEST(TestFredkinConstructor, fred_con2)
{
	FredkinCell test = FredkinCell('-');
	ASSERT_EQ(test.status,'-');
}
TEST(TestFredkinConstructor, fred_con3)
{
	FredkinCell test = FredkinCell('3');
	ASSERT_EQ(test.status,'3');
}

TEST(TestFredkinExecute, f_exe1)
{
	FredkinCell test = FredkinCell('0');
	test.cell_Execute(0);
	ASSERT_FALSE(test.alive);
}
TEST(TestFredkinExecute, f_exe2)
{
	FredkinCell test = FredkinCell('-');
	test.cell_Execute(1);
	ASSERT_TRUE(test.alive);
}
TEST(TestFredkinExecute, f_exe3)
{
	FredkinCell test = FredkinCell('0');
	test.cell_Execute(1);
	ASSERT_EQ(test.status,'1');
}
TEST(TestFredkinPrint, f_print1)
{
	FredkinCell test = FredkinCell('-');
	ostringstream o;
	o << test;
	ASSERT_EQ(o.str(),"-");
}
TEST(TestFredkinPrint, f_print2)
{
	FredkinCell test = FredkinCell('0');
	ostringstream o;
	o << test;
	ASSERT_EQ(o.str(),"0");
}
TEST(TestLifeConstructor, life1)
{
	Life<ConwayCell> test(1,1);
	ASSERT_EQ(test._x,1);
}
TEST(TestLifeConstructor, life2)
{
	Life<FredkinCell> test(1,1);
	ASSERT_EQ(test._x,1);
}
TEST(TestLifeConstructor, life3)
{
	Life<Cell> test(2,2);
	ASSERT_EQ(test._y,2);
}
TEST(TestLifeParse, parse1)
{
	Life<ConwayCell> test(2,2);
	istringstream r("\n..\n..");
	test.parseFile(r);
	ASSERT_EQ(test.grid[0][0].isStatus(),'.');
}
TEST(TestLifeParse, parse2)
{
	Life<ConwayCell> test(2,2);
	istringstream r("\n..\n.*");
	test.parseFile(r);
	ASSERT_EQ(test.grid[1][1].isStatus(),'*');
}
TEST(TestLifeParse, parse3)
{
	Life<Cell> test(2,2);
	istringstream r("\n--\n--");
	test.parseFile(r);
	ASSERT_EQ(test.grid[1][1].isStatus(),'-');
}
TEST(TestLifeNeighs, alive1)
{
	Life<ConwayCell> test(2,2);
	istringstream r("\n..\n.*");
	test.parseFile(r);
	ASSERT_EQ(test.alive_neighs(0,0),1);
}
TEST(TestLifeNeighs, alive2)
{
	Life<ConwayCell> test(2,2);
	istringstream r("\n..\n**");
	test.parseFile(r);
	ASSERT_EQ(test.alive_neighs(0,0),2);
}
TEST(TestLifeNeighs, alive3)
{
	Life<ConwayCell> test(2,2);
	istringstream r("\n.*\n**");
	test.parseFile(r);
	ASSERT_EQ(test.alive_neighs(0,0),3);
}
TEST(TestLifeExecute, l_exe1)
{
	Life<ConwayCell> test(2,2);
	istringstream r("\n.*\n**");
	test.parseFile(r);
	test.execute();
	ASSERT_EQ(test.grid[0][0].isStatus(),'*');
}
TEST(TestLifeExecute, l_exe2)
{
	Life<FredkinCell> test(2,2);
	istringstream r("\n--\n--");
	test.parseFile(r);
	test.execute();
	ASSERT_EQ(test.grid[0][0].isStatus(),'-');
}
TEST(TestLifeExecute, l_exe3)
{
	Life<Cell> test(2,2);
	istringstream r("\n--\n--");
	test.parseFile(r);
	test.execute();
	ASSERT_EQ(test.grid[0][0].isStatus(),'-');
}
TEST(TestLifeRun, run1)
{
	Life<ConwayCell> test(3,3);
	istringstream r("\n...\n.*.\n..*");
	test.parseFile(r);
	test.run(2,1);
	ASSERT_EQ(test.getPopulation(),0);
}
TEST(TestLifeRun, run2)
{
	Life<FredkinCell> test(3,3);
	istringstream r("\n---\n-0-\n-0-");
	test.parseFile(r);
	test.run(2,2);
	ASSERT_EQ(test.getPopulation(),2);
}
TEST(TestLifeRun, run3)
{
	Life<Cell> test(3,3);
	istringstream r("\n--*\n--0\n--*");
	test.parseFile(r);
	test.run(2,1);
	ASSERT_EQ(test.getPopulation(),6);
}

TEST(TestCellClone, cloneFred1)
{
	FredkinCell* p = new  FredkinCell();
	AbstractCell* q = p->clone();
	ASSERT_EQ(p->isStatus(),q->isStatus());
	ASSERT_NE(p,q);	
	delete p;
	delete q;
}

TEST(TestCellClone, cloneFred2)
{
	FredkinCell* p = new  FredkinCell('-');
	AbstractCell* q = p->clone();
	ASSERT_EQ(p->isStatus(),q->isStatus());
	ASSERT_NE(p,q);	
	delete p;
	delete q;
}
TEST(TestCellClone, cloneFred3)
{
	FredkinCell* p = new  FredkinCell('0');
	AbstractCell* q = p->clone();
	ASSERT_EQ(p->isStatus(),q->isStatus());
	ASSERT_NE(p,q);	
	delete p;
	delete q;
}
TEST(TestCellClone, cloneFred4)
{
	FredkinCell* p = new  FredkinCell('+');
	AbstractCell* q = p->clone();
	ASSERT_EQ(p->isStatus(),q->isStatus());
	ASSERT_NE(p,q);	
	delete p;
	delete q;
}
TEST(TestCellClone, cloneCon1)
{
	ConwayCell* p = new  ConwayCell();
	AbstractCell* q = p->clone();
	ASSERT_EQ(p->isStatus(),q->isStatus());
	ASSERT_NE(p,q);	
	delete p;
	delete q;
}
TEST(TestCellClone, cloneCon2)
{
	ConwayCell* p = new  ConwayCell('*');
	AbstractCell* q = p->clone();
	ASSERT_EQ(p->isStatus(),q->isStatus());
	ASSERT_NE(p,q);	
	delete p;
	delete q;
}
TEST(TestCellClone, cloneCon3)
{
	ConwayCell* p = new  ConwayCell('.');
	AbstractCell* q = p->clone();
	ASSERT_EQ(p->isStatus(),q->isStatus());
	ASSERT_NE(p,q);	
	delete p;
	delete q;
}


TEST(TestCellAssignment, CellAssignment1)
{
	Cell p = Cell(new  ConwayCell('.'));
	ASSERT_EQ(p.isStatus(),'.');
	Cell q = Cell(new  ConwayCell('*'));
	p = q;
	ASSERT_EQ(p.isStatus(),'*');
	
}
TEST(TestCellAssignment, CellAssignment2)
{
	Cell p = Cell(new  FredkinCell('-'));
	ASSERT_EQ(p.isStatus(),'-');
	Cell q = Cell(new  FredkinCell('0'));
	p = q;
	ASSERT_EQ(p.isStatus(),'0');
	
}
TEST(TestCellAssignment, CellAssignment3)
{
	Cell p = Cell(new  FredkinCell('-'));
	ASSERT_EQ(p.isStatus(),'-');
	Cell q = Cell(new  ConwayCell('*'));
	p = q;
	ASSERT_EQ(p.isStatus(),'*');
}

TEST(TestAliveNeigh, AliveCon)
{
	Life<ConwayCell> test(3,3);
	istringstream r("\n..*\n.**\n..*");
	test.parseFile(r);
	ASSERT_EQ(test.alive_neighs(0,2),2);
}
TEST(TestCellAssignment, AliveFred)
{
	Life<FredkinCell> test(3,3);
	istringstream r("\n--0\n-00\n--0");
	test.parseFile(r);
	ASSERT_EQ(test.alive_neighs(0,2),1);
}
TEST(TestCellAssignment, AliveCell)
{
	Life<Cell> test(3,3);
	istringstream r("\n-*0\n.00\n-.0");
	test.parseFile(r);
	ASSERT_EQ(test.alive_neighs(0,2),2);
	ASSERT_EQ(test.alive_neighs(0,1),3);
}
TEST(TestLifePopulation, ConCell)
{
	Life<Cell> test(3,3);
	istringstream r("\n.*.\n...\n..*");
	test.parseFile(r);
	ASSERT_EQ(test.getPopulation(),2);
	
}
TEST(TestLifePopulation, FredCell)
{
	Life<Cell> test(3,3);
	istringstream r("\n--0\n-00\n--0");
	test.parseFile(r);
	ASSERT_EQ(test.getPopulation(),4);

}
TEST(TestLifePopulation, Cell)
{
	Life<Cell> test(3,3);
	istringstream r("\n-*0\n.00\n-.0");
	test.parseFile(r);
	ASSERT_EQ(test.getPopulation(),5);

}
TEST(TestIterator, begin)
{
	Life<Cell> l(3,3);
	ASSERT_EQ(l.begin(), l.end());

}
TEST(TestIterator, at)
{
	Life<Cell> test(3,3);
	istringstream r("\n-*0\n.00\n-.0");
	test.parseFile(r);
	ASSERT_EQ(test.at(0).isStatus(),'-');

}

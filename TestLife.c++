#include <algorithm>
#include <sstream>
#include <string>
#include <typeinfo>

#include "gtest/gtest.h"

#include "Life.h"

TEST(TestCellConstructor, con1)
{
	Cell test = Cell('t');
	ASSERT_EQ('t',test.status);
}
TEST(TestCellConstructor, con2)
{
	Cell test = Cell('z');
	ASSERT_EQ('z',test.status);
}
TEST(TestCellConstructor, con3)
{
	Cell test = Cell('s');
	ASSERT_EQ('s',test.status);
}

TEST(TestCellAlive, ali1)
{
	Cell test = Cell('*');
	test.p = new ConwayCell('*');
	ASSERT_TRUE(test.isAlive());
}
TEST(TestCellAlive, ali2)
{
	Cell test = Cell('0');
	test.p = new FredkinCell('0');
	ASSERT_TRUE(test.isAlive());
}
TEST(TestCellAlive, ali3)
{
	Cell test = Cell('.');
	test.p = new ConwayCell('.');
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
	test.p = new ConwayCell('*');
	test.cell_Execute(0);
	ASSERT_EQ(test.isAlive(),false);

}
TEST(TestCellExecute, c_exe2)
{
	Cell test = Cell('.');
	test.p = new ConwayCell('.');
	test.cell_Execute(3);
	ASSERT_EQ(test.isAlive(),true);
}
TEST(TestCellExecute, c_exe3)
{
	Cell test = Cell('-');
	test.p = new FredkinCell('-');
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
	istringstream r("ConwayCell\n2\n2\n1\n1\n..\n..");
	test.parseFile(r);
	ASSERT_EQ(test.cell_type,"ConwayCell");
}
TEST(TestLifeParse, parse2)
{
	Life<ConwayCell> test(2,2);
	istringstream r("ConwayCell\n2\n2\n1\n1\n..\n..");
	test.parseFile(r);
	ASSERT_EQ(test.iterations,1);
}
TEST(TestLifeParse, parse3)
{
	Life<ConwayCell> test(2,2);
	istringstream r("ConwayCell\n2\n2\n1\n1\n..\n..");
	test.parseFile(r);
	ASSERT_EQ(test.num_of_prints,1);
}
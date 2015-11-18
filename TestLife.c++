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
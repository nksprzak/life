#include <cassert>    // assert
#include <cstddef>    // ptrdiff_t, size_t
#include <new>        // bad_alloc, new
#include <stdexcept>  // invalid_argument
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>

class AbstractCell
{

};

class Cell
{

};

class ConwayCell: AbstractCell
{
};

class FredkinCell: AbstractCell
{

};


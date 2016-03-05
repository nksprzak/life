# Conway's Game of Life
This program demonstrates [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway's_Game_of_Life)

# Types of Cells

There are three different Cells that can be on the board, Cell, ConwayCell, and FredkinCell. 

Cells go from one of two states each iteration of the board, alive or dead. 

A ConwayCell goes from alive to dead with it either has 0 or 1 alive neighbors, or more than 3 alive neighbors.

A dead ConwayCell can go to alive only by having exactly 3 neighbors.

Dead = .

Alive = *

Fredkin alive cells die with  0,2, or 4 neighbors and dead cells become alive with 1 or 3 neighbors.

Dead = .

Alive = 1(denotes age of the cell)


# Input 

See RunLife.in 

# Output

See RunLife.out

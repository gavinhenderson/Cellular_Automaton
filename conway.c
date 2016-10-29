
/**************************************************
 * An Implementation of Conway's Game of Life.    *
 *************************************************/

/*
 * David Mayes
 * 150012384
 *
 * Gavin Henderson
 *
 * AC21009
 */

#include <stdio.h>
#include <stlib.h>

#include "cell.h"
#include "conway.h"

/*
 * Creates a grid of cells,
 *
 * (uses rows of CellGroups)
 * Creates 'height' number of cellGroups, with 'width' number of cells in them
 * The groups are linked together.
 */
CellGrid* createCellGrid(int newValues[][], int width, int height)
{

}

/*
 * Frees the memory used by the grid.
 * 
 * Uses deleteCellGroup()
 */
int deleteCellGrid(CellGrid* cell_grid)
{

}

/*
 * Creates the next generation in Conway's Game of Life
 *
 * Generates information from the current generation,
 * deletes it, then creates a new generation using 
 * createCellGrid().
 */
CellGrid* nextConway(CellGrid* cell_grid)
{

}


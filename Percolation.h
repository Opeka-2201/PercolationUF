/* ========================================================================= *
 * Percolation interface:
 * ========================================================================= */

#ifndef _PERCOLATION_H_
#define _PERCOLATION_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct percolation_t Percolation;

/* ------------------------------------------------------------------------- *
 * Create a fully closed percolation grid.
 *
 * PARAMETERS
 * size         The number of cells on a side of the grid
 *
 * NOTE
 * The returned structure should be cleaned with $percFree$ after
 * usage.
 *
 * RETURN
 * perc         The created percolation structure.
 * ------------------------------------------------------------------------- */
Percolation *percCreate(size_t n);

/* ------------------------------------------------------------------------- *
 * Free the memory allocated for the percolation structure.
 *
 * PARAMETERS
 * perc         The percolation structure to free
 * ------------------------------------------------------------------------- */
void percFree(Percolation *perc);

/* ------------------------------------------------------------------------- *
 * Return the size of the percolation grid. If the size is N, the grid is
 * composed N*N cells.
 *
 * PARAMETERS
 * perc         The percolation structure
 *
 * RETURN
 * size         The size of percolation grid
 * ------------------------------------------------------------------------- */
size_t percSize(const Percolation *perc);

/* ------------------------------------------------------------------------- *
 * Open a cell in the percolation grid.
 *
 * PARAMETERS
 * perc         The percolation structure
 * row          The row index
 * col          The column index
 * ------------------------------------------------------------------------- */
void percOpenCell(Percolation *perc, size_t row, size_t col);

/* ------------------------------------------------------------------------- *
 * Check whether a cell in the percolation grid is opened.
 *
 * PARAMETERS
 * perc         The percolation structure
 * row          The row index
 * col          The column index
 *
 * RETURN
 * opened       True if the cell is open, false otherwise
 * ------------------------------------------------------------------------- */
bool percIsCellOpen(const Percolation *perc, size_t row, size_t col);

/* ------------------------------------------------------------------------- *
 * Check whether a cell in the percolation grid is full: there is a path
 * between this cell and an opened cell at the top of the grid.
 *
 * PARAMETERS
 * perc         The percolation structure
 * row          The row index
 * col          The column index
 *
 * RETURN
 * full         True if the cell is full, false otherwise
 * ------------------------------------------------------------------------- */
bool percIsCellFull(const Percolation *perc, size_t row, size_t col);

/* ------------------------------------------------------------------------- *
 * Check whether the grid percolations: there is an path of opened cells from 
 * the top to the bottom of the grid.
 *
 * PARAMETERS
 * perc         The percolation structure
 *
 * RETURN
 * percolates   True if the grid percolations, false otherwise.
 * ------------------------------------------------------------------------- */
bool percPercolates(const Percolation *perc);

/* ------------------------------------------------------------------------- *
 * Print the percolation grid to the given stream $out$. 
 *
 * PARAMETERS
 * perc         The percolation structure
 * out          File descriptor where to write the maze.
 * ------------------------------------------------------------------------- */
void percPrint(const Percolation *perc, FILE* out);

#endif  // _PERCOLATION_H_

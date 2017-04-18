/**
 * @author Nikita Marinosyan
 * @date 11.04.2017
 * Higher School of Economics,
 * Faculty of Computer Science
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>

#include "grid.h"

// According to new restrictions of C++ standards, an explicit definition of static consts is a need
const bool grid::NOT_INFECTED = false;
const bool grid::INFECTED = true;
const int  grid::NOT_VISITED = -1;

// Students may need to alter the constructor
grid::grid(const std::string& fileName)
{
  
    std::ifstream grid_file;

    try
    {
        grid_file.open(fileName.c_str());

        // check if it's all ok
        if (!grid_file.good())
            throw std::runtime_error("File cannot be open");

        // opened correctly
        grid_file >> _rows;
        grid_file >> _cols;

        _area = new std::vector<bool>(_rows * _cols, grid::NOT_INFECTED);
        // Mark all not infected cells as unvisited
        _visited = new std::vector<int>(_rows * _cols, grid::NOT_VISITED);

        _lastCalled = -1; // Nothing was called yet

        int blob_row;
        int blob_col;

        while (!grid_file.eof() && grid_file.good())
        {
            grid_file >> blob_row;
            grid_file >> blob_col;

            _area->operator[](indexof(blob_row, blob_col)) = INFECTED;
        }
    }
    catch (...)
    {
        // always tries to properly close the file!
        grid_file.close();
        throw;              // dispatch further
    }
  
    grid_file.close();
}

// Students may need to alter the destructor
grid::~grid () 
{
  delete _area;
  delete _visited;
}


// Students will need to alter this function to display the
// plus signs (+) next to the cells that belong to
// a counted colony.
std::ostream& operator << (std::ostream& stream, const grid& ob)
{
    for (int _row = 0; _row < ob._rows; ++_row)
    {     
        for (int _col = 0; _col < ob._cols; _col++)
        {
            // Print 1 if infected, 0 if not
            stream << ob._area->operator[](ob.indexof(_row, _col));

            // Print + near the cell value if it
            // belongs to the colony we search for
            if ((ob._visited->operator[](ob._lastCalled) == ob._visited->operator[](ob.indexof(_row, _col)))
                    && ob.infected(_row, _col))
                stream << "+  ";
            else
                stream << "   ";

        }

        stream << std::endl;
    }

    stream << std::endl;
    
    return stream;
}

// Students have to replace the return statement in this function with their
// recursive implementation of this method */
int grid::count (int row, int col)
{
    // Check if the cell is:
    // not infected, visited or out of bounds
    if (!checkIndex(row, col) || !infected(row, col) || _visited->operator[](indexof(row, col)) > NOT_VISITED)
        // If so, we do not need to increment count
        return 0;

    // We mark all cells with the ordering
    // number of the colony they belong to
    _visited->operator[](indexof(row, col)) = (int) _calculated.size();

    return
            count(row - 1, col - 1) +
            count(row - 1, col)     +
            count(row - 1, col + 1) +
            count(row, col - 1)     +
            count(row, col + 1)     +
            count(row + 1, col - 1) +
            count(row + 1, col)     +
            count(row + 1, col + 1) +
            1; // Current cell
}


// Students may need to alter this function
int grid::getCount (int row, int col)
{
    // Remember the index
    // of the last called cell
    _lastCalled = indexof(row, col);

    // Get the index of the colony
    int colonyIndex = _visited->operator[](_lastCalled);
    // If this cell has not been visited,
    // we must generate new key for the colony
    if (colonyIndex == -1)
        colonyIndex = (int) _calculated.size();

    if (_calculated.find(colonyIndex) != _calculated.end())
        // If so, the size of the colony
        // has been already calculated
        return _calculated[colonyIndex];

    // Otherwise, calculate
    // the size of the colony,
    // record it and return
    _calculated[colonyIndex] = count(row, col);
    return _calculated[colonyIndex];
}

// Students do not need to alter function indexof.
int grid::indexof(int row, int col) const
{
    if (!checkIndex(row, col))
        throw std::invalid_argument("Index out of range");

    return row *_cols + col;
}

// Students do not need to alter function infected.
bool grid::infected(int row, int col) const 
{
    return (_area->operator[](indexof(row, col)) == INFECTED);
}


// Students do not need to alter this function w/o any special reasons.
bool grid::checkIndex(int row, int col) const
{
    return !(row >= _rows || row < 0 || col >= _cols || col < 0);
}

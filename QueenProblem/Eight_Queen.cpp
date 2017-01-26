//
// Created by Nikita Marinosyan on 19.10.16.
//

#include "eight_queen.h"
#include <stdexcept>
#include <cstdlib>

using namespace std;

bool QueenProblem::isInserted(int queen_row, int queen_col) {

    // Check the
    // current row
    for (int j = 0; j < queen_col; ++j) {
        if(board[queen_row][j] == 1) {
            // The queen can't be
            // placed in this cell
            return false;
        }
    }

    for (int j = queen_col+1; j <size; ++j) {
        if(board[queen_row][j] == 1) {
            // The queen can't be
            // placed in this cell
            return false;
        }
    }

    // Check the upper
    // left diagonal
    for (int i = queen_row, j = queen_col; i > -1 && j > -1; --i, --j) {
        if(board[i][j] == 1) {
            // The queen can't be
            // placed in this cell
            return false;
        }
    }

    // Check the lower
    // left diagonal
    for (int i = queen_row, j = queen_col; i < size && j > -1; ++i, --j) {
        if(board[i][j] == 1) {
            // The queen can't be
            // placed in this cell
            return false;
        }
    }

    // Check the upper
    // right diagonal
    for (int i = queen_row, j = queen_col; i > -1 && j < size; --i, ++j) {
        if(board[i][j] == 1) {
            // The queen can't be
            // placed in this cell
            return false;
        }
    }

    // Check the upper
    // right diagonal
    for (int i = queen_row, j = queen_col; i < size && j < size; ++i, ++j) {
        if(board[i][j] == 1) {
            // The queen can't be
            // placed in this cell
            return false;
        }
    }

    // The queen can be
    // placed in this cell
    return true;
}

void QueenProblem::initialize(const int size) {

    if(isInitialized()) {
        // Clear memory
        for (int i = 0; i < size; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }

    numberOfSolutions = 0;
    this->size = size;

    // Initialize the
    // two-dimensional array
    board = new int*[size];
    for(int i = 0; i < size; ++i)
        board[i] = new int[size];

    // Fill in the array
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            board[i][j] = 42; // The meaning of life
        }
    }

    // Mark the array as initialized
    initialized = true;
}

bool QueenProblem::isInitialized() {
    return initialized;
}

bool QueenProblem::isSolved() {
    return solved;
}

long QueenProblem::getNumberOfSolutions(){

    if(!isSolved()) {
        throw std::logic_error("Error!");
    }
    return numberOfSolutions;
}

void QueenProblem::backtracking(int queen) {

    // Check if the method was
    // called after initialization
    if (isInitialized() && (size > 0)) {

        if (size == 1){
            // There is only one
            // solution to the problem
            numberOfSolutions = 1;
            solved = true;
            return;
        }
        // Check if the task has
        // a solution
        if (size > 1 && size < 4) {
            solved = true;
            return;
        } else {
            if (queen == size) {
                // Increment the number
                // of solutions
                ++numberOfSolutions;

                // Mark the task
                // as solved
                solved = true;

                return;
            }

            for (int currentRow = 0; currentRow < size; ++currentRow) {

                // Check if placing a
                // queen here is safe
                if (isInserted(currentRow, queen)) {

                    // Mark the current
                    // cell as reserved
                    board[currentRow][queen] = 1;

                    // Find a proper cell
                    // for the next queen
                    backtracking(queen + 1);

                    // Mark the cell as free
                    // because the solution
                    // didn't work if this code
                    // is reached
                    board[currentRow][queen] = 42;
                }
            }
            return;
        }
    } else {
        throw std::logic_error("Error!");
    }
}

QueenProblem::~QueenProblem() {

    // Clear memory
    for (int i = 0; i < size; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

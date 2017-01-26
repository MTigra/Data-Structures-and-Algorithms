#include <iostream>
#include "eight_queen.h"

using namespace std;
int main()
{
    QueenProblem qp;
    for (int i = 1; i < 9; ++i) {
        qp.initialize(i);
        qp.backtracking(0);
        std::cout<< i << " queens: " << qp.getNumberOfSolutions() << " solutions: " << " solved: " << qp.isSolved() << "\n";
    }
    return 0;
}


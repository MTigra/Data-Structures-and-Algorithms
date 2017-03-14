//
// Created by Nikita on 18.11.16.
//

#include "SCCSolver.h"
#include <cstdlib>
#include <stdexcept>

using namespace std;

Vertice::Vertice(int id) {

    // Set the id value
    this->id = id;
}

bool Vertice::compare(Vertice *v1, Vertice *v2) {

    // Return bool value whether finished step
    // of the first value is greater than the second one
    return (*v2).finished_step < (*v1).finished_step;
}

void Vertice::refresh() {

    // Set default values
    discovered_step == -1;
    finished_step == -1;
    passed == false;
}

bool SCCSolver::isInitialized() {
    return initialized;
}

bool SCCSolver::isSolved() {
    return solved;
}

std::vector<std::vector<int>> SCCSolver::getResult() {

    if (isSolved()) {
        return result;
    } else {
        throw logic_error("No solution found yet!");
    }
}

void SCCSolver::initialize(std::vector<int> *adjList, int n) {

    // Make sure adjacencyList does not point
    // to 'null' and vertPool isn't empty
    if (adjacencyList == nullptr && vertPool.size() == 0) {
        // All good
        initialize(adjList, n);
}
    else {

        // Clear them if at least
        // one of them is not 'empty'
        delete[] adjacencyList;
        for (vector<Vertice*>::iterator i = vertPool.begin(); i != vertPool.end(); ++i) {
            delete *i;
        }
        vertPool.clear();

        //
        initialize(adjList, n);
    }
}
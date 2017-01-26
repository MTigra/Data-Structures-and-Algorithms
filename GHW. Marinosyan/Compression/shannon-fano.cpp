//
// Created by Nikita Marinosyan on 01.12.16.
//

#include <algorithm>
#include "shannon-fano.h"

SFVertex::SFVertex(char character, int frequency) {
    this->character = character;
    this->frequency = frequency;
    code = "";
    operations += 3;
}

vector<SFVertex> createSFVector(map<char, int> from){

    // Create vector which will be
    // containing vertices of the tree
    vector<SFVertex> tree;

    map<char, int>::iterator current_vertex;
    // Copy data from map to the vector
    for (current_vertex = from.begin(); current_vertex != from.end(); ++current_vertex) {

        // Copy current vertex
        SFVertex vertex = SFVertex(current_vertex->first, current_vertex->second);

        // Add the vertex to
        // the end of the list
        tree.push_back(vertex);
        operations += 5;
    }
    operations += 1;
    return tree;
}

void buildTree(vector<SFVertex> &tree, unsigned int left, unsigned int right) {

    // Check if there is
    // only 1 symbol left
    if (left == right) {
        return;
    }
    operations += 1;

    // Check if there are
    // only 2 symbols left
    if ( left + 1 == right) {
        tree.at(left).code += "0";
        tree.at(right).code += "1";
        operations += 2;
        return;
    }
    operations += 2;

    // Create variables to control
    // the indices of the tree vertices
    unsigned int high = left;
    unsigned int low = right;

    // Create variables to control
    // sums of frequencies
    int sh = tree.at(high).frequency;
    int sl = tree.at(low).frequency;
    operations += 4;

    // Find the partition point
    while (high + 1 != low) {

        // Decide which sum of
        // frequencies is greater
        if (sl < sh) {

            // Switch to the
            // next character
            --low;

            // Increase frequency sum
            // of the right part
            sl += tree.at(low).frequency;
        }
        else {
            // Switch to the
            // next character
            ++high;

            // Increase frequency sum
            // of the left part
            sh += tree.at(high).frequency;
        }
        operations += 5;
    }

    // After the partition point is found
    // we need to add a bit to the byte
    // codes of every character
    for (int i = left; i <= high; ++i) {
        tree.at(i).code += "0";
        operations += 3;
    }
    for (int j = low; j <= right; ++j) {
        tree.at(j).code += "1";
        operations += 3;
    }
    operations += 2;

    // Launch recursion of
    // the the subtrees
    buildTree(tree, left, high);
    buildTree(tree, low, right);
    operations += 2;
}

map<char, string> sf_coding(map<char, int> frequencies) {

    // Create vector which will be
    // containing vertices of the tree
    vector<SFVertex> tree = createSFVector(frequencies);

    // Build a binary tree
    // if the file is not empty
    if (tree.size() != 0) {
        // Sort the tree
        // in descending order
        sort(tree.begin(), tree.end(),
             [](SFVertex a, SFVertex b) -> bool {
                 return a.frequency > b.frequency;
             });

        // Actually build a tree
        buildTree(tree, 0, tree.size() - 1);
        operations += 4;
    }

    // Create map which will be
    // containing binary codes of
    // each character
    map<char, string> codes;
    fillSFCodeTable(codes, tree);
    operations += 2;

    // Return the table
    // of binary codes
    return codes;
}

void sf_compression(string ipath, string opath){

    // Create variable to store
    // the amount of characters
    // in the input file
    unsigned int length = 0;

    // Create binary codes table
    map<char, string> codes = sf_coding(getFrequencyMap(ipath, length));

    // Compress the file
    compressFile(codes, length, ipath, opath);

    operations += 5;
}

void fillSFCodeTable(map<char, string> &table, vector<SFVertex> codes) {
    for (int i = 0; i < codes.size(); ++i) {
        table[codes[i].character] = codes[i].code;
        operations += 3;
    }
    operations += 1;
}
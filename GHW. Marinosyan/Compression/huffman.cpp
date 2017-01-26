//
// Created by Nikita Marinosyan on 30.11.16.
//

#include <algorithm>
#include "huffman.h"

vector<HuffmanVertex*> createHuffmanVector(map<char, int> from) {
    vector<HuffmanVertex*> tree;
    map<char, int>::iterator current_vertex;
    // Copy data from map to the vector
    for (current_vertex = from.begin(); current_vertex != from.end(); ++current_vertex) {

        // Copy current vertex
        // to the pointer
        HuffmanVertex* vertex = new HuffmanVertex(current_vertex->first, current_vertex->second);

        // Add the vertex to
        // the end of the list
        tree.push_back(vertex);
        operations += 5;
    }
    operations += 1;
    return tree;
}

void fillHuffmanCodeTable(map<char, string> &table, HuffmanVertex* root, string &code) {

    // Check if there is the left child
    if (root->left_node) {
        // Go deeper in left the tree
        code += "0";
        fillHuffmanCodeTable(table, root->left_node, code);
        operations += 2;
    }
    if (root->right_node) {
        // Go deeper in the right subtree
        code += "1";
        fillHuffmanCodeTable(table, root->right_node, code);
        operations += 2;
    }
    operations += 2;

    if (root->character != '\0') {
        // Make a record about
        // this character bin code
        table[root->character] = code;
        operations += 1;
    }
    operations += 1;

    // Check if the erasing is possible
    if(code.length() > 0) {
        // Go up and delete the
        // last bit from the code
        code.erase(code.length()-1);
        operations += 1;
    }
    operations += 1;
}

HuffmanVertex::HuffmanVertex(char c, int v) {
    // Set default values
    left_node = nullptr;
    right_node = nullptr;

    // Initialize fields
    character = c;
    frequency = v;

    operations += 4;
}

HuffmanVertex::HuffmanVertex(HuffmanVertex* left, HuffmanVertex* right) {
    // Set pointers to
    // the children
    left_node = left;
    right_node = right;
    character = '\0';

    // Set frequency by summing
    // values of both children
    frequency = left->frequency + right->frequency;

    operations += 4;
}

void memClear(HuffmanVertex* v) {
    if (v == nullptr) {
        operations += 2;
        return;
    }
    memClear(v->left_node);
    memClear(v->right_node);
    delete v;
    operations += 5;
}

map<char, string> huffman_coding(map<char, int> frequencies) {

    // Create vector which will be
    // containing vertices of the tree
    vector<HuffmanVertex*> tree = createHuffmanVector(frequencies);

    // Create map which will be
    // containing binary codes of
    // each character
    map<char, string> codes;

    if (tree.size() != 0) {
        while (tree.size() > 1) {
            // Sort in descending order
            // to determine two smallest
            // by frequency vertices

            sort(tree.begin(), tree.end(),
                 [](HuffmanVertex *a, HuffmanVertex *b) -> bool {
                     return a->frequency > b->frequency;
                 });

            // Create new vertex by merging two
            // smallest by frequency vertices
            HuffmanVertex *new_vertex = new HuffmanVertex(tree[tree.size() - 1], tree[tree.size() - 2]);

            // Remove children
            // from the vector
            tree.pop_back();
            tree.pop_back();

            // Add new vertex to the vector
            tree.push_back(new_vertex);

            operations += 9;
        }

        // Create root of the tree
        HuffmanVertex *root = tree.back();

        // Fill in the map which will be
        // containing binary codes of
        // each character
        string code = "";
        fillHuffmanCodeTable(codes, root, code);

        // Clear the memory
        memClear(root);
        operations += 4;
    }
    operations += 2;
    // Return the table
    // of binary codes
    return codes;
}

void huffman_compression(string ipath, string opath) {

    // Create variable to store
    // the amount of characters
    // in the input file
    unsigned int length = 0;

    // Create binary codes table
    map<char, string> codes = huffman_coding(getFrequencyMap(ipath, length));

    // Create a compressed file
    compressFile(codes, length, ipath, opath);

    operations += 5;
}
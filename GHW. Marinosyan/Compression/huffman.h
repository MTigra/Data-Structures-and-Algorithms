//
// Created by Nikita Marinosyan on 30.11.16.
//
#pragma once

#include "utilities.h"

/*
 * Class which represents
 * a vertex of Huffman
 * binary tree
 */
class HuffmanVertex {

public:
    // Constructor merging
    // two vertices
    HuffmanVertex(HuffmanVertex* left, HuffmanVertex* right);

    // Constructor for
    // creating single vertex
    HuffmanVertex(char c, int v);

    // Value of the vertex
    int frequency;

    // Character containing
    // in the vertex
    char character;

    // Pointers to the children
    HuffmanVertex* left_node;
    HuffmanVertex* right_node;
};

/**
 * Utility method
 * to clear the memory
 */
void memClear(HuffmanVertex* v);

/**
 * Utility method to copy
 * data from map to vector
 * @param from - map containig source data
 * @return vector containing the same data
 */
vector<HuffmanVertex*> createHuffmanVector(map<char, int> from);

/**
 * Utility method to create
 * binary codes table
 * @param tree - binary tree
 * @return - table of codes for each character
 */
void fillHuffmanCodeTable(map<char, string> &table, HuffmanVertex* root, string &code);

/**
 * Method used to create
 * binary codes table based
 * on Huffman algorithm
 * @param frequencies - table of frequencies
 * @return table of binary codes for each character
 */
map<char, string> huffman_coding(map<char, int> frequencies);

/**
 * Main method to do the compression
 * based on Huffman algorithm
 * @param path - path to the file which
 * should be compressed
 */
void huffman_compression(string ipath, string opath);
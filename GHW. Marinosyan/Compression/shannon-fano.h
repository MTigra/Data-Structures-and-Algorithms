//
// Created by Nikita Marinosyan on 01.12.16.
//

#pragma once

#include "utilities.h"

/*
 * Class which represents
 * a vertex of Shannon-Fano
 * binary tree
 */
class SFVertex {

public:
    // Variable to store
    // the character containing
    // in this vertex
    char character;

    // Variable to store
    // the frequency of the
    // character containing
    // in this vertex
    int frequency;

    // Variable to store
    // the binary code of the
    // character containining
    // in this vertex
    string code;

    // Constructor
    SFVertex(char character, int frequency);
};

/**
 * Method used to create
 * binary codes table based
 * on Shannon-Fano algorithm
 * @param frequencies - table of frequencies
 * @return table of binary codes for each character
 */
map<char, string> sf_coding(map<char, int> frequencies);

/**
 * Main method to do the compression
 * based on Shannon-Fano  algorithm
 * @param path - path to the file which
 * should be compressed
 */
void sf_compression(string ipath, string opath);

/**
 * Utility method to copy
 * data from map to vector
 * @param from - map containig source data
 * @return vector containing the same data
 */
vector<SFVertex> createSFVector(map<char, int> from);

/*
 * Recursive method which
 * builds the binary tree by
 * implementing Shannon-Fano algorithm
 */
void buildTree(vector<SFVertex> &tree, unsigned int left, unsigned int right);

/**
 * Main method to do the compression
 * based on Shannon-Fano algorithm
 * @param path - path to the file which
 * should be compressed
 */
void fillSFCodeTable(map<char, string> &table, vector<SFVertex> codes);

/**
 * Method used to create
 * binary codes table based
 * on Shannon-Fano algorithm
 * @param frequencies - table of frequencies
 * @return table of binary codes for each character
 */
map<char, string> sf_coding(map<char, int> frequencies);
//
// Created by Nikita Marinosyan on 29.11.16.
//
#pragma once

#include <map>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/**
 * Utility method to calculate the
 * frequency of each character in
 * the input file
 * @param path - path to the input file
 * @return - map of frequencies
 */
map<char, int> getFrequencyMap(string path, unsigned int &length);

/**
 * Utility method to
 * create compressed file
 */
void compressFile(map<char, string> codes, unsigned int length, string ipath, string opath);

/**
 * Utility method to
 * decompress file
 */
void decompressFile(string ipath, string opath);

/*
 * Global variable to calculate
 * the amount of elementary operations
 */
extern long operations;
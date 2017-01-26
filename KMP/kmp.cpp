//
// Created by Nikita Marinosyan on 08.12.16.
//

#include <cstdlib>
#include "kmp.h"

using namespace std;

/*
 * Utility method to create
 * prefix table of the pattern
 */
vector<int> createPrefixTable(string substring) {

    // Create vector with
    // 0 values by default
    vector<int> prefix_table(substring.length());

    int q = 0;

    // First element has
    // no suffixes or prefixes
    // so the loop starts with
    // the second element
    for (int k = 1; k < substring.length(); ++k){

        while(substring[k] != substring[q] && q > 0) {
            q = prefix_table[q - 1];
        }

        if (substring[k] == substring[q]) {
            ++q;
        }

        prefix_table[k] = q;
    }

    return prefix_table;
}

/*
 * Utility method to create an improved
 * prefix table in order to minimize the amount
 * of operations as well as complexity
 */
vector<int> brs(vector<int> prefix_table, string substring) {

    vector<int> brs(substring.length());

    for (int i = 1; i < prefix_table.size(); ++i) {
        if (substring[prefix_table[i]] == substring[i+1]) {
            brs[i] = brs[prefix_table[i-1]];
        }
        else {
            brs[i] = prefix_table[i];
        }
    }

    return brs;
}

std::vector<int>* find_substrings(std::string& source, std::string& substring) {

    // Create a pointer to integer values vector
    // which should contain all values of indices
    // of starts of passed substring
    vector<int>* indices = new vector<int>();

    int q = 0;

    // Create the prefix table which will help
    // us to search the substring with less complexity
    vector<int> prefix_table = brs(createPrefixTable(substring), substring);

    // Find the substrings
    for (int i = 0; i < source.length(); ++i){

        while ((q > 0) && (substring[q] != source[i])) {
            q = prefix_table[q - 1];
        }

        // Increment q in
        // case of the match
        if (substring[q] == source[i])
            q++;

        // If k equals to substring length
        // we need to set its value to zero
        if (q == substring.length()) {
            // Or continue the search
            indices->push_back(i - substring.length() + 1);
            q = 0;
        }
    }

    // Return the pointer
    // to the result vector
    return indices;
}

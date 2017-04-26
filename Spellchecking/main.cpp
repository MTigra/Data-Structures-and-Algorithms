/**
 * @author Nikita Marinosyan
 * @date 26.04.2017
 * Higher School of Economics,
 * Faculty of Computer Science
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <algorithm>

#include "dictionary.h"

using namespace std;

void lower(string& s);
string stripPunct(const string& s);
void checkSpelling(ifstream& in, Dictionary& dict);

string swapWithNext(string misspelled, size_t i);
string eraseCharacter(string misspelled, size_t i);
string replaceCharacter(string misspelled, size_t toBeReplaced, char replacing);
string insertCharacter(string misspelled, size_t placeToInsertBefore, char toBeInserted);

void suggestTransposing(string misspelled, Dictionary& dict, HashSet<string, hash_function, equality>& suggestions);
void suggestRemoval(string misspelled, Dictionary& dict, HashSet<string, hash_function, equality>& suggestions);
void suggestReplacement(string misspelled, Dictionary& dict, HashSet<string, hash_function, equality>& suggestions);
void suggestInserting(string misspelled, Dictionary& dict, HashSet<string, hash_function, equality>& suggestions);


int main(int argc, char* argv[]) 
{
	// Output usage message if improper command line args were given.
	if (argc != 3)
    {
		cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
		return EXIT_FAILURE;
	}

	ifstream inf(argv[2]);
	if (! inf) 
    {
		cerr << "Could not open " << argv[2] << "\n";
		return EXIT_FAILURE;
	}

	// Read dictionary, but let user know what we are working on.
	cout << "Loading dictionary, this may take awhile...\n";

	Dictionary d(argv[1]);

	checkSpelling(inf, d);

	inf.close();

	return EXIT_SUCCESS;
}

void checkSpelling(ifstream& in, Dictionary& dict) 
{
	int line_number = 0;
	while (in) 
    {
		++line_number;

		string line;
		getline(in, line);

  	    stringstream ss (stringstream::in | stringstream::out);
		ss << line;

		string word;
		while (ss >> word)
        {
			// Ensure the word is
			// written in lowercase
			lower(word);

			// Ensure there is no
			// trailing punctuation character
			word = stripPunct(word);

			// If the word does not exits
			// So, it is misspelled
			if (!dict.search(word))
			{
				// Create hash set to control
				// the duplication of suggestions
				HashSet<string, hash_function, equality> suggestions;

				// Output the suggestions header
				cout << "line " << line_number << ": '" << word << "'" << endl;
				cout << "        suggestions:" << endl;

				suggestTransposing(word, dict, suggestions);
				suggestRemoval(word, dict, suggestions);
				suggestReplacement(word, dict, suggestions);
				suggestInserting(word, dict, suggestions);
			}
		}
	}
}

/*
 * Utility method to swap
 * adjacent characters
 */
string swapWithNext(string misspelled, size_t i)
{
	swap(misspelled[i], misspelled[i + 1]);
	return misspelled;
}

/*
 * Method to find the suggestions
 * by transposing adjacent characters
 */
void suggestTransposing(string misspelled, Dictionary& dict, HashSet<string, hash_function, equality>& suggestions)
{
	for (size_t i = 0; i < misspelled.length() - 1; ++i)
	{
		string suggestion = swapWithNext(misspelled, i);
		if (dict.search(suggestion))
		{
			// Check if the word
			// was not suggested yet
			if (!suggestions.search(suggestion))
			{
				// Add it to the suggestions
				suggestions.insert(suggestion);

				// Output the new suggestion
				cout << "                " << suggestion << endl;
			}
		}
	}
}

/*
 * Utility method to erase
 * one character from the word
 */
string eraseCharacter(string misspelled, size_t i)
{
	return misspelled.erase(i, 1);
}

/*
 * Method to find the suggestions
 * by removing one character from the word
 */
void suggestRemoval(string misspelled, Dictionary& dict, HashSet<string, hash_function, equality>& suggestions)
{
	for (size_t i = 0; i < misspelled.length(); ++i)
	{
		string suggestion = eraseCharacter(misspelled, i);
		if (dict.search(suggestion))
		{
            // Check if the word
            // was not suggested yet
            if (!suggestions.search(suggestion))
            {
                // Add it to the suggestions
                suggestions.insert(suggestion);

                // Output the new suggestion
                cout << "                " << suggestion << endl;
            }
		}
	}
}

/*
 * Utility method to replace
 * one character with another
 */
string replaceCharacter(string misspelled, size_t toBeReplaced, char replacing)
{
    return misspelled.replace(toBeReplaced, 1, 1, replacing);
}

/*
 * Method to find the suggestions
 * by replacing the characters
 */
void suggestReplacement(string misspelled, Dictionary& dict, HashSet<string, hash_function, equality>& suggestions)
{
    for (size_t i = 0; i < misspelled.length(); ++i)
    {
        for (char c = 'a'; c <= 'z'; ++c)
        {
            string suggestion = replaceCharacter(misspelled, i, c);
            if (dict.search(suggestion))
            {
                // Check if the word
                // was not suggested yet
                if (!suggestions.search(suggestion))
                {
                    // Add it to the suggestions
                    suggestions.insert(suggestion);

                    // Output the new suggestion
                    cout << "                " << suggestion << endl;
                }
            }
        }
    }
}

/*
 * Utility method to insert
 * one character into the word
 */
string insertCharacter(string misspelled, size_t placeToInsertBefore, char toBeInserted)
{
    return misspelled.insert(placeToInsertBefore, 1, toBeInserted);
}

/*
 * Method to find the suggestions
 * by inserting the characters
 */
void suggestInserting(string misspelled, Dictionary& dict, HashSet<string, hash_function, equality>& suggestions)
{
    for (size_t i = 0; i <= misspelled.length(); ++i)
    {
        for (char c = 'a'; c <= 'z'; ++c)
        {
            string suggestion = insertCharacter(misspelled, i, c);
            if (dict.search(suggestion))
            {
                // Check if the word
                // was not suggested yet
                if (!suggestions.search(suggestion))
                {
                    // Add it to the suggestions
                    suggestions.insert(suggestion);

                    // Output the new suggestion
                    cout << "                " << suggestion << endl;
                }
            }
        }
    }
}

void lower(string& s) 
{
    // Ensures that a word is lowercase
	for (int i = 0; i < s.length(); ++i)
		s[i] = (char) tolower(s[i]);
}

string stripPunct(const string& s) 
{
	// Remove any single trailing
	// punctuation character from a word.  
	if (ispunct(s[s.length() - 1])) 
		return s.substr (0, s.length() - 1);
	
    return s;
}

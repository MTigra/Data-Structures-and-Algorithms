////////////////////////////////////////////////////////////////////////////////
// Module Name:  main.cpp
// Authors:      Nikita Marinosyan, Leonid Dworzanski, Sergey Shershakov
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
//#include <string>
//#include <cstdlib>

//#include "linked_list.h"
#include "dna_element.h"

using namespace std;

// TODO: укажите здесь абсолютный путь к файлу с кусочками ДНК для восстановления
static const char* INP_FILENAME = "res/test1";

int main (int argc, char* argv[])
{
    /*try{
        DNARepairer dnarepairer;

        dnarepairer.readFile(INP_FILENAME);


        cout << "Broken DNAs" << endl;
        dnarepairer.printDNAStorage();

        dnarepairer.repairDNA();

        cout << "\nGood as it is" << endl;
        dnarepairer.printDNAStorage();
    }
    catch(exception &e) {
        cout << e.what();
    }
    catch (...){
        cout << "Something wrong happend." << endl;
    }
    cout << endl;

    */;
    DNAElement* element = new DNAElement("a1:G");
    cout << element->base;
    return EXIT_SUCCESS;
}


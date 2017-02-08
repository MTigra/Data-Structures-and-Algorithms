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
#include "linked_list.h"

using namespace std;

// TODO: укажите здесь абсолютный путь к файлу с кусочками ДНК для восстановления
static const char* INP_FILENAME = "res/test1";

using namespace xi;

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
    DNAElement* element = new DNAElement();
    cout << (char)element->base;

    LinkedList<int> mylist {};
    int data[] = {0, 1, 2, 3, 4, 5};
    mylist.addElementToEnd(data[0]);
    mylist.addElementToEnd(data[1]);
    mylist.addElementToEnd(data[2]);
    mylist.addElementToEnd(data[3]);
    mylist.addElementToEnd(data[4]);
    mylist.addElementToEnd(data[5]);
    LinkedList<int> other {mylist};
    other.deleteNodes(other.getPreHead(), other.getPreHead()->next);
    other.deleteNodes(other.getPreHead(), other.getPreHead()->next->next);

    LinkedList<int> blabla{};
    blabla.addElementToEnd(data[5]);
    //printLinkedList(blabla, "New small list. BLABLA");
    blabla = other;
    //printLinkedList(blabla, "After Copy assignement = from other. BLABLA");
    //printLinkedList(other, "Doing a copy assignement from here. OTHER");
    blabla.moveNodeToEnd(mylist.getPreHead()->next);
    //printLinkedList(blabla, "After adding one element to blabla from mylist, should be = 1");
    blabla.moveNodesAfter(other.getPreHead()->next->next, blabla.getPreHead()->next, blabla.getPreHead()->next->next->next);
    //printLinkedList(blabla, "After moved some nodes from blabla into other. BLABLA");
    //printLinkedList(other, "After moved some nodes from blabla into other. OTHER");
    blabla.moveNodesToEnd(other.getPreHead(), other.getLastNode());
    //printLinkedList(blabla, "After moving all nodes from other to blabla's end. BLABLA");
    //printLinkedList(other, "After moving all nodes from other to blabla's end. OTHER");
    //printLinkedList(mylist, "Almost unchanged. MYLIST");

    cout << mylist[0] << endl;
    cout<< mylist[1] << endl;
 cout<< mylist[2] << endl;
    cout<< "Size: "<< mylist.size() << endl;
    cout<< mylist[ mylist.size() - 1] << endl;

    cout << other.getPreHead()->value << mylist.getPreHead()->value << blabla.getPreHead()->value;
    return EXIT_SUCCESS;
}


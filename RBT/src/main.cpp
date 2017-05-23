////////////////////////////////////////////////////////////////////////////////
// Module Name:  main.cpp
// Authors:      Sergey Shershakov
// Version:      0.1.0
// Date:         01.05.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "rbtree.h"
#include "def_dumper.h"

using namespace std;


void simplestTest()
{
    using namespace xi;

    // просто создаем объект дерева
    RBTree<int> tree1;
    tree1.setDumper(new RBTreeDefDumper<int, std::less<int> >("/Users/Nikita_Marinosyan/Desktop/BRT/scripts/log.txt",
                                                              "/Users/Nikita_Marinosyan/Desktop/BRT/scripts/"));
    tree1.insert(4);
    tree1.insert(5);
    tree1.insert(6);
}


int main()
{
    cout << "Hello, World!" << endl;

    simplestTest();

    return 0;
}
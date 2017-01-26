#include <iostream>
#include <string>
#include <functional>
#include <stdexcept>
#include "binary_tree.h"

using namespace std;

string s;

int log(int v)
{
    s += to_string(v) + " ";
    return 0;
}

void test1()
{
    BinaryTree<int> tree;
    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(12, 12);
    tree.insert(2, 2);
    tree.insert(6, 6);
    s = "";
    tree.Traverse(log);
    if (s != "2 5 6 10 12 ") throw exception();
}

void test2()
{
    BinaryTree<int> tree;
    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(12, 12);
    tree.insert(2, 2);
    tree.insert(6, 6);
    tree.remove(5);
    s = "";
    tree.Traverse(log);
    if (s != "2 6 10 12 ") throw exception();
}

void test3()
{
    BinaryTree<int> tree;
    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(12, 12);
    tree.insert(2, 2);
    tree.insert(6, 6);
    tree.remove(10);
    s = "";
    tree.Traverse(log);
    if (s != "2 5 6 12 ") throw exception();
}

void test4()
{
    BinaryTree<int> tree;
    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(12, 12);
    tree.insert(2, 2);
    tree.insert(6, 6);
    tree.remove(2);
    s = "";
    tree.Traverse(log);
    if (s != "5 6 10 12 ") throw exception();
}

void test5()
{
    BinaryTree<int> tree;
    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(12, 12);
    tree.insert(2, 2);
    tree.insert(6, 6);
    tree.remove(6);
    s = "";
    tree.Traverse(log);
    if (s != "2 5 10 12 ") throw exception();
}

void test6()
{
    BinaryTree<int> tree;
    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(12, 12);
    tree.insert(2, 2);
    tree.insert(6, 6);
    tree.remove(12);
    s = "";
    tree.Traverse(log);
    if (s != "2 5 6 10 ") throw exception();
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();

    return 0;
}
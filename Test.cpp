#include <cmath>
#include "doctest.h"
#include "BinaryTree.hpp"
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <exception>
#include <stdexcept>
using namespace std;
using namespace ariel;
/*
            h
            |
        g---
        |
        |
        |
        |
    a---
        |
        |       f
        |       |
        |   d---
        |   |   |
        |   |   e
        |   |
        b---
            |
            |
            |
            c


*/
BinaryTree <char> bt;
TEST_CASE("pre checking ")
{
    bt.add_root('a').add_left('a', 'b').add_left('b', 'c').add_right('b', 'd').add_left('d', 'e').add_right('d', 'f').add_right('a', 'g').add_right('g', 'h');
    auto it=bt.begin_preorder(); 
    CHECK('a' == (*it));
    ++it;
    CHECK('b' == (*it));
    ++it;
    CHECK('c' == (*it));
    ++it;
    CHECK('d' == (*it));
    ++it;
    CHECK('e' == (*it));
    ++it;
    CHECK('f' == (*it));
    ++it;
    CHECK('g' == (*it));
    ++it;
    CHECK('h' == (*it));
}

TEST_CASE("post checking ")
{
    auto it=bt.begin_postorder(); 
    CHECK('c' == (*it));
    ++it;
    CHECK('e' == (*it));
    ++it;
    CHECK('f' == (*it));
    ++it;
    CHECK('d' == (*it));
    ++it;
    CHECK('b' == (*it));
    ++it;
    CHECK('h' == (*it));
    ++it;
    CHECK('g' == (*it));
    ++it;
    CHECK('a' == (*it));
  
}


TEST_CASE("in checking ")
{
    auto it=bt.begin_inorder(); 
    CHECK('c' == (*it));
    ++it;
    CHECK('b' == (*it));
    ++it;
    CHECK('e' == (*it));
    ++it;
    CHECK('d' == (*it));
    ++it;
    CHECK('f' == (*it));
    ++it;
    CHECK('a' == (*it));
    ++it;
    CHECK('g' == (*it));
    ++it;
    CHECK('h' == (*it));
  
}
TEST_CASE("updating data checking ")
{
    bt.add_root('x');
    bt.add_left('x', 'y');
    bt.add_right('y', 'z');
    auto it=bt.begin_preorder(); 
    CHECK('x' == (*it));
    ++it;
    CHECK('y' == (*it));
    ++it;
    CHECK('c' == (*it));
    ++it;
    CHECK('z' == (*it));
}

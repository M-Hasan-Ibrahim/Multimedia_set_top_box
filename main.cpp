//
// main.cpp
// Created on 21/10/2018
//
#include "Multimedia.h"

#include <iostream>
using namespace std;

int main(int argc, const char* argv[])
{
    std::cout << "Hello brave new world" << std::endl;

    Multimedia m ("file1", "path1");
    m.display(std::cout);

    return 0;
}

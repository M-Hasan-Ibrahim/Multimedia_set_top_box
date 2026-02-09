//
// main.cpp
// Created on 21/10/2018
//
#include "Multimedia.h"

#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Group.h"
#include "MultimediaManager.h"


#include <memory>
#include <vector>

#include <iostream>
using namespace std;

void testMultiMediaManager(){
    MultimediaManager m;

    auto p = m.createPhoto("p1", "assets/photo.png", 1.0, 2.0);
    auto v = m.createVideo("v1", "assets/video.mp4", 120);
    int ch[] = {10,20,30};
    auto f = m.createFilm("film1", "assets/video.mp4", 120, ch, 3);

    auto g1 = m.createGroup("First Group");
    auto g2 = m.createGroup("Second Group");

    g1->push_back(p);
    g1->push_back(f);
    g2->push_back(f);

    m.displayMultimedia("film1", std::cout);
    m.displayGroup("First Group", std::cout);

    m.playMultimedia("v1", 3);

    m.deleteMultimedia("film1");
    m.displayGroup("Second Group", std::cout);
}

int main(int argc, const char* argv[])
{
    testMultiMediaManager();   


    return 0;
}

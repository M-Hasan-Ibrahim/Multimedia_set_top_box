//
// main.cpp
// Created on 21/10/2018
//
#include "Multimedia.h"

#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Group.h"


#include <memory>
#include <vector>

#include <iostream>
using namespace std;

void photoVideoTest(){
    int platform;
    std::cout << "Platform (1=Windows, 2=Linux, 3=WSL): ";
    std::cin >> platform;

    std::vector<std::shared_ptr<Multimedia>> list;
    list.push_back(std::make_shared<Photo>("p1", "assets/photo.png", 33.9, 35.5));
    list.push_back(std::make_shared<Video>("v1", "assets/video.mp4", 120));

    for (const auto& obj : list) {
        obj->display(std::cout);
        obj->play(platform);
        std::cout << "----\n";
    }
}

void filmTest(){
    int* a = new int[3]{10, 20, 30};

    Film f("film1", "assets/video.mp4", 120, a, 3);
    
    std::cout << "display 1:\n";
    f.display(std::cout);
    
    delete[] a;
    a = new int[3]{1, 1, 1};

    std::cout << "display 2:\n";
    f.display(std::cout);

    f.play(3);

    delete[] a;
}

void groupTest() {
    auto p1 = std::make_shared<Photo>("p1", "assets/photo.png", 1, 2);
    auto v1 = std::make_shared<Video>("v1", "assets/video.mp4", 120);

    int ch[] = {10,20,30};
    auto f1 = std::make_shared<Film>("film1", "assets/video.mp4", 120, ch, 3);

    Group gA("First Group");
    Group gB("Second Group");

    gA.push_back(p1);
    gA.push_back(f1);

    gB.push_back(v1);
    gB.push_back(f1);

    gA.display(std::cout);
    gB.display(std::cout);
}


int main(int argc, const char* argv[])
{
    groupTest();   


    return 0;
}

//
// main.cpp
// Created on 21/10/2018
//
#include "Multimedia.h"
#include "Photo.h"
#include "Video.h"

#include <memory>
#include <vector>

#include <iostream>
using namespace std;

int main(int argc, const char* argv[])
{
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


    return 0;
}

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

void testSerialization() {
    MultimediaManager m;

    int ch[] = {10, 20, 30};
    m.createPhoto("p1", "assets/photo.png", 1, 2);
    m.createVideo("v1", "assets/video.mp4", 120);
    m.createFilm("film1", "assets/video.mp4", 120, ch, 3);

    std::cout << "=== ORIGINAL ===\n";
    m.displayMultimedia("p1", std::cout);
    m.displayMultimedia("v1", std::cout);
    m.displayMultimedia("film1", std::cout);

    if (!m.saveMultimediaTable("db.txt")) {
        std::cout << "SAVE FAILED\n";
        return;
    }
    std::cout << "Saved to db.txt\n";

    MultimediaManager m2;
    if (!m2.loadMultimediaTable("db.txt")) {
        std::cout << "LOAD FAILED\n";
        return;
    }

    std::cout << "=== LOADED ===\n";
    m2.displayMultimedia("p1", std::cout);
    m2.displayMultimedia("v1", std::cout);
    m2.displayMultimedia("film1", std::cout);
}

int main(int argc, const char* argv[])
{

    try {
        MultimediaManager m;
        m.createPhoto("p1", "assets/photo.png", 1, 2);
        m.createPhoto("p1", "assets/photo2.png", 1, 2); // duplicate -> throws
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }

    MultimediaManager m2;
    std::cout << std::boolalpha << m2.deleteMultimedia("doesNotExist") << "\n"; // false


    return 0;
}

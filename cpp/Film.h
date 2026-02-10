#ifndef FILM_H
#define FILM_H

#include "Video.h"
#include <iostream>
#include <string>

class MultimediaManager;

class Film : public Video{
    friend class MultimediaManager;
public:
    Film() = default;


    Film(const Film& other) : Video(other) {
        setChapters(other.chapters, other.chapterCount);
    }

    Film& operator=(const Film& other) {
        if (this == &other) return *this;
        Video::operator=(other);
        setChapters(other.chapters, other.chapterCount);
        return *this;
    }

    ~Film() override { 
        std::cout << "film: " << name << " destructed\n";
        delete[] chapters; 
    }


    void setChapters(const int* chapterDurations, int count){

        clearChapters();

        if (count <= 0) throw std::runtime_error("Film chapters count must be > 0");
        if (!chapterDurations) throw std::runtime_error("Film chapters pointer is null");

        chapterCount = count;
        chapters = new int[chapterCount];

        for (int i = 0; i < chapterCount; ++i){
            chapters[i] = chapterDurations[i];
        } 
    }

    void getChapters(const int*& out, int& outCount) const {
        out = chapters;
        outCount = chapterCount;
    }

    int getChapterCount() const { return chapterCount; }

    void display(std::ostream& os) const override {
        Video::display(os);
        os << "Chapters (" << chapterCount << "): ";
        if (!chapters || chapterCount == 0) {
            os << "none\n";
            return;
        }
        for (int i = 0; i < chapterCount; ++i) {
            os << chapters[i];
            if (i + 1 < chapterCount) os << ", ";
        }
        os << "\n";
    }

    std::string className() const override { return "Film"; }

    void write(std::ostream& os) const override {
        Video::write(os);
        os << chapterCount << "\n";
        for (int i = 0; i < chapterCount; ++i) os << chapters[i] << "\n";
    }

    void read(std::istream& is) override {
        Video::read(is);

        std::string line;
        std::getline(is, line);
        int n = std::stoi(line);

        clearChapters();
        if (n <= 0) return;
        chapterCount = n;
        chapters = new int[chapterCount];
        for (int i = 0; i < chapterCount; ++i) {
            std::getline(is, line);
            chapters[i] = std::stoi(line);
        }
    }


private:
    Film(const std::string& name, const std::string& pathname, int duration, const int* chapters, int chapterCount) : Video(name, pathname, duration) {
        setChapters(chapters, chapterCount);
    } 
    int* chapters = nullptr;
    int chapterCount = 0;

    void clearChapters(){
        delete[] chapters;
        chapters = nullptr;
        chapterCount = 0;
    }
};


#endif

#ifndef FILM_H
#define FILM_H

#include "Video.h"
#include <iostream>
#include <string>


class Film : public Video{
public:
    Film() = default;
    Film(const std::string& name, const std::string& pathname, int duration, const int* chapters, int chapterCount) : Video(name, pathname, duration) {
        setChapters(chapters, chapterCount);
    } 

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
        delete[] chapters;
    }

    void setChapters(const int* chapterDurations, int count){
        clearChapters();

        if (!chapterDurations || count <= 0) return;

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

private:
    int* chapters = nullptr;
    int chapterCount = 0;

    void clearChapters(){
        delete[] chapters;
        chapters = nullptr;
        chapterCount = 0;
    }
};


#endif

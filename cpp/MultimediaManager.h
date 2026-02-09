#ifndef MULTIMEDIA_MANAGER_H
#define MULTIMEDIA_MANAGER_H

#include <map>
#include <memory>
#include <string>
#include <iostream>

#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Group.h"

class MultimediaManager {
public:
    using MultimediaPtr = std::shared_ptr<Multimedia>;
    using PhotoPtr = std::shared_ptr<Photo>;
    using VideoPtr = std::shared_ptr<Video>;
    using FilmPtr  = std::shared_ptr<Film>;
    using GroupPtr = std::shared_ptr<Group>;

    PhotoPtr createPhoto(const std::string& name, const std::string& path, double lat, double lon) {
        auto p = PhotoPtr(new Photo(name, path, lat, lon));
        multimediaTable[name] = p;
        return p;
    }

    VideoPtr createVideo(const std::string& name, const std::string& path, int duration) {
        auto v = VideoPtr(new Video(name, path, duration));
        multimediaTable[name] = v;
        return v;
    }

    FilmPtr createFilm(const std::string& name, const std::string& path, int duration,
                       const int* chapters, int chapterCount) {
        auto f = FilmPtr(new Film(name, path, duration, chapters, chapterCount));
        multimediaTable[name] = f;
        return f;
    }

    GroupPtr createGroup(const std::string& name) {
        auto g = GroupPtr(new Group(name));
        groupTable[name] = g;
        return g;
    }

    void displayMultimedia(const std::string& name, std::ostream& os) const {
        auto it = multimediaTable.find(name);
        if (it == multimediaTable.end()) { os << "Multimedia not found: " << name << "\n"; return; }
        it->second->display(os);
    }

    void displayGroup(const std::string& name, std::ostream& os) const {
        auto it = groupTable.find(name);
        if (it == groupTable.end()) { os << "Group not found: " << name << "\n"; return; }
        it->second->display(os);
    }

    void playMultimedia(const std::string& name, int platform) const {
        auto it = multimediaTable.find(name);
        if (it == multimediaTable.end()) { std::cerr << "Multimedia not found: " << name << "\n"; return; }
        it->second->play(platform);
    }

    // optional delete (additional question)
    void deleteMultimedia(const std::string& name) {
        auto it = multimediaTable.find(name);
        if (it == multimediaTable.end()) return;

        auto target = it->second;
        for (auto& kv : groupTable) kv.second->remove(target);
        multimediaTable.erase(it);
    }

    void deleteGroup(const std::string& name) {
        groupTable.erase(name);
    }

private:
    std::map<std::string, MultimediaPtr> multimediaTable;
    std::map<std::string, GroupPtr> groupTable;
};

#endif

#ifndef MULTIMEDIA_MANAGER_H
#define MULTIMEDIA_MANAGER_H

#include <map>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <stdexcept>
#include <cctype>

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
        if (!isValidName(name))
            throw std::runtime_error("Invalid name: " + name);

        if (multimediaTable.find(name) != multimediaTable.end())
            throw std::runtime_error("Multimedia already exists: " + name);

        auto p = PhotoPtr(new Photo(name, path, lat, lon));
        multimediaTable[name] = p;
        return p;
    }

    VideoPtr createVideo(const std::string& name, const std::string& path, int duration) {
        if (!isValidName(name))
            throw std::runtime_error("Invalid name: " + name);

        if (multimediaTable.find(name) != multimediaTable.end())
            throw std::runtime_error("Multimedia already exists: " + name);
        
        auto v = VideoPtr(new Video(name, path, duration));
        multimediaTable[name] = v;
        return v;
    }

    FilmPtr createFilm(const std::string& name, const std::string& path, int duration,
                       const int* chapters, int chapterCount) {
        if (!isValidName(name))
            throw std::runtime_error("Invalid name: " + name);

        if (multimediaTable.find(name) != multimediaTable.end())
            throw std::runtime_error("Multimedia already exists: " + name);
        
        auto f = FilmPtr(new Film(name, path, duration, chapters, chapterCount));
        multimediaTable[name] = f;
        return f;
    }

    GroupPtr createGroup(const std::string& name) {
        if (!isValidName(name))
            throw std::runtime_error("Invalid name: " + name);

        if (groupTable.find(name) != groupTable.end())
            throw std::runtime_error("Group already exists: " + name);

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

    bool playMultimedia(const std::string& name, int platform) const {
        auto it = multimediaTable.find(name);
        if (it == multimediaTable.end()) return false;
        it->second->play(platform);
        return true;
    }


    bool deleteMultimedia(const std::string& name) {
        auto it = multimediaTable.find(name);
        if (it == multimediaTable.end()) return false; // nothing to do
        auto target = it->second;
        for (auto& kv : groupTable) kv.second->remove(target);
        multimediaTable.erase(it);
        return true;
    }


    bool deleteGroup(const std::string& name) {
        return groupTable.erase(name) > 0;
    }


    bool saveMultimediaTable(const std::string& filename) const {
        std::ofstream ofs(filename);
        if (!ofs) return false;

        ofs << multimediaTable.size() << "\n";
        for (const auto& kv : multimediaTable) {
            const auto& obj = kv.second;
            ofs << obj->className() << "\n";
            obj->write(ofs);
        }
        return true;
    }

    bool loadMultimediaTable(const std::string& filename) {
        std::ifstream ifs(filename);
        if (!ifs) return false;

        multimediaTable.clear();

        std::string line;
        std::getline(ifs, line);
        int count = std::stoi(line);

        
        for (int i = 0; i < count; ++i) {
            std::string cls;
            std::getline(ifs, cls);

            std::shared_ptr<Multimedia> obj;

            if (cls == "Photo") obj = std::shared_ptr<Photo>(new Photo());
            else if (cls == "Video") obj = std::shared_ptr<Video>(new Video());
            else if (cls == "Film") obj = std::shared_ptr<Film>(new Film());
            else return false;

            obj->read(ifs);
            multimediaTable[obj->getName()] = obj;
        }
        return true;
    }

    static bool isValidName(const std::string& s) {
        if (s.empty()) return false;
        for (unsigned char c : s) {
            if (!(std::isalnum(c) || c=='_' || c=='-' )) return false; // simple rule
        }
        return true;
    }



private:
    std::map<std::string, MultimediaPtr> multimediaTable;
    std::map<std::string, GroupPtr> groupTable;
};

#endif

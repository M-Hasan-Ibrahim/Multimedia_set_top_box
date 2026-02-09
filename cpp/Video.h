#ifndef VIDEO_H
#define VIDEO_H

#include "Multimedia.h"
#include <cstdlib>

class MultimediaManager;

class Video : public Multimedia{
    friend class MultimediaManager;
    
public:
    Video() = default;

    // Video(const std::string& name, const std::string& pathname, int duration) : Multimedia(name, pathname), duration(duration){}

    ~Video() override{
        std::cout << "video: " << this->name << " destructed\n";
    }

    virtual void display(std::ostream& os) const override{
        Multimedia::display(os);
        os << "Duration: " << duration << "\n";
    }

    virtual void play(int platform) const override{
        std::string cmd;
        if (platform == 1) {
            cmd = "start \"\" vlc \"" + pathname + "\"";
        } else if (platform == 2) {
            cmd = "xdg-open \"" + pathname + "\" &"; // or mpv
        } else if (platform == 3) {
            cmd = "\"/mnt/c/Program Files (x86)/VideoLAN/VLC/vlc.exe\" "
              "\"$(wslpath -w '" + pathname + "')\"";
        } else {
            std::cout << "invalid platform\n";
            return;
        }
        system(cmd.c_str());
    }


    int getDuration() const{
        return this->duration;
    }
    void setDuration(int duration){
        this->duration = duration;
    }

    std::string className() const override { return "Video"; }

    void write(std::ostream& os) const override {
        Multimedia::write(os);
        os << duration << "\n";
    }

    void read(std::istream& is) override {
        Multimedia::read(is);
        std::string line;
        std::getline(is, line); duration = std::stoi(line);
    }



protected:
    Video(const std::string& name, const std::string& pathname, int duration) : Multimedia(name, pathname), duration(duration){}


private:

    int duration = 0;
};

#endif
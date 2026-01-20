#ifndef PHOTO_H
#define PHOTO_H

#include "Multimedia.h"
#include <cstdlib>

class Photo : public Multimedia{
public:
    Photo() = default;

    Photo(const std::string& name, const std::string& pathname, double latitude, double longitude) 
    : Multimedia(name, pathname), latitude(latitude), longitude(longitude){}

    virtual ~Photo(){
        std::cout << "photo: " << this->name << " destructed\n";
    }

    virtual void display(std::ostream& os) const override{
        Multimedia::display(os);
        os << "Latitude: " << latitude << "\n";
        os << "Longitude: "<< longitude << "\n";
    }

    virtual void play(int platform) const override{
        std::string cmd;
        if (platform == 1) {
            cmd = "start \"\" \"" + pathname + "\"";
        } else if (platform == 2) {
            cmd = "xdg-open \"" + pathname + "\" &";
        } else if (platform == 3) {
            cmd = "explorer.exe \"$(wslpath -w '" + pathname + "')\"";
        } else {
            std::cout << "invalid platform\n";
            return;
        }
        system(cmd.c_str());
    }


    double getLatitude() const{
        return this->latitude;
    } 
    double getLongitude() const{
        return this->longitude;
    }

    void setLatitude(double latitude){
        this->latitude = latitude;
    }
    void setLongitude(double longitude){
        this->longitude = longitude;
    }


private:
    double latitude = 0.0;
    double longitude = 0.0;
};

#endif
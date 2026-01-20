#include "Multimedia.h"

Multimedia::Multimedia(){
    this->name = "No Name";
    this->path = "No Path Specified";
}

Multimedia::Multimedia(const std::string& name, const std::string& path){
    this->name = name;
    this->path = path;
}

void Multimedia::display(std::ostream& os) const{
    os << "Name: " << name << std::endl;
    os << "Path: " << pathname << std::endl;
}

void Multimedia::setName(const std::string& name){
    this->name = name;
}

std::string Multimedia::getName() const{
    return this->name;
}

void Multimedia::setPath(const std::string& path){
    this->path = path;
}

std::string Multimedia::getPath() const{
    return this->path;
}




virtual Multimedia::~Multimedia(){
    std::cout << "object terminated" << std::endl;
}
#include "Multimedia.h"

Multimedia::Multimedia(){
    this->name = "No Name";
    this->pathname = "No Path Specified";
}

Multimedia::Multimedia(const std::string& name, const std::string& pathname){
    this->name = name;
    this->pathname = pathname;
}

void Multimedia::display(std::ostream& os) const{
    os << "Name: " << this->name << std::endl;
    os << "Path: " << this->pathname << std::endl;
}

void Multimedia::setName(const std::string& name){
    this->name = name;
}

std::string Multimedia::getName() const{
    return this->name;
}

void Multimedia::setPathName(const std::string& pathname){
    this->pathname = pathname;
}

std::string Multimedia::getPathName() const{
    return this->pathname;
}

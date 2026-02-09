#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include<string>
#include<iostream>

class Multimedia{
public:
    Multimedia();
    Multimedia(const std::string& name,const std::string& pathname);

    virtual ~Multimedia() = default;

    virtual std::string className() const = 0;

    virtual void display(std::ostream& os) const;
    virtual void play(int platform) const = 0;

    void setName(const std::string& name);
    std::string getName() const;

    void setPathName(const std::string& pathname);
    std::string getPathName() const;

    virtual void write(std::ostream& os) const {
        os << name << "\n";
        os << pathname << "\n";
    }

    virtual void read(std::istream& is) {
        std::getline(is, name);
        std::getline(is, pathname);
    }

protected:
    std::string name = "";
    std::string pathname = "";

};


#endif
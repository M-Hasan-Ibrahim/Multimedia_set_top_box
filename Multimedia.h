#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include<string>
#include<iostream>

class Multimedia{
public:
    Multimedia();
    Multimedia(const std::string& name,const std::string& pathname);

    virtual ~Multimedia();

    virtual void display(std::ostream& os) const;
    virtual void play(int platform) const = 0;

    void setName(const std::string& name);
    std::string getName() const;

    void setPathName(const std::string& pathname);
    std::string getPathName() const;

protected:
    std::string name = "";
    std::string pathname = "";

};


#endif
#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include<string>
#include<iostream>

class Multimedia{
public:
    Multimedia();
    Multimedia(const std::string& name,const std::string& path);

    virtual ~Multimedia();

    virtual void display(std::ostream& os) const;

    void setName(const std::string& name);
    std::string getName() const;

    void setPath(const std::string& path);
    std::string getPath() const;

private:
    std::string name = "";
    std::string path = "";

};


#endif
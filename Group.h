#ifndef GROUP_H
#define GROUP_H

#include <list>
#include <memory>
#include <string>
#include <iostream>
#include "Multimedia.h"

using MultimediaPtr = std::shared_ptr<Multimedia>;

class Group : public std::list<MultimediaPtr> {
private:
    std::string name;

public:
    Group(const std::string& name) : name(name) {}

    const std::string& getName() const { return name; }

    void display(std::ostream& os) const {
        os << "Group: " << name << "\n";
        for (const auto& obj : *this) {
            if (obj) obj->display(os);
            os << "----\n";
        }
    }
};

#endif

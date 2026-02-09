//
//  server.cpp
//  TP C++
//  Eric Lecolinet - Telecom ParisTech - 2016.
//

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "tcpserver.h"

#include "../cpp/MultimediaManager.h"


const int PORT = 3331;


static void nl_to_semicolon(std::string& s) {
  std::replace(s.begin(), s.end(), '\n', ';');
  std::replace(s.begin(), s.end(), '\r', ';');
}


int main() {
  MultimediaManager manager;

  int ch[] = {10,20,30};
  auto v1 = manager.createVideo("v1", "../assets/video.mp4", 120);
  auto f1 = manager.createFilm("film1", "../assets/video.mp4", 120, ch, 3);
  auto p1 = manager.createPhoto("p1", "../assets/photo.png", 1, 2);

  auto g1 = manager.createGroup("FirstGroup");
  g1->push_back(p1);
  g1->push_back(f1);

  auto g2 = manager.createGroup("SecondGroup");
  g2->push_back(p1);
  g2->push_back(v1);

  TCPServer server([&](std::string const& request, std::string& response) {
    std::istringstream iss(request);
    std::string cmd;
    iss >> cmd;

    if (cmd == "help") {
      response = "Commands: help ; show <name> ; showg <group> ; play <name> <platform> ; quit";
      return true;
    }

    if (cmd == "show") {
      std::string name; iss >> name;
      if (name.empty()) { response = "ERR: usage show <name>"; return true; }

      std::ostringstream oss;
      manager.displayMultimedia(name, oss);
      response = oss.str();
      nl_to_semicolon(response);
      return true;
    }

    if (cmd == "showg") {
      std::string gname; iss >> gname;
      if (gname.empty()) { response = "ERR: usage showg <group>"; return true; }

      std::ostringstream oss;
      manager.displayGroup(gname, oss);
      response = oss.str();
      nl_to_semicolon(response);
      return true;
    }

    if (cmd == "play") {
      std::string name; int platform;
      iss >> name >> platform;
      if (name.empty() || !iss) { response = "ERR: usage play <name> <platform>"; return true; }

      manager.playMultimedia(name, platform);
      response = "OK";
      return true;
    }

    if (cmd == "quit") { response = "OK"; return false; }

    response = "ERR: unknown command (type help)";
    return true;
  });

  std::cout << "Server running on port " << PORT << std::endl;
  return (server.run(PORT) < 0) ? 1 : 0;
}


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
  auto video = manager.createVideo("video", "../assets/video.mp4", 120);
  auto film = manager.createFilm("film", "../assets/video.mp4", 120, ch, 3);
  auto photo = manager.createPhoto("photo", "../assets/photo.png", 1, 2);

  auto group1 = manager.createGroup("group1");
  group1->push_back(photo);
  group1->push_back(film);

  auto group2 = manager.createGroup("group2");
  group2->push_back(photo);
  group2->push_back(video);

  TCPServer server([&](std::string const& request, std::string& response) {
    try{
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
    } catch (const std::exception& e) {
        response = std::string("ERR: ") + e.what();
        nl_to_semicolon(response);
        return true;
      }
  });

  std::cout << "Server running on port " << PORT << std::endl;
  return (server.run(PORT) < 0) ? 1 : 0;
}


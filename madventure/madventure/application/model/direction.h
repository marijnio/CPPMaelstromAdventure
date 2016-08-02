#pragma once

#include <cassert>
#include <map>
#include <string>
using namespace std;

struct Direction {
  Direction(int angle) : angle(angle) {}

  const int angle;

  map<int, string> Direction::labels = {
    { 0, "NORTH" },
    { 90, "EAST" },
    { 180, "SOUTH" },
    { 270, "WEST" }
  };


  string Name() {
    string str = Direction::labels.at(angle);

    map<int, string>::iterator it = labels.find(angle);
    if (it == labels.end()) {
      return "NULL";
    }
    return it->second;
  }

  int Opposite() {
    return (angle + 180) % 360;
  }
};
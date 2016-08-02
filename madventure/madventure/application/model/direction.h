#pragma once

#include <cassert>
#include <map>

using namespace std;

struct Direction {
  Direction(int angle) : angle(angle) {}

  const int angle;

  map<int, char> Direction::initials = {
    { 0, 'N' },
    { 90, 'E' },
    { 180, 'S' },
    { 270, 'W' }
  };

  int Direction::GetAngle(char initial) {
    map<int, char>::iterator it = initials.find(initial);
    assert(it != initials.end());
    return it->second;
  }

  char Initial() {
    return Direction::initials.at(angle);
  }

  int Opposite() {
    return (angle + 180) % 360;
  }
};
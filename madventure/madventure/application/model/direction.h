#pragma once

#include <cassert>
#include <map>

using namespace std;

struct Direction {
  explicit Direction(int angle) : angle(angle) {}

  const int angle;

  map<int, char> Direction::initials = {
    { 0, 'N' },
    { 90, 'E' },
    { 180, 'S' },
    { 270, 'W' }
  };

  int Direction::GetAngle(char initial) {
    std::map<int, char>::iterator it = initials.find(initial);
    assert(it != initials.end());
    return it->second;
  }

  int Opposite() {
    return (angle + 180) % 360;
  }
}
#pragma once

#include <memory>
#include <string>

#include "unit.h"

using namespace std;

struct Player : Unit {
  explicit Player(shared_ptr<Area> area, string name, int health)
      : Unit(area, health), name(name) {
    area->visited = true;
  }
  string name;
  int dexterity = 1;
};
#pragma once

#include <memory>

#include "unit.h"

using namespace std;

struct Player : Unit {
  explicit Player(shared_ptr<Area> area, int health) : Unit(area, health) {
    area->visited = true;
  }

  char name[13] = "Goliath";
};
#pragma once

#include <memory>

#include "unit.h"

using namespace std;

struct Enemy : Unit {
  explicit Enemy(shared_ptr<Area> area, int health) : Unit(area, health) {}

  char name[13] = "Lizard";
};
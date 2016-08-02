#pragma once

#include <memory>

#include "unit.h"

using namespace std;

struct Enemy : Unit {
  explicit Enemy(shared_ptr<Area> area) : Unit(area) {}

  char name[13] = "Lizard";
};
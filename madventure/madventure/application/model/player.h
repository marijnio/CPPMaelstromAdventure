#pragma once

#include <memory>

#include "unit.h"

using namespace std;

struct Player : Unit {
  explicit Player(shared_ptr<Area> area) : Unit(area) {}

  char name[13] = "Icarus";
};
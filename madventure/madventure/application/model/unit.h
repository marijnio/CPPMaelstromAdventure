#pragma once

#include <memory>

#include "../model/area.h"

using namespace std;

struct Unit {
  Unit(shared_ptr<Area> area, int health)
      : area(area), health(health) {}

  // Necessary virtual destructor in order to make this a polymorphic type.
  virtual ~Unit() {};

  shared_ptr<Area> area;
  int health;
};
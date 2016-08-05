#pragma once

#include <memory>

#include "../model/area.h"

using namespace std;

struct Unit {
  explicit Unit(shared_ptr<Area> area, int health)
      : area(area), health(health) {}

  shared_ptr<Area> area;
  int health;
};
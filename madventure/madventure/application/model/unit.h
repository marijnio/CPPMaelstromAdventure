#pragma once

#include <memory>

#include "../model/area.h"

using namespace std;

struct Unit {
  explicit Unit(shared_ptr<Area> area) : area(area) {}

  shared_ptr<Area> area;  
};
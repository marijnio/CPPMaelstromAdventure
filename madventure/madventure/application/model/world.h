#pragma once

#include <vector>
#include <memory>

#include "../model/level.h"

using namespace std;

struct World {
  explicit World() {}

  vector<shared_ptr<Level>> levels;
};
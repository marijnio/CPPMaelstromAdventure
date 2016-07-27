#pragma once

#include <memory>
#include <vector>

#include "../model/area.h"
#include "../model/level.h"
#include "../graph/SparseGraph.h"

class LevelSystem {
public:
  explicit LevelSystem();

  vector<int> GetAreaDirections(shared_ptr<Area> area);
};
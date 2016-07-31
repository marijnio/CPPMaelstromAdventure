#pragma once

#include <memory>
#include <vector>

#include "../model/area.h"
#include "../model/level.h"
#include "../graph/SparseGraph.h"
#include "../graph/GraphEdgeTypes.h"

class LevelSystem {
public:
  LevelSystem() {};

  vector<int> GetNeighboringNodeIndices(shared_ptr<Area> area);
};


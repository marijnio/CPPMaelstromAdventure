#pragma once

#include <memory>
#include <vector>

#include "../model/area.h"
#include "../model/level.h"
#include "../model/world.h"
#include "../graph/SparseGraph.h"
#include "../graph/GraphEdgeTypes.h"

class LevelSystem {
public:
  LevelSystem() {};

  shared_ptr<Level> NewLevel(int columns, int row);

  vector<int> GetNeighboringNodeIndices(shared_ptr<Area> area);
  
  void setWorld(shared_ptr<World> world) { world_ = world; }
private:
  shared_ptr<World> world_;
};


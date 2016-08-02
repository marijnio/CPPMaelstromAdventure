#pragma once

#include <memory>
#include <vector>

#include "../model/area.h"
#include "../model/level.h"
#include "../model/world.h"
#include "../model/direction.h"
#include "../graph/SparseGraph.h"
#include "../graph/GraphEdgeTypes.h"

class LevelSystem {
public:
  LevelSystem() {
    world_ = make_shared<World>();
  };

  shared_ptr<Level> NewLevel(int columns, int row);
  void AddLevel(shared_ptr<Level> level) { world_->levels.push_back(level); }
  vector<int> NeighboringNodeIndexes(shared_ptr<Area> area);
  static int RelativeVectorAngle(const Vector2D alpha, const Vector2D beta);
  vector<Direction> LevelSystem::GetDirections(shared_ptr<Area> area, vector<int> neighbors);
  shared_ptr<Area> RandomArea(shared_ptr<Level> level);
  vector<shared_ptr<Area>> GetAreasInLevel(shared_ptr<Level> level);
  void AddGateway(shared_ptr<Area> from, shared_ptr<Area> to);
private:
  shared_ptr<World> world_;
};


#pragma once

#include <memory>

#include "../graph/GraphNodeTypes.h"

using namespace std;

struct Level; // Forward declaration

struct Area {
  explicit Area(int node_index, shared_ptr<Level> level)
      : node_index(node_index), level(level) {}
  int node_index;
  shared_ptr<Level> level;
};
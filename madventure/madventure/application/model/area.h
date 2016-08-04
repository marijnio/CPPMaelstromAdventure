#pragma once

#include <memory>
#include <vector>
#include <string>

#include "../graph/GraphNodeTypes.h"
#include "gateway.h"
#include "../system/gameinfoparser.h"

using namespace std;

struct Level; // Forward declaration

struct Area {
  explicit Area(int node_index, shared_ptr<Level> level)
      : node_index(node_index), level(level) {
    climate = rand() % (12);
    visited = false;
  }
  int node_index;
  shared_ptr<Level> level;
  shared_ptr<Gateway> gateway;
  int climate;
  bool visited;
};


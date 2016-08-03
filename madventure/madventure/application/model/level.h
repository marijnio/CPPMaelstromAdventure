#pragma once

#include <memory>

#include "area.h"
#include "../graph/SparseGraph.h"
#include "../graph/GraphNodeTypes.h"
#include "../graph/GraphEdgeTypes.h"

struct Level {
  explicit Level(shared_ptr<SparseGraph<NavGraphNode<shared_ptr<Area>>,
                 NavGraphEdge>> graph)
      : graph(graph) {
    time_ = rand() % (24);
  }
  int time_;
  void IncrementTime(int amount) {
    time_ = (time_ + amount) % 24;
  }
  shared_ptr<SparseGraph<NavGraphNode<shared_ptr<Area>>, NavGraphEdge>> graph;
};
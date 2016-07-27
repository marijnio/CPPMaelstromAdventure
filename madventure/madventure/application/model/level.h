#pragma once

#include <memory>

#include "area.h"
#include "../graph/SparseGraph.h"
#include "../graph/GraphNodeTypes.h"
#include "../graph/GraphEdgeTypes.h"

struct Level {
  explicit Level(shared_ptr<SparseGraph<NavGraphNode<shared_ptr<Area>>, NavGraphEdge>> graph)
      : graph(graph) {}

  shared_ptr<SparseGraph<NavGraphNode<shared_ptr<Area>>, NavGraphEdge>> graph;
};
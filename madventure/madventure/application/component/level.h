#pragma once

#include "area.h"
#include "../graph/SparseGraph.h"
#include "../graph/GraphNodeTypes.h"
#include "../graph/GraphEdgeTypes.h"

struct Level {
  explicit Level(SparseGraph<NavGraphNode<Area>, NavGraphEdge> graph)
    : graph_(graph) {}

  SparseGraph<NavGraphNode<Area>, NavGraphEdge> graph_;
};
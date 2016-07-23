#pragma once

#include "entityx/entityx.h"

#include "area.h"
#include "../graph/SparseGraph.h"
#include "../graph/GraphNodeTypes.h"
#include "../graph/GraphEdgeTypes.h"

struct Level {
  explicit Level(SparseGraph<NavGraphNode<ex::Entity*>, NavGraphEdge> graph)
      : graph(graph) {}

  SparseGraph<NavGraphNode<ex::Entity*>, NavGraphEdge> graph;
};
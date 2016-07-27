#pragma once

#include <memory>

#include "../graph/GraphNodeTypes.h"

using namespace std;

struct Area {
  explicit Area(NavGraphNode<shared_ptr<Area>> node) : node(node) {}

  NavGraphNode<shared_ptr<Area>> node;
};
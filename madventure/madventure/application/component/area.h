#pragma once

#include "entityx/entityx.h"

#include "../graph/GraphNodeTypes.h"

struct Area {
  explicit Area(NavGraphNode<ex::Entity*> node) : node(node) {}

  NavGraphNode<ex::Entity*> node;

  char myword[13] = "Hello world!";
};
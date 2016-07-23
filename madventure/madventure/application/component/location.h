#pragma once

#include "entityx/entityx.h"

#include "../component/area.h"

namespace ex = entityx;

struct Location {
  explicit Location(ex::Entity* area) : area_(area) {}

  ex::Entity* area_;
  
};
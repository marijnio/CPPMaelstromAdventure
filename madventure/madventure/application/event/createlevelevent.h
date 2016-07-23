#pragma once

#include "entityx/entityx.h"

namespace ex = entityx;

struct CreateLevelEvent {
  CreateLevelEvent(ex::EntityManager &es) : es_(es) {}

  entityx::EntityManager &es_;
};
#pragma once

#include "entityx/entityx.h"

namespace ex = entityx;

class InterpreterSystem : public ex::System<InterpreterSystem> {
public:
  explicit InterpreterSystem() {};

  void update(ex::EntityManager &es, ex::EventManager &events,
              ex::TimeDelta dt);
};
#ifndef MADVENTURE_APPLICATION_SYSTEM_INTERPRETERSYSTEM_H_
#define MADVENTURE_APPLICATION_SYSTEM_INTERPRETERSYSTEM_H_

#include "entityx/entityx.h"

namespace ex = entityx;

class InterpreterSystem : public ex::System<InterpreterSystem> {
public:
  explicit InterpreterSystem() {};

  void update(ex::EntityManager &es, ex::EventManager &events,
              ex::TimeDelta dt);
};

#endif // MADVENTURE_APPLICATION_SYSTEM_INTERPRETERSYSTEM_H_
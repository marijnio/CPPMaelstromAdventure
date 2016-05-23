#ifndef MADVENTURE_APPLICATION_SYSTEM_INTERPRETERSYSTEM_H_
#define MADVENTURE_APPLICATION_SYSTEM_INTERPRETERSYSTEM_H_

#include "entityx\entityx.h"

namespace ex = entityx;

class InterpreterSystem : public entityx::System<InterpreterSystem> {
public:
  explicit InterpreterSystem();

  void update(entityx::EntityManager &es, entityx::EventManager &events,
              entityx::TimeDelta dt);
};

#endif // MADVENTURE_APPLICATION_SYSTEM_INTERPRETERSYSTEM_H_
#ifndef MADVENTURE_APPLICATION_SYSTEM_LEVELSYSTEM_H_
#define MADVENTURE_APPLICATION_SYSTEM_LEVELSYSTEM_H_

#include "entityx/entityx.h"

namespace ex = entityx;

struct LevelSystem : public ex::System<LevelSystem> {
public:
  explicit LevelSystem() {};

  void update(ex::EntityManager &es, ex::EventManager &events,
              ex::TimeDelta dt);
};

#endif // MADVENTURE_APPLICATION_SYSTEM_LEVELSYSTEM_H_
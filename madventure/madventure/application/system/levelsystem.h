#ifndef MADVENTURE_APPLICATION_SYSTEM_LEVELSYSTEM_H_
#define MADVENTURE_APPLICATION_SYSTEM_LEVELSYSTEM_H_

#include "entityx\entityx.h"

namespace ex = entityx;

struct LevelSystem : public entityx::System<LevelSystem> {
public:
  explicit LevelSystem();

  void update(entityx::EntityManager &es, entityx::EventManager &events,
              entityx::TimeDelta dt);
};

#endif // MADVENTURE_APPLICATION_SYSTEM_LEVELSYSTEM_H_
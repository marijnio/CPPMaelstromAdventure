#pragma once

#include "entityx/entityx.h"

#include "../event/createlevelevent.h"

namespace ex = entityx;

struct LevelSystem : public ex::System<LevelSystem>, public ex::Receiver<LevelSystem> {
public:
  explicit LevelSystem() {};

  void configure(ex::EventManager &events) override;

  void update(ex::EntityManager &es, ex::EventManager &events,
              ex::TimeDelta dt);

  void receive(const CreateLevelEvent &createlevel);

  ex::Entity createLevel(ex::EntityManager & es);

private:

};
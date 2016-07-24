#pragma once

#include "entityx/entityx.h"

#include "../event/createlevelevent.h"

namespace ex = entityx;

struct LevelSystem : public ex::System<LevelSystem>, public ex::Receiver<LevelSystem> {
public:
  explicit LevelSystem() {};

  void configure(ex::EventManager &events) override;

  void update(ex::EntityManager &entities, ex::EventManager &events,
              ex::TimeDelta dt);

  void receive(const CreateLevelEvent &createlevel);

  ex::Entity createLevel(ex::EntityManager &entities);

private:
  std::vector<ex::Entity> levels_;
};
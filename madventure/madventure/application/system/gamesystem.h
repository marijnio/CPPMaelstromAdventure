#pragma once

#include "entityx/entityx.h"
#include "../event/gamequitevent.h"

namespace ex = entityx;

class GameSystem
    : public ex::System<GameSystem>, public ex::Receiver<GameSystem> {
public:
  explicit GameSystem() {};

  void configure(ex::EventManager &events) override;

  void update(ex::EntityManager &entities, ex::EventManager &events,
              ex::TimeDelta dt);

  void initialize(ex::EntityManager &entities, ex::EventManager &events);

  void receive(const GameQuitEvent &gamequit);

  bool is_finished() { return finished_; }

private:
  bool finished_;
  bool initialized_ = false;
};
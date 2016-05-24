#pragma once

#include "entityx/entityx.h"
#include "../event/gamequit.h"

namespace ex = entityx;

class GameSystem
  : public ex::System<GameSystem>, public ex::Receiver<GameSystem> {
public:
  explicit GameSystem() {};

  void configure(ex::EventManager &events) override;

  void update(ex::EntityManager &es, ex::EventManager &events,
              ex::TimeDelta dt);

  void receive(const GameQuit &gamequit);

  bool is_finished() { return finished_; }

private:
  bool finished_;
};
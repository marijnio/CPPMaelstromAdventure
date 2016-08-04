#pragma once

#include "../model/world.h"
#include "../model/enemy.h"
#include "../model/player.h"

class UnitSystem {
public:
  UnitSystem() {};

  shared_ptr<Enemy> SpawnEnemy(shared_ptr<Area>);
  shared_ptr<Player> SpawnPlayer(shared_ptr<Area>);
  shared_ptr<Player> player() { return player_; }
  void SetPlayer(shared_ptr<Player> player) { player_ = player; }

  // Generic implementation.
  template <typename T>
  void MoveUnit(shared_ptr<T> unit, shared_ptr<Area> destination);
  // Specialized implementation.
  void MoveUnit(shared_ptr<Player> unit, shared_ptr<Area> destination);

private:
  shared_ptr<Player> player_;
};


template <typename T>
void UnitSystem::MoveUnit(shared_ptr<T> unit, shared_ptr<Area> destination) {
  unit->area = destination;
}

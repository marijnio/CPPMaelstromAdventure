#pragma once

#include "../model/world.h"
#include "../model/enemy.h"

class UnitSystem {
public:
  UnitSystem() {};

  shared_ptr<Enemy> SpawnEnemy(shared_ptr<Area>);
  void setWorld(shared_ptr<World> world) { world_ = world; }
  void MoveUnit(shared_ptr<Unit> unit, shared_ptr<Area> destination);
private:
  shared_ptr<World> world_;
};


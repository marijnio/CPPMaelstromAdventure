#include "unitsystem.h"

using namespace std;

shared_ptr<Enemy> UnitSystem::SpawnEnemy(shared_ptr<Area> destination) {
  auto enemy = make_shared<Enemy>(destination);
  return enemy;
}

void UnitSystem::MoveUnit(shared_ptr<Unit> unit, shared_ptr<Area> destination) {
  unit->area = destination;
}

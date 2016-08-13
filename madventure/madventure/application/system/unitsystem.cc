#include "unitsystem.h"

#include <iostream>
#include <fstream>

#include <math.h>

using namespace std;

shared_ptr<Enemy> UnitSystem::SpawnEnemy(shared_ptr<Area> destination,
                                         int health) {
  auto enemy = make_shared<Enemy>(destination, health);
  destination->units.push_back(enemy);
  //cout << "Spawning enemy in destination " << destination->node_index << ".\n";
  return enemy;
}

shared_ptr<Player> UnitSystem::SpawnPlayer(shared_ptr<Area> destination,
                                           string name, int health) {
  auto player = make_shared<Player>(destination, name, health);
  destination->units.push_back(player);
  return player;
}

void UnitSystem::TrapPlayer(shared_ptr<Player> player) {
  cout << "It's a trap!\n";
  auto difficulty = player->area->trap->difficulty;
  auto dexterity = player->dexterity;
  auto damage = static_cast<int>(round((8.0 * difficulty)
    - (8.0 * static_cast<double>(dexterity))));
  if (damage <= 0) {
    damage = 0;
    cout << "Succesfully dismantled the trap.\n";
  } else {
    player->health = player->health - damage;
    cout << "You've been struck by the trap and took " << damage << " damage.\n";
  }
  player->area->trap = nullptr;
}

void UnitSystem::MoveUnit(shared_ptr<Player> unit, shared_ptr<Area> destination) {
  // Remove the unit from its current location.
  auto units = unit->area->units;
  vector<shared_ptr<Unit>>::iterator position = find(units.begin(), units.end(), unit);
  if (position != units.end()) {
    units.erase(position);
  }
  // Update the reference in the unit.
  unit->area = destination;

  // Add the unit to the new location.
  destination->units.push_back(unit);

  unit->area->visited = true;
}
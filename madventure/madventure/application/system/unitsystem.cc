#include "unitsystem.h"

#include <iostream>
#include <fstream>

#include <math.h>

using namespace std;

shared_ptr<Enemy> UnitSystem::SpawnEnemy(shared_ptr<Area> destination,
                                         int health, EnemyType enemy_type,
                                         EnemyModifier enemy_modifier) {
  auto enemy = make_shared<Enemy>(destination, health, enemy_type, enemy_modifier);
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
  // First, remove the unit from its current location.

  // Copy unit vector from source area.
  auto source_units = unit->area->units;

  vector<shared_ptr<Unit>>::iterator position = find(source_units.begin(), source_units.end(), unit);
  if (position != source_units.end()) {
    // Unit found in source area. Erase.
    source_units.erase(position);
  }

  // Restore updated unit vector onto source area.
  unit->area->units = source_units;

  // Update the area reference from within the unit.
  unit->area = destination;

  // Add the unit to the new location.
  destination->units.push_back(unit);

  unit->area->visited = true;
}

vector<shared_ptr<Enemy>> UnitSystem::SelectEnemies(vector<shared_ptr<Unit>> units) {
  vector<shared_ptr<Enemy>> enemies;

  for (vector<shared_ptr<Unit>>::iterator it = units.begin(); it != units.end(); ++it) {
    auto unit_pointer = (*it).get(); // Convert shared_ptr to regular pointer.
    if (dynamic_cast<Enemy*>(unit_pointer) != 0) {
      // Current unit is a verified enemy.
      enemies.push_back(dynamic_pointer_cast<Enemy>(*it));
    }
  }
  return enemies;
}

vector<shared_ptr<Player>> UnitSystem::SelectPlayers(vector<shared_ptr<Unit>> units) {
  vector<shared_ptr<Player>> players;

  for (vector<shared_ptr<Unit>>::iterator it = units.begin(); it != units.end(); ++it) {
    auto unit_pointer = (*it).get(); // Convert shared_ptr to regular pointer.
    if (dynamic_cast<Player*>(unit_pointer) != 0) {
      // Current unit is a verified player.
      players.push_back(dynamic_pointer_cast<Player>(*it));
    }
  }
  return players;
}

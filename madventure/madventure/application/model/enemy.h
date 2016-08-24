#pragma once

#include <memory>

#include "unit.h"

using namespace std;

// Note: These are strongly typed enums, aka enum classes.
enum class EnemyType { SERPENT, WHALE, MEDUSA, DRAGON, OCTOPUS, SQUID, NAUTILUS };
enum class EnemyModifier { NONE, TWOHEADED, STONE, ELECTRIC, FIREBREATHING, UNDEAD };

inline string EnemyTypeAsString(enum class EnemyType type) {
  vector<string> strings = { "SERPENT", "WHALE", "MEDUSA", "DRAGON", "OCTOPUS", "SQUID", "NAUTILUS" };
  return strings[static_cast<int>(type)];
}

inline string EnemyModifierAsString(enum class EnemyModifier modifier) {
  vector<string> strings = { "NONE", "TWOHEADED", "STONE", "ELECTRIC", "FIREBREATHING", "UNDEAD" };
  return strings[static_cast<int>(modifier)];
}

struct Enemy : Unit {
  explicit Enemy(shared_ptr<Area> area, int health, EnemyType type,
                 EnemyModifier modifier)
      : Unit(area, health), type(type), modifier(modifier) {}

  EnemyType type;
  EnemyModifier modifier;
};

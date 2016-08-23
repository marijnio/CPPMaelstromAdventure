#pragma once

#include <memory>

#include "unit.h"

using namespace std;

struct Enemy : Unit {
  explicit Enemy(shared_ptr<Area> area, int health) : Unit(area, health) {}

  char name[13] = "Lizard";
};

// Note: These are strongly typed enums, aka enum classes.
enum class EnemyType { SERPENT, WHALE, MEDUSA, DRAGON, OCTOPUS, SQUID, NAUTILUS, DRAGON };

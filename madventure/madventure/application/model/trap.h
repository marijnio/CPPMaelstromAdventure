#pragma once

#include <memory>

struct Area; // Forward declaration

using namespace std;

struct Trap {
  explicit Trap(double difficulty) : difficulty(difficulty) {}
  
  double difficulty;
};
#pragma once

#include <string>
#include <map>
#include <memory>

#include "interpretercommands.h"

class GameSystem;

using namespace std;

class InterpreterSystem {
public:
  explicit InterpreterSystem(GameSystem* game_system)
      : game_system_(game_system) {};

  ~InterpreterSystem() {
    // Clean up map after use.
    map<string, Command*>::iterator it;
    for (it = commands.begin(); it != commands.end(); ++it) {
      Command* pointer = it->second;
      delete pointer;
    }
  };

  void Update();

  static map<string, Command*> commands;

private:
  GameSystem* game_system_;
};
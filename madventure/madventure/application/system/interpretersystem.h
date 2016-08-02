#pragma once

#include <string>
#include <map>
#include <memory>

#include "commands.h"
#include "debugcommands.h"

class GameSystem;

using namespace std;

class InterpreterSystem {
public:
  explicit InterpreterSystem(GameSystem* game_system)
      : game_system_(game_system) {};

  ~InterpreterSystem() {
    // Clear maps.
    map<string, Command*>::iterator it;
    for (it = commands.begin(); it != commands.end(); ++it) {
      Command* pointer = it->second;
      delete pointer;
    }
    for (it = debug_commands.begin(); it != debug_commands.end(); ++it) {
      Command* pointer = it->second;
      delete pointer;
    }
  };

  void Update();

  static map<string, Command*> commands;
  static map<string, Command*> debug_commands;
private:
  GameSystem* game_system_;

  Command* FindCommand(map<string, Command*> table, const string keyword);
};
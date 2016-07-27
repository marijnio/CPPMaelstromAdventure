#pragma once

#include <string>
#include <map>
#include <memory>

#include "gamesystem.h"

#include "interpretercommands.h"

using namespace std;

class InterpreterSystem {
public:
  explicit InterpreterSystem(shared_ptr<GameSystem> game_system)
      : game_system_(game_system) {};

  ~InterpreterSystem() {
    // Clean up map after use.
    std::map<string, Command*>::iterator it;
    for (it = commands_.begin(); it != commands_.end(); ++it) {
      Command* pointer = it->second;
      delete pointer;
    }
  };

  void update();

private:
  map<string, Command*> commands_ = {
    { "inspect", new InspectCommand() },
    { "quit", new QuitCommand() }
  };

  shared_ptr<GameSystem> game_system_;

};
#pragma once

#include <string>
#include <map>

#include "entityx/entityx.h"

#include "interpretercommands.h"

namespace ex = entityx;
using namespace std;

class InterpreterSystem {
private:
  map<string, Command*> commands_ = {
    { "inspect", new InspectCommand() },
    { "quit", new QuitCommand() }
  };

public:
  explicit InterpreterSystem() {};
  ~InterpreterSystem() {
    // Clean up map after use.
    std::map<string, Command*>::iterator it;
    for (it = commands_.begin(); it != commands_.end(); ++it) {
      Command* pointer = it->second;
      delete pointer;
    }
  };

  void update(GameSystem game_system);

};
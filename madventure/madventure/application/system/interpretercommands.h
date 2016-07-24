#pragma once

#include <vector>
#include <string>

#include "entityx/entityx.h"

#include "../event/gamequitevent.h"

namespace ex = entityx;
using namespace std;

class Command {
public:
  Command() {}

  virtual void execute(ex::EntityManager &entities, ex::EventManager &events,
                       vector<string> words) = 0;
};

class InspectCommand : public Command {
public:
  InspectCommand() {}
  void execute(ex::EntityManager &entities, ex::EventManager &events,
               vector<string> words) {
    std::cout << "Inspecting..." << std::endl;
  }
};

class QuitCommand : public Command {
public:
  QuitCommand() {}
  void execute(ex::EntityManager &entities, ex::EventManager &events,
               vector<string> words) {
    events.emit<GameQuitEvent>();
  }
};

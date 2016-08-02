#pragma once

#include "commands.h"

class PositionCommand : public Command {
public:
  PositionCommand() {}
  void Execute(GameSystem* game_system, vector<string> words);
};
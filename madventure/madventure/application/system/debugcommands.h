#pragma once

#include "commands.h"

class PrintPositionCommand : public Command {
public:
  PrintPositionCommand() {}
  void Execute(GameSystem* game_system, vector<string> words);
};

class PrintPathsCommand : public Command {
public:
  PrintPathsCommand() {}
  void Execute(GameSystem* game_system, vector<string> words);
};

class PrintMapCommand : public Command {
public:
  PrintMapCommand() {}
  void Execute(GameSystem* game_system, vector<string> words);
};

class DistanceToGatewayCommand : public Command {
public:
  DistanceToGatewayCommand() {}
  void Execute(GameSystem* game_system, vector<string> words);
};

class SpanningTreeCommand : public Command {
public:
  SpanningTreeCommand() {}
  void Execute(GameSystem* game_system, vector<string> words);
};

class DamagePlayerCommand : public Command {
public:
  DamagePlayerCommand() {}
  void Execute(GameSystem* game_system, vector<string> words);
};
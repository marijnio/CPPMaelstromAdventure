#pragma once

#include <vector>
#include <string>

class GameSystem;

using namespace std;

class Command {
public:
  Command() {}

  virtual void Execute(GameSystem* game_system, vector<string> words) = 0;
};

class InspectCommand : public Command {
public:
  InspectCommand() {}
  void Execute(GameSystem* game_system, vector<string> words);

  static vector<string> subjects;
};

class GoCommand : public Command {
public:
  GoCommand() {}
  void Execute(GameSystem* game_system, vector<string> words);
};

class HelpCommand : public Command {
public:
  HelpCommand() {}
  void Execute(GameSystem* game_system, vector<string> words);
};

class QuitCommand : public Command {
public:
  QuitCommand() {}
  void Execute(GameSystem* game_system, vector<string> words);
};
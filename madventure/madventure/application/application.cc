#include "application.h"
#include "system/interpretersystem.h"
#include "system/levelsystem.h"

Application::Application() {
  game_system_ = new GameSystem();
  interpreter_system_ = new InterpreterSystem();
  level_system_ = new LevelSystem();
  
  game_system_->configure();
  interpreter_system_->configure();
  level_system_->configure();
}

void Application::update() {
  game_system_->update();
  interpreter_system_->update();
  level_system_->update();
}

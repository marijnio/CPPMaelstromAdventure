#include "application.h"

Application::Application() {
  game_system_ = make_shared<GameSystem>();
  interpreter_system_ = make_shared<InterpreterSystem>(game_system_);
}

void Application::update() {
  game_system_->update();
  interpreter_system_->update();
}

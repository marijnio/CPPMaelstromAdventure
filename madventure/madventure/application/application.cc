#include "application.h"

Application::Application() {
  game_system_ = make_shared<GameSystem>();
  interpreter_system_ = make_shared<InterpreterSystem>(game_system_);
  game_system_->Init();
}

void Application::Update() {
  game_system_->Update();
  interpreter_system_->Update();
}

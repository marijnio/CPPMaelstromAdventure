#include "application.h"

Application::Application() {
  game_system_ = make_shared<GameSystem>();
  game_system_->Init();
}

void Application::Update() {
  game_system_->Update();
}

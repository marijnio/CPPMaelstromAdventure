#include "application.h"
#include "system/interpretersystem.h"
#include "system/levelsystem.h"

Application::Application() : entityx::EntityX() {
  systems.add<GameSystem>();
  systems.add<InterpreterSystem>();
  systems.add<LevelSystem>();
  systems.configure();
}

void Application::update(entityx::TimeDelta dt) {
  systems.update<GameSystem>(dt);
  systems.update<InterpreterSystem>(dt);
  systems.update<LevelSystem>(dt);
}

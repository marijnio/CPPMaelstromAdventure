#include "application.h"
#include "system/levelsystem.h"
#include "system/interpretersystem.h"

Application::Application() : entityx::EntityX() {
  systems.add<InterpreterSystem>();
  systems.add<LevelSystem>();
  systems.configure();
}

void Application::update(entityx::TimeDelta dt) {
  systems.update_all(dt);
}

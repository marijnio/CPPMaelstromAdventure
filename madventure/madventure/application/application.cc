#include "application.h"
#include "system/levelsystem.h"

Application::Application() : entityx::EntityX() {
  systems.add<LevelSystem>();
  systems.configure();
}

void Application::update(entityx::TimeDelta dt) {
  systems.update_all(dt);
}

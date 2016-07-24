#include <iostream>
#include <string>

#include "gamesystem.h"
#include "../event/createlevelevent.h"
#include "../component/level.h"
#include "../component/area.h"
#include "../component/player.h"
#include "../component/location.h"

using namespace std;

void GameSystem::configure(ex::EventManager &events) {
  events.subscribe<GameQuitEvent>(*this);
}

void GameSystem::initialize(ex::EntityManager &entities, ex::EventManager &events) {
  std::cout << "Welcome to Maelstrom Adventure.\n";
  events.emit<CreateLevelEvent>(entities);
  
  ex::ComponentHandle<Level> level;
  for (ex::Entity entity : entities.entities_with_components(level)) {
    NavGraphNode<ex::Entity*> first_node = level->graph->GetNode(0);

    // Create player entity.
    ex::Entity player = entities.create();
    player.assign<Player>();
    player.assign<Location>(first_node.ExtraInfo());

    //ex::ComponentHandle<Player> player_handle = player.component<Player>();

    break;
  }

  initialized_ = true;
}

void GameSystem::update(ex::EntityManager &entities, ex::EventManager &events,
                        ex::TimeDelta dt) {
  if (initialized_ == false) {
    initialize(entities, events);
  }
}

void GameSystem::receive(const GameQuitEvent &event) {
  std::cout << "Thank you for playing.\n" << std::endl;
  finished_ = true;
}
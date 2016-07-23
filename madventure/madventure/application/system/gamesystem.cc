#include <iostream>
#include <string>

#include "gamesystem.h"
#include "../event/createlevelevent.h"

using namespace std;

void GameSystem::configure(ex::EventManager &events) {
  events.subscribe<GameQuit>(*this);
  events.subscribe<ex::EntityCreatedEvent>(*this);
}

void GameSystem::update(ex::EntityManager & es, ex::EventManager & events,
                        ex::TimeDelta dt) {

}

void GameSystem::receive(const GameQuit &gamequit) {
  std::cout << "Game quit command received.\n" << std::endl;
  finished_ = true;
}

void GameSystem::receive(const ex::EntityCreatedEvent &entity_created_event) {
  std::cout << "Game system recognised creation of entity.\n" << std::endl;
}
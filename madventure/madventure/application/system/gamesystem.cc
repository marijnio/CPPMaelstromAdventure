#include <iostream>
#include <string>

#include "gamesystem.h"
#include "../event/createlevel.h"

using namespace std;

void GameSystem::configure(ex::EventManager &events) {
  events.subscribe<GameQuit>(*this);
  events.emit<CreateLevel>();
}

void GameSystem::update(ex::EntityManager & es, ex::EventManager & events,
                        ex::TimeDelta dt) {

}

void GameSystem::receive(const GameQuit &gamequit) {
  std::cout << "Game quit command received.\n" << std::endl;
  finished_ = true;
}

#include <iostream>
#include <string>

#include "gamesystem.h"

using namespace std;

void GameSystem::configure(ex::EventManager &events) {
  events.subscribe<GameQuit>(*this);
}

void GameSystem::update(ex::EntityManager & es, ex::EventManager & events,
                        ex::TimeDelta dt) {

}

void GameSystem::receive(const GameQuit &gamequit) {
  std::cout << "Game quit command received.\n" << std::endl;
  finished_ = true;
}

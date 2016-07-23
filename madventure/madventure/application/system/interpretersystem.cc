#include <iostream>
#include <string>

#include "interpretersystem.h"
#include "../event/gamequit.h"
#include "../event/createlevelevent.h"

using namespace std;

void InterpreterSystem::update(ex::EntityManager &es,
                               ex::EventManager &events, ex::TimeDelta dt) {
  string mystr;
  cout << "\n>";
  getline(cin, mystr);
  cout << "You said " << mystr << ".\n";
  if (mystr == "quit") {
    events.emit<GameQuit>();
  }
}

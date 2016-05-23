#include <iostream>
#include <string>

#include "interpretersystem.h"

using namespace std;

InterpreterSystem::InterpreterSystem() {
}

void InterpreterSystem::update(ex::EntityManager & es,
                               ex::EventManager & events, ex::TimeDelta dt) {
  string mystr;
  cout << "\n>";
  getline(cin, mystr);
  cout << "You said " << mystr << ".\n";
}

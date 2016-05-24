#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "entityx/entityx.h"
#include "application/application.h"

int main(int args[]) {
  
  Application app;

  std::cout << "Welcome to Maelstrom Adventure.\n";

  do {
    app.update(NULL);
  } while (!app.is_finished());

  _CrtDumpMemoryLeaks();

  return 0;
}
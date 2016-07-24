#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "application/application.h"

int main(int args[]) {
  
  Application app;

  do {
    app.update(NULL);
  } while (!app.is_finished());

  _CrtDumpMemoryLeaks();

  return 0;
}
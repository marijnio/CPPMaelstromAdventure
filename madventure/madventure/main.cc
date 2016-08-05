#include <vld.h>

#include "application/application.h"

int main(int args[]) {

  // Use time as seeds for the random number generators.
  srand(static_cast <unsigned int> (time(0)));
  
  Application app;

  do {
    app.Update();
  } while (!app.is_finished());

  return 0;
}

#include <vld.h> 

#include "application/application.h"

int main(int args[]) {
  
  Application app;

  do {
    app.Update();
  } while (!app.is_finished());

  return 0;
}

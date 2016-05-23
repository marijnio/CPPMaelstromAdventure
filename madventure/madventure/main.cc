#include "entityx\entityx.h"
#include "application\application.h"

int main(int args[]) {
  
  Application app;

  std::cout << "Welcome to Maelstrom Adventure.\n";

  while (true) {
    app.update(NULL);
  }

  return 0;
}
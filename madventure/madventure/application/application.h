#ifndef MADVENTURE_APPLICATION_H_
#define MADVENTURE_APPLICATION_H_

#include "entityx/entityx.h"
#include "system/gamesystem.h"

namespace ex = entityx;

class Application : public ex::EntityX {
public:
  explicit Application();

  void update(ex::TimeDelta dt);

  bool is_finished() { return systems.system<GameSystem>()->is_finished(); }
};

#endif // MADVENTURE_APPLICATION_H_
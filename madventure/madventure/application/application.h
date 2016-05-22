#ifndef MADVENTURE_APPLICATION_H_
#define MADVENTURE_APPLICATION_H_

#include "entityx\entityx.h"

namespace ex = entityx;

class Application : public ex::EntityX {
public:
  explicit Application();

  void update(ex::TimeDelta dt);
};

#endif // MADVENTURE_APPLICATION_H_
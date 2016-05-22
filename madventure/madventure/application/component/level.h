#ifndef MADVENTURE_APPLICATION_COMPONENT_LEVEL_H_
#define MADVENTURE_APPLICATION_COMPONENT_LEVEL_H_

struct Level {
  explicit Level(int x_size, int y_size) : x_size(x_size), y_size(y_size) {}

  int x_size, y_size;
};

#endif // MADVENTURE_APPLICATION_COMPONENT_LEVEL_H_
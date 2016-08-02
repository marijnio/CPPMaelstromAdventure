#pragma once

#include <memory>

struct Area; // Forward declaration

using namespace std;

struct Gateway {
  explicit Gateway(shared_ptr<Area> from, shared_ptr<Area> to)
      : from(from), to(to) {}
  shared_ptr<Area> from;
  shared_ptr<Area> to;
};
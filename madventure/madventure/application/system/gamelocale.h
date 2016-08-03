#pragma once

#include <string>
#include <map>

using namespace std;

class GameLocale {
public:
  GameLocale();

  string GetAreaDescription(int climate);
  string GetTimeDescription(int time);
private:
  map<string, string> area_descriptions_;
};
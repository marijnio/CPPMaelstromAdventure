#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "../utility/json.hpp"

using namespace std;
using json = nlohmann::json;

class GameInfoParser {
public:
  GameInfoParser() {}
  json ReadJson();
};

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "../utility/json.hpp"

using namespace std;
using json = nlohmann::json;

enum DataType {
  kAreaDescription
};

class GameInfoParser {
public:
  GameInfoParser() {}

  map<string, string> GetAreaDescriptions(string url);
private:
  json ReadJson(string url);
};

#include "gameinfoparser.h"


json GameInfoParser::ReadJson() {

  string line;
  // fill a stream with JSON text
  std::stringstream ss;
  ifstream myfile("application/assets/area_description.json");
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      ss << line;
    }
    myfile.close();
  }
  else cout << "Unable to open file";

  // create JSON from stream
  json j_complete(ss);
  std::cout << std::setw(2) << j_complete << "\n\n";

  // iterate the array
  for (json::iterator it = j_complete.begin(); it != j_complete.end(); ++it) {
    std::cout << *it << "\n\n";
  }

  return j_complete;
}
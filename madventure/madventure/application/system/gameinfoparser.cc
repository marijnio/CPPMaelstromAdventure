#include "gameinfoparser.h"

json GameInfoParser::ReadJson(string url) {
  // Fill a stream with JSON text
  string line;
  std::stringstream ss;
  ifstream myfile(url);
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      ss << line;
    }
    myfile.close();
  } else {
    cout << "Unable to open file at url <" << url << ">\n";
    return json();
  }

  // Create JSON from stream
  json object(ss);

  // Pretty print result
  //std::cout << std::setw(2) << payload << "\n\n";

  // iterate the array
  //for (json::iterator it = j_complete.begin(); it != j_complete.end(); ++it) {
  //  std::cout << *it << "\n\n";
  //}

  return object;
}

map<string, string> GameInfoParser::GetAreaDescriptions(string url) {
  map<string, string> data;
  json object = ReadJson(url);
  // Shift two objects down towards array.
  object = object.front().front();

  // Iterate the array
  for (json::iterator alfa = object.begin(); alfa != object.end(); ++alfa) {
    json pair = *alfa;
    string a = pair.front().get<string>();
    string b = pair.back().get<string>();
    data.insert(make_pair(a, b));
  }
  return data;
}

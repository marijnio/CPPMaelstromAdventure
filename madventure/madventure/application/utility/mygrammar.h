#pragma once

#include <string>
#include <vector>

using namespace std;

inline string EnumerateWords(vector<string> words) {
  string sentence;
  vector<string>::iterator it;
  for (it = words.begin(); it != words.end(); ++it) {
    sentence = sentence.append(*it);

    // Separate with comma if not at last in map.
    if ((it + 1) == words.end()) {
      sentence = sentence.append(".");
    } else if ((it + 2) == words.end()) {
      sentence = sentence.append(" and ");
    } else {
      sentence = sentence.append(", ");
    }
  }
  return sentence;
}
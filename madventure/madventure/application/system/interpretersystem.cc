#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <regex>

#include "interpretersystem.h"
#include "../event/gamequitevent.h"

Command* InterpreterSystem::FindCommand(map<string, Command*> table, const string keyword) {
  std::map<std::string, Command*>::iterator it;
  if (table.find(keyword) != table.end()) {
    it = table.find(keyword);
    assert(it != table.end()); // Verify
    return it->second;
  }
  return nullptr;
}

void InterpreterSystem::Update() {
  cout << ">";

  string line;
  getline(cin, line); // Read one line from cin.
  // Transform input to upper case.
  std::transform(line.begin(), line.end(), line.begin(), ::toupper);
  stringstream buffer(line);

  vector<string> words;
  // Copy each word from line to words.
  copy(istream_iterator<string>(buffer),
    istream_iterator<string>(),
    back_inserter(words));

  if (words.empty()) {
    cout << "No command received. Type help for a list of commands.\n\n";
    return;
  }

  string keyword = words[0];

  // Find match for keyword in known commands map.
  Command* c = FindCommand(commands, keyword);

  if (c == nullptr) {
    // Not found, try next map.
    c = FindCommand(debug_commands, keyword);
  }

  if (c == nullptr) {
    // Not found, try synonyms
    map<string, vector<string>>::iterator it;
    if (thesaurus.find(keyword) != thesaurus.end()) {
      // Synonym found.
      it = thesaurus.find(keyword);
      // Get translation and replace given words.
      words = it->second;
      // Find command of translation.
      c = FindCommand(commands, words[0]);
    }
  }

  if (c != nullptr) {
    // Found, execute.
    c->Execute(game_system_, words);
    cout << "\n";
  } else {
    // Not found.
    cout << "Unable to interpret. Type help for a list of commands.\n\n";
    return;
  }
}

// Checks if a string contains only alphabetic letters.
// Uses a C++11 regex function to determinate.
inline bool ContainsNonAlpha(string word) {
  return !regex_match(word, regex("^[A-Za-z]+$"));
}

string InterpreterSystem::RequestWord(string prompt) {
  cout << prompt;

  string line;
  getline(cin, line); // Read one line from cin.
  stringstream buffer(line);

  // Check if the input contains non-alphabetic characters.
  if (ContainsNonAlpha(line)) {
    // Ask the word again using a recursive function call.
    return RequestWord(prompt);
  }
  return line;
}

// C++11 uniform initialization of command maps.

map<string, Command*> InterpreterSystem::commands = {
  { "GO", new GoCommand() },
  { "INSPECT", new InspectCommand() },
  { "HEAL", new HealCommand() },
  { "HELP", new HelpCommand() },
  { "QUIT", new QuitCommand() }
};

map<string, vector<string>> InterpreterSystem::thesaurus = {
  { "NORTH", { "GO", "NORTH" }},
  { "EAST", { "GO", "EAST" }},
  { "SOUTH", { "GO", "SOUTH" }},
  { "WEST",{ "GO", "WEST" }},
  { "DOWN",{ "GO", "DOWN" }},
  { "UP",{ "GO", "UP" }}
};

map<string, Command*> InterpreterSystem::debug_commands = {
  { "PRINTPOSITION", new PrintPositionCommand() },
  { "PRINTPATHS", new PrintPathsCommand() },
  { "PRINTMAP", new PrintMapCommand() },
  { "GATEWAY", new DistanceToGatewayCommand() },
  { "SPANNINGTREE", new SpanningTreeCommand() },
  { "DAMAGEPLAYER", new DamagePlayerCommand() }
};
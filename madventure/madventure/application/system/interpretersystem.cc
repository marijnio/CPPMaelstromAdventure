#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

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
  // Transform input to lower case.
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

// C++11 uniform initialization of command maps.

map<string, Command*> InterpreterSystem::commands = {
  { "GO", new GoCommand() },
  { "INSPECT", new InspectCommand() },
  { "HELP", new HelpCommand() },
  { "QUIT", new QuitCommand() }
};

map<string, Command*> InterpreterSystem::debug_commands = {
  { "PRINTPOSITION", new PrintPositionCommand() },
  { "PRINTPATHS", new PrintPathsCommand() },
  { "PRINTMAP", new PrintMapCommand() },
  { "GATEWAY", new DistanceToGatewayCommand() },
  { "SPANNINGTREE", new SpanningTreeCommand() }
};
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
  stringstream buffer(line);
  vector<string> words;

  // Copy each word from line to words.
  copy(istream_iterator<string>(buffer),
    istream_iterator<string>(),
    back_inserter(words));

  // Find match for keyword in known commands map.
  Command* c = FindCommand(commands, words[0]);

  if (c == nullptr) {
    // Not found, try next map.
    c = FindCommand(debug_commands, words[0]);
  }

  if (c != nullptr) {
    // Found, execute.
    c->Execute(game_system_, words);
  } else {
    // Not found.
  }

  cout << '\n';


  //String input = read();
  //String[] inputArray = input.split("\\s"); // Split at every space
  //                                          // Convert array to list
  //List<String> words = new ArrayList<String>(Arrays.asList(inputArray));

  //// Interpret the first word as a command
  //if (commands.containsKey(words.get(0))) {
  //  // The first word is in the dictionary
  //  commands.get(words.get(0)).execute(gameSystem, words);
  //}
  //else if (synonyms.containsKey(words.get(0))) {
  //  // The first word is a synonym so get reference as individual words
  //  List<String> reference = Arrays.asList(synonyms.get(words.get(0)
  //    ).split("\\s"));
  //  // Consume the synonym
  //  words.remove(0);
  //  // Add synonym reference words to the rest of the words
  //  words.addAll(0, reference);
  //  commands.get(words.get(0)).execute(gameSystem, words);
  //}
  //else {
  //  System.out.println("That is no verb I recognize.");
  //}
  //System.out.println();

}

// C++11 uniform initialization of command maps.

map<string, Command*> InterpreterSystem::commands = {
  { "go", new GoCommand() },
  { "inspect", new InspectCommand() },
  { "help", new HelpCommand() },
  { "quit", new QuitCommand() }
};
map<string, Command*> InterpreterSystem::debug_commands = {
  { "printposition", new PrintPositionCommand() },
  { "printpaths", new PrintPathsCommand() }
};
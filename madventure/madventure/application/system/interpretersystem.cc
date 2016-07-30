#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

#include "interpretersystem.h"
#include "../event/gamequitevent.h"

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

  //cout << "Input contains:";
  //for (vector<string>::iterator it = words.begin();
  //     it != words.end(); ++it) {
  //  cout << ' ' << *it;
  //  cout << '\n';
  //}

  // Check if keyword is present in command map.
  if (commands.find(words[0]) != commands.end()) {
    
    std::map<std::string, Command*>::iterator it = commands.find(words[0]);
    assert(it != commands.end()); // Verify

    it->second->Execute(game_system_, words);
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

// C++11 uniform initialization of command map.
map<string, Command*> InterpreterSystem::commands = {
  { "inspect", new InspectCommand() },
  { "help", new HelpCommand() },
  { "quit", new QuitCommand() }
};
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

#include "interpretersystem.h"
#include "../event/gamequitevent.h"
#include "../event/createlevelevent.h"

void InterpreterSystem::update(ex::EntityManager &entities,
                               ex::EventManager &events, ex::TimeDelta dt) {
  string line;
  getline(cin, line); // Read one line from cin.
  stringstream buffer(line);
  vector<string> words;

  // Copy each word from line to words.
  copy(istream_iterator<string>(buffer),
    istream_iterator<string>(),
    back_inserter(words));

  cout << "Input contains:";
  for (vector<string>::iterator it = words.begin();
       it != words.end(); ++it) {
    cout << ' ' << *it;
    cout << '\n';
  }
  cout << '\n';

  // Check if keyword is present in command map.
  if (commands_.find(words[0]) != commands_.end()) {
    std::cout << "map contains key world!\n";
    
    std::map<std::string, Command*>::iterator it = commands_.find(words[0]);
    assert(it != commands_.end()); // Verify

    it->second->execute(entities, events, words);
  }



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

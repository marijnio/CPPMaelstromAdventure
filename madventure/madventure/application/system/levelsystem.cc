#include <list>

#include "levelsystem.h"

using namespace std;

LevelSystem::LevelSystem() {
}

vector<int> LevelSystem::GetAreaDirections(shared_ptr<Area> area) {
  // Extract graph from area
  auto graph = area->level->graph;

  list<NavGraphEdge> edges = graph->GetEdgeList(area->node_index);

  vector<int> directions;

  for (list<NavGraphEdge>::iterator it = edges.begin(); it != edges.end(); ++it) {
    cout << "Edge leading to node with index " << it->To() << "\n";
    directions.push_back(it->To());
  }

  return directions;
}


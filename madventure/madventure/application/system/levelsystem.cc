#include <list>

#include "levelsystem.h"

using namespace std;

vector<int> LevelSystem::GetNeighboringNodeIndices(shared_ptr<Area> area) {
  // Extract graph from area
  auto graph = area->level->graph;

  list<NavGraphEdge> edges = graph->GetEdgeList(area->node_index);

  vector<int> indices;

  for (list<NavGraphEdge>::iterator it = edges.begin(); it != edges.end(); ++it) {
    cout << "Edge leading to node with index " << it->To() << "\n";
    indices.push_back(it->To());
  }

  return indices;
}



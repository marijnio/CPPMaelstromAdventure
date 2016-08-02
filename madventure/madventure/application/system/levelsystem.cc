#include <list>

#include "levelsystem.h"
#include "../graph/HandyGraphFunctions.h"

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

shared_ptr<Level> LevelSystem::NewLevel(int columns, int rows) {
  assert(world_);
  assert(columns > 0 && rows > 0);

  // Make new bi-directional graph.
  auto graph = make_shared<SparseGraph<NavGraphNode<shared_ptr<Area>>, NavGraphEdge>>(false);
  // Fill graph with a grid of nodes.
  GraphHelper_CreateGrid(*graph, columns, rows, columns, rows, false);

  // Place graph in a new level.
  shared_ptr<Level> level = make_shared<Level>(graph);

  // Create areas in level for every node and attach.
  for (int i = 0; i < graph->NumNodes(); i++) {
    shared_ptr<Area> area = make_shared<Area>(i, level);
    graph->GetNode(i).SetExtraInfo(area);
  }

  // Place level in world.
  world_->levels.push_back(level);

  return level;
}

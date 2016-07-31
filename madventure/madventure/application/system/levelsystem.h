#pragma once

#include <memory>
#include <vector>

#include "../model/area.h"
#include "../model/level.h"
#include "../graph/SparseGraph.h"

template <class graph_type>
class LevelSystem {
public:
  LevelSystem();

  vector<int> GetNeighboringNodes(shared_ptr<Area> area);
};

template <class graph_type>
vector<graph_type::NodeType> LevelSystem::GetNeighboringNodes(shared_ptr<Area> area) {
  // Extract graph from area
  auto graph = area->level->graph;

  list<graph_type::EdgeType> edges = graph->GetEdgeList(area->node_index);

  vector<graph_type::EdgeType> directions;

  for (list<graph_type::EdgeType>::iterator it = edges.begin(); it != edges.end(); ++it) {
    cout << "Edge leading to node with index " << it->To() << "\n";
    directions.push_back(it->To());
  }

  return directions;
}


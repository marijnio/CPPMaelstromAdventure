#include <list>
#include <math.h>

#include "levelsystem.h"
#include "../graph/HandyGraphFunctions.h"

using namespace std;

vector<int> LevelSystem::NeighboringNodeIndexes(shared_ptr<Area> area) {
  auto graph = area->level->graph;
  auto edges = graph->GetEdgeList(area->node_index);

  vector<int> indexes;
  for (list<NavGraphEdge>::iterator it = edges.begin(); it != edges.end(); ++it) {
    Vector2D position = graph->GetNode(it->To()).Pos();
    indexes.push_back(it->To());
  }
  return indexes;
}

inline int PositiveModulo(int i, int n) {
  return (i % n + n) % n;
}

int LevelSystem::RelativeVectorAngle(const Vector2D alpha, const Vector2D beta) {
  // Make a vector which spans the distance between alpha and beta.
  Vector2D gamma = Vector2D(beta.x - alpha.x, beta.y - alpha.y);
  double theta = atan2(gamma.y, gamma.x);
  double pi = atan(1) * 4;
  int degrees = static_cast<int>(round(180 * theta / pi));
  int remainder = PositiveModulo(degrees, 360);
  return remainder;
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


vector<Direction> LevelSystem::GetDirections(shared_ptr<Area> area, vector<int> neighbors) {
  auto graph = area->level->graph;
  Vector2D this_position = graph->GetNode(area->node_index).Pos();
  vector<int>::iterator it;
  vector<Direction> directions;
  for (it = neighbors.begin(); it != neighbors.end(); ++it) {
    // For every neighboring node index.
    int index = *it;
    // Get node and its position.
    auto neighbor = graph->GetNode(index);
    Vector2D that_position = neighbor.Pos();
    // Find at which angle it is positioned from current node.
    int angle = LevelSystem::RelativeVectorAngle(this_position, that_position);
    // Add the direction of that angle to the list.
    directions.push_back(Direction(angle));
  }
  return directions;
}

shared_ptr<Area> LevelSystem::RandomArea(shared_ptr<Level> level) {
  auto graph = level->graph;
  auto node = graph->GetNode(graph->RandomNode());
  return node.ExtraInfo();
}

vector<shared_ptr<Area>> LevelSystem::GetAreasInLevel(shared_ptr<Level> level) {
  auto nodes = level->graph->GetNodeVector();
  vector<shared_ptr<Area>> areas;
  vector<NavGraphNode<shared_ptr<Area>>>::iterator it;
  for (it = nodes.begin(); it != nodes.end(); ++it) {
    areas.push_back(it->ExtraInfo());
  }
  return areas;
}

void LevelSystem::AddGateway(shared_ptr<Area> from, shared_ptr<Area> to) {
  auto gateway = make_shared<Gateway>(from, to);
  from->gateway = gateway;
  to->gateway = gateway;
}

void LevelSystem::PrintMap(shared_ptr<SparseGraph<NavGraphNode<shared_ptr<Area>>,
                           NavGraphEdge>> graph, shared_ptr<Player> player,
                           bool show_all) {
  int low_x = static_cast<int>(graph->LowestNodeX());
  int low_y = static_cast<int>(graph->LowestNodeY());
  int high_x = static_cast<int>(graph->HighestNodeX());
  int high_y = static_cast<int>(graph->HighestNodeY());

  // Retrieve all graph nodes.
  auto nodes = graph->GetNodeVector();
  // Print the map with row going from high x to low x.
  for (int i = high_x; i >= low_x; i--) {
    // For every node.
    vector<NavGraphNode<shared_ptr<Area>>>::iterator it;
    for (it = nodes.begin(); it != nodes.end(); ++it) {
      // Retrieve node x position.
      double node_x = static_cast<int>(round(it->Pos().x));
      // Is the node positioned in the row to print?
      if (node_x == i) {
        if (it->ExtraInfo()->visited == true || show_all == true) {
          if (player->area->node_index == it->Index()) {
            // Player present in area.
            cout << "x";
          } else if (it->ExtraInfo()->gateway) {
            // Gateway present in area.
            if (it->ExtraInfo()->gateway->from == it->ExtraInfo()) {
              cout << "w";
            } else {
              cout << "v";
            }
          } else {
            cout << "o";
          }
        }
        else {
          cout << "~";
        }
        double node_y = static_cast<int>(round(it->Pos().y));
        if (node_y != high_y) {
          cout << "-";
        }
      }

    }
    cout << "\n";
    if (i > low_x) {
      for (int j = low_y; j <= high_y; j++) {
        cout << "| ";
      }
    }
    cout << "\n";
  }

}
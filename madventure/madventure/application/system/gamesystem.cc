#include <iostream>
#include <string>
#include <assert.h>

#include "gamesystem.h"
#include "../graph/SparseGraph.h"
#include "../graph/HandyGraphFunctions.h"
#include "../model/level.h"

//#include "../event/createlevelevent.h"
//#include "../component/area.h"
//#include "../component/player.h"
//#include "../component/location.h"

using namespace std;

GameSystem::GameSystem() {
  std::cout << "Welcome to Maelstrom Adventure.\n";
  world_ = make_shared<World>();
  finished_ = false;
}

void GameSystem::Init() {
  NewLevel(3, 3);
}


  //events.emit<CreateLevelEvent>(entities);
  //
  //ex::ComponentHandle<Level> level;
  //for (ex::Entity entity : entities.entities_with_components(level)) {
  //  NavGraphNode<ex::Entity*> first_node = level->graph->GetNode(0);

  //  // Create player entity.
  //  ex::Entity player = entities.create();
  //  player.assign<Player>();
  //  player.assign<Location>(first_node.ExtraInfo());

  //  //ex::ComponentHandle<Player> player_handle = player.component<Player>();

  //  break;
  //}

void GameSystem::NewLevel(int columns, int rows) {
  assert(columns > 0 && rows > 0);

  // Make new bi-directional graph.
  auto graph = make_shared<SparseGraph<NavGraphNode<shared_ptr<Area>>, NavGraphEdge>>(false);
  // Fill graph with a grid of nodes.
  GraphHelper_CreateGrid(*graph, columns, rows, columns, rows, false);

  // Create areas for every node and attach.
  for (int i = 0; i < graph->NumNodes(); i++) {
    NavGraphNode<shared_ptr<Area>> current_node = graph->GetNode(i);
    shared_ptr<Area> area = make_shared<Area>(current_node);
    current_node.SetExtraInfo(area);
  }

  // Place graph in a new level.
  shared_ptr<Level> level = make_shared<Level>(graph);

  // Place level in world.
  world_->levels.push_back(level);
}

void GameSystem::update() {
}
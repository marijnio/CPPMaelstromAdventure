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
  finished_ = false;
  interpreter_system_ = new InterpreterSystem(this);
  level_system_ = new LevelSystem();
}

GameSystem::~GameSystem() {
  delete interpreter_system_;
}

void GameSystem::Init() {
  std::cout << "Welcome to Maelstrom Adventure.\n\n";

  // Create world and level.
  world_ = make_shared<World>();
  shared_ptr<Level> level = NewLevel(3, 3);

  // Select starting area.
  auto area = level->graph->GetNode(0).ExtraInfo();

  // Create player and place in area.
  player_ = make_shared<Player>(area);
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

shared_ptr<Level> GameSystem::NewLevel(int columns, int rows) {
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

void GameSystem::Update() {
  interpreter_system_->Update();
}
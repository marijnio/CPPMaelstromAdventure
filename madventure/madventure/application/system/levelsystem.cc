#include <memory>

#include "../utility/vector2D.h"

#include "levelsystem.h"

#include "../component/level.h"
#include "../graph/SparseGraph.h"
#include "../graph/HandyGraphFunctions.h"

using namespace std;

void LevelSystem::configure(ex::EventManager &events) {
  events.subscribe<CreateLevelEvent>(*this);
}

void LevelSystem::update(ex::EntityManager &entities,
                         ex::EventManager & events, ex::TimeDelta dt) {

}

ex::Entity LevelSystem::createLevel(ex::EntityManager &entities) {
  ex::Entity level = entities.create();

  // Create non-directed navigation graph.
  auto graph = new SparseGraph<NavGraphNode<ex::Entity*>, NavGraphEdge>(false);

  GraphHelper_CreateGrid(*graph, 4, 4, 4, 4, false);

  level.assign<Level>(*graph);

  ex::ComponentHandle<Level> level_handle = level.component<Level>();
  auto obtained_graph = level_handle->graph;
  for (int i = 0; i < obtained_graph->NumNodes(); i++) {
    NavGraphNode<ex::Entity*> current_node = obtained_graph->GetNode(i);
    ex::Entity area = entities.create();
    area.assign<Area>(current_node);
    current_node.SetExtraInfo(&area);

    //ex::ComponentHandle<Area> handle = current_node.ExtraInfo()->component<Area>();
  }

  return level;
}

void LevelSystem::receive(const CreateLevelEvent& create_level_event) {
  std::cout << "Creating level.\n" << std::endl;
  levels_.push_back(createLevel(create_level_event.es_));
}

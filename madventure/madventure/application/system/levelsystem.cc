#include <memory>

#include "levelsystem.h"

#include "../component/level.h"
#include "../graph/SparseGraph.h"
#include "../graph/HandyGraphFunctions.h"

using namespace std;

void LevelSystem::configure(ex::EventManager &events) {
  events.subscribe<CreateLevelEvent>(*this);
}

void LevelSystem::update(ex::EntityManager & es, ex::EventManager & events,
                         ex::TimeDelta dt) {

}

ex::Entity LevelSystem::createLevel(ex::EntityManager & es) {
  ex::Entity level = es.create();

  // Create non-directional navigation graph
  auto graph = new SparseGraph<NavGraphNode<>, NavGraphEdge>(false);

  GraphHelper_CreateGrid(*graph, 1, 1, 3, 3);

  level.assign<Level>(graph);

  cout << "edges: " << graph->NumEdges() << "; nodes: " << graph->NumNodes()
    << endl;
  //level.
  return level;
}

void LevelSystem::receive(const CreateLevelEvent& create_level_event) {
  std::cout << "Creating level.\n" << std::endl;
  createLevel(create_level_event.es_);
}

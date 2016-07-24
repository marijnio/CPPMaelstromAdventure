#include "interpretercommands.h"

#include "../component/player.h"
#include "../component/location.h"
#include "../component/area.h"

#include "../system/levelsystem.h"

void InspectCommand::execute(GameSystem game_system, vector<string> words) {

  // Retrieve player location component.
  //ex::ComponentHandle<Player> player;
  //ex::ComponentHandle<Location> location;
  //for (ex::Entity entity : entities.entities_with_components(player, location)) {
    // Retrieve area component.
  //ex::Entity area_entity = *(location->area_);
  //ex::ComponentHandle<Area> area = area_entity.component<Area>();
  //  break; // There is only one player so stop at first.
  //}
  

  //UUID playerID = gameSystem.getGameWorld().getPlayer().getID();
  //TransformComponent transform = gameSystem.getTransformComponent(playerID);

  //// Retrieve the player's location component
  //UUID levelID = gameSystem.getGameWorld().getLevel().getID();
  //LevelComponent level = gameSystem.getLevelComponent(levelID);

  //TimeComponent timeComponent = gameSystem.getTimeComponent(levelID);

  //// Retrieve the accompanying node
  //NavigationGraphNode node = transform.getLocation().getNode();

  //// Retrieve the area ID
  //UUID areaID = node.getArea().getOwner().getID();

  //AreaComponent areaComponent = gameSystem.getAreaComponent(areaID);

  //// Save the node index
  //int nodeIndex = node.getIndex();

  //timeComponent.printTime();
  //areaComponent.printWeatherDescription();
  //areaComponent.printEnemies();
  //level.describeAvailableDirections(nodeIndex);
}

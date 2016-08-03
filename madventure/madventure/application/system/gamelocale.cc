#include "gamelocale.h"

#include "gameinfoparser.h"

GameLocale::GameLocale() {
  area_descriptions_ = GameInfoParser().GetAreaDescriptions("application/assets/area_description.json");
}

string GameLocale::GetAreaDescription(int climate) {
  string tag;
  tag.append("TXT_KEY_BEAUFORT_DESCRIPTION_");
  tag.append(to_string(climate));
  return area_descriptions_.at(tag);
}


string GameLocale::GetTimeDescription(int time) {
  // The hour of day is used to describe the time.

  string tag = "TXT_KEY_TIME_DESCRIPTION_";

  if (time > 5 && time < 12) {
    // Morning
    tag.append("MORNING");
  }
  else if (time < 13) {
    // Noon
    tag.append("NOON");
  }
  else if (time < 18) {
    // Afternoon
    tag.append("AFTERNOON");
  }
  else if (time < 20) {
    // Evening
    tag.append("EVENING");
  }
  else {
    // Night
    tag.append("NIGHT");
  }

  return area_descriptions_.at(tag);
}
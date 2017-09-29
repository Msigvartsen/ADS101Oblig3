#include <iostream>


struct PlayerProfile {
  std::string key;
  std::string nick;
  std::string email;
  int rating;

  bool operator == (const PlayerProfile& t2) const { return key == t2.key; }
};


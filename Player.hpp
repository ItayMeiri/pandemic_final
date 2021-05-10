//
// Created by ischelle on 05/05/2021.
//

#pragma once

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <string>

namespace pandemic {
class Player {
private:
public:
  std::string my_role;
  City current_city;              // The current city the player is in
  std::unordered_set<City> cards; // The player cards
  Board &board;
  Player(Board &board, City city); // init
  virtual std::string role();
  virtual Player &take_card(City city);
  virtual Player &build();
  virtual Player &drive(City city);
  virtual Player &fly_direct(City city);
  virtual Player &treat(City city);
  virtual Player &fly_charter(City city);
  virtual Player &fly_shuttle(City city);
  virtual Player &discover_cure(Color color);
  void remove_cards();
};
} // namespace pandemic

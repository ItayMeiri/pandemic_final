//
// Created by ischelle on 05/05/2021.
//

#include "Medic.hpp"

namespace pandemic {

Medic::Medic(Board &board, City city) : Player(board, city) {
  Color clr = board.get_color(current_city);
  if (board.cured(clr)) {
    board.data_map.at(city).level = 0;
  }
  this->my_role = "Medic";
}
Player &Medic::treat(City city) {

  if (city != current_city) {
    throw std::invalid_argument("You're not in this city");
  }

  if (board.get_level(current_city) <= 0) {
    throw std::invalid_argument("The level is already 0");
  }
  board.data_map.at(current_city).level = 0;
  return *this;
}

Player &Medic::drive(City city) {
  Player::drive(city);
  AutoHeal();
  return *this;
}

Player &Medic::fly_charter(City city) {
  Player::fly_charter(city);
  AutoHeal();
  return *this;
}

Player &Medic::fly_shuttle(City city) {
  Player::fly_shuttle(city);
  AutoHeal();
  return *this;
}
Player &Medic::fly_direct(City city) {
  Player::fly_direct(city);
  AutoHeal();
  return *this;
}
void Medic::AutoHeal() {
  if (board.cured(board.get_color(current_city))) {
    board.data_map.at(current_city).level = 0;
  }
}
} // namespace pandemic

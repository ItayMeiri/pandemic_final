//
// Created by ischelle on 05/05/2021.
//

#include "Virologist.hpp"

namespace pandemic {
Virologist::Virologist(Board &board, City city) : Player(board, city) {
  this->my_role = "Virologist";
}
  Player &Virologist::treat(City c) {
  if (cards.find(c) == cards.end() || cards.empty()) {
    if(c != current_city)
    {
      throw std::invalid_argument("You don't have the right card!");
    }
  }
  if (!board.valid_city(c)) {
    throw std::invalid_argument("Invalid city");
  }
  if (board.get_level(c) == 0) {
    throw std::invalid_argument("No sick cubes");
  }
  if (board.cured(board.get_color(c))) {
    board.data_map.at(c).level = 0;
  } else {
    board.data_map.at(c).level-=1;
  }
  //throw card
  if(c == current_city)
  {
    return *this;
  }
  cards.erase(c);
  return *this;
}
} // namespace pandemic
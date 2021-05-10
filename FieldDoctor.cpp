//
// Created by ischelle on 05/05/2021.
//

#include "FieldDoctor.hpp"
namespace pandemic {
FieldDoctor::FieldDoctor(Board &board, City city) : Player(board, city) {
  my_role = "FieldDoctor";
}

Player &FieldDoctor::treat(City c) {
  if (!board.has_neighbor(current_city, c)) {
    if(current_city != c)
    {
      throw std::invalid_argument("This city is not neighboring!");
    }
  }
  if (board.data_map.find(c) == board.data_map.end()) {
    throw std::invalid_argument("Invalid city");
  }
  if (board.get_level(c)  <= 0) {
    throw std::invalid_argument("No sick cubes");
  }
  if (board.cured(board.get_color(c))) {
    board.data_map.at(c).level = 0;
  } else {
    board.data_map.at(c).level--;
  }
  return *this;
}
} // namespace pandemic
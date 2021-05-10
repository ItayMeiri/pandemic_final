//
// Created by ischelle on 05/05/2021.
//
#include "Scientist.hpp"
namespace pandemic {
Scientist::Scientist(Board &board, City city, int n) : Player(board, city) {
  this->n = n;
  this->my_role = "Scientist";
}

Player &Scientist::discover_cure(Color color) {
  if (!board.has_center(current_city)) {
    throw std::invalid_argument("This city has no center!");
  }
  if (board.cured(color)) {
    // disease already cured
    return *this;
  }
  std::unordered_set<City> to_delete;
  for (auto it : cards) {
    if (board.get_color(it) == color) {
      to_delete.insert(it);
    }
  }
  if (to_delete.size() < n) {
    throw std::invalid_argument("Not enough cards!");
    return *this;
  }
  board.cured_diseases.insert(color);
  int temp = n;
  for (auto it : to_delete) {
    if (temp == 0) {
      break;
    }
    cards.erase(it);
    temp--;
  }
  return *this;
}
} // namespace pandemic
//
// Created by ischelle on 05/05/2021.
//
#include "Researcher.hpp"
namespace pandemic {
Researcher::Researcher(Board &board, City city) : Player(board, city) {
  this->my_role = "Researcher";
}
Player &Researcher::discover_cure(Color color) {
  const int cards_to_throw = 5;
  std::unordered_set<City> to_delete;
  if (board.cured(color)) {
    // it's already in cured disease, aka it's cured!
    return *this;
  }
  for (auto it : cards) {
    if (board.get_color(it) == color) {
      to_delete.insert(it);
    }
  }
  if (to_delete.size() < cards_to_throw) {
    throw std::invalid_argument("You don't have enough cards!");
  }
  int temp = cards_to_throw;
  for (auto it : to_delete) {
    if (temp == 0) {
      break;
    }
    cards.erase(it);
    temp--;
  }
  board.cured_diseases.insert(color);

  return *this;
}
} // namespace pandemic
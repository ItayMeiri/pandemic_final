//
// Created by ischelle on 05/05/2021.
//
#include "GeneSplicer.hpp"
namespace pandemic {
GeneSplicer::GeneSplicer(Board &board, City city) : Player(board, city) {
  my_role = "GeneSplicer";
}
Player &GeneSplicer::discover_cure(Color c) {
  const int temp = 5;
  if (!board.has_center(current_city)) {
    throw std::invalid_argument("This city has no center!!");
  }
  if (board.cured(c)) {
    return *this;
  }
  if (cards.size() < temp) {
    throw std::invalid_argument("Not enough cards");
  }
  int counter = 0;
  for (auto it : cards) {
    if (counter == temp) {
      break;
    }
    cards.erase(it);
    counter++;
  }
  board.cured_diseases.insert(c);
  return *this;
}
} // namespace pandemic

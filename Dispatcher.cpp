//
// Created by ischelle on 05/05/2021.
//

#include "Dispatcher.hpp"
namespace pandemic {

Dispatcher::Dispatcher(Board &board, City city) : Player(board, city) {
  my_role = "Dispatcher";
}

// can fly directly without throwing card, if the city has research center
Player &Dispatcher::fly_direct(City c) {
  if (!board.valid_city(c)) {
    throw std::invalid_argument("Bad city name");
  }
  if (c == current_city) {
    throw std::invalid_argument("Can't fly to your own city!");
  }
  if (board.has_center(current_city)) {

    current_city = c;
    return *this;
  }
  if (cards.find(c) == cards.end()) {
    throw std::invalid_argument("No card for this city");
  }
  current_city = c;
  cards.erase(c);
  return *this;
}
} // namespace pandemic
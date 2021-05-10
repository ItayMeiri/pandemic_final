//
// Created by ischelle on 05/05/2021.
//

#include "Player.hpp"

namespace pandemic {
Player::Player(Board &board, City city) : board(board) {
  this->current_city = city;
  this->my_role = "Player";
}

Player &Player::build() {
  if(!board.valid_city(current_city))
  {
    throw std::invalid_argument("Bad city");
  }
  if (board.has_center(current_city)) {
    return *this;
  }
  if (cards.find(current_city) == cards.end()) {
    throw std::invalid_argument("Has no cards");
  }
  board.set_center(current_city, true);
  cards.erase(current_city); // throw card
  return *this;
}
Player &Player::discover_cure(Color color) {
    if(!board.valid_city(current_city))
  {
    throw std::invalid_argument("Bad city");
  }
  if (!board.has_center(current_city)) {
    throw std::invalid_argument("There's no center here!");
  }
  if (board.cured(color)) {
    return *this; // disease already cured
  }
  std::unordered_set<City> to_delete;
  for (auto it : cards) {
    if (board.get_color(it) == color) {
      to_delete.insert(it);
    }
  }
  const int five = 5;
  if (to_delete.size() < five) {
    throw std::invalid_argument("Not enough cards!");
  }
  board.cured_diseases.insert(color);
  for (auto it : to_delete) {
    cards.erase(it);
  }
  return *this;
}
Player &Player::drive(City city) {
    if(!board.valid_city(current_city))
  {
    throw std::invalid_argument("Bad city");
  }
    if(city == current_city)
  {
    throw std::invalid_argument("You can't drive to your own city!");
  }
  if (!board.has_neighbor(current_city, city)) {
    if(!board.has_neighbor(city, current_city))
    {
      throw std::invalid_argument("You're not neighboring this city!");
    }
  }
  current_city = city; // drive completed
  return *this;
}
Player &Player::fly_charter(City city) {
    if(!board.valid_city(current_city))
  {
    throw std::invalid_argument("Bad city");
  }
  if(city == current_city)
  {
    throw std::invalid_argument("You can't fly to your own city!");
  }
  if (cards.find(current_city) == cards.end()) {
    throw std::invalid_argument("You don't have this city!");
  }
  cards.erase(current_city);
  current_city = city;
  return *this;
}
Player &Player::fly_direct(City city) { // flies to card
  if (cards.find(city) == cards.end()) {
    throw std::invalid_argument("You don't have a card for this!");
    return *this;
  }

  cards.erase(city);
  current_city = city;
  return *this;
}
Player &Player::fly_shuttle(City city) {
  if (city == current_city) {
    throw std::invalid_argument("Can't fly to your own city");
    }
  if (!(board.has_center(city) && board.has_center(current_city))) {
    throw std::invalid_argument("This city doesn't have a center");
  }
  current_city = city;
  return *this;
}
std::string Player::role() { return my_role; }

Player &Player::take_card(City city) {
  if(cards.find(city) == cards.end())
  {
      cards.insert(city);
  }
  return *this;
}
Player &Player::treat(City city) {
  if (city != current_city) {
    throw std::invalid_argument("You can only treat your own city");
  }
  if (board.data_map.find(city) == board.data_map.end()) {
    throw std::invalid_argument("Invalid city");
  }
  if (board.get_level(city) <= 0) {
    board.data_map.at(city).level = 0;
    throw std::invalid_argument("No sick cubes");
  }
  if (board.cured(board.get_color(city))) {
    board.data_map.at(city).level = 0;
  } else {
    board.data_map.at(city).level--;
  }
  return *this;
}

void Player::remove_cards()
{
  cards.clear();
}

} // namespace pandemic
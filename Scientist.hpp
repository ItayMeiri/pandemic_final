//
// Created by ischelle on 05/05/2021.
//

#pragma once

#include "Player.hpp"
namespace pandemic {
class Scientist : public Player {
public:
  int n;
  Scientist(Board &board, City city, int n);
  virtual Player &discover_cure(
      Color color) override;
};
} // namespace pandemic

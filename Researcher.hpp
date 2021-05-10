//
// Created by ischelle on 05/05/2021.
//
#pragma once
#include "Player.hpp"
namespace pandemic {
class Researcher : public Player

{
public:
  Researcher(Board &board, City city);
  virtual Player &discover_cure(Color color) override;
};
} // namespace pandemic
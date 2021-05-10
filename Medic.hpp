//
// Created by ischelle on 05/05/2021.
//

#pragma once
#include "Player.hpp"

/**
 * Medic:
 * -Removes all disease cubes when treating
 * -Automatically heals any city he enters when a disease is cured
 */
namespace pandemic {
class Medic : public Player {
public:
  Medic(Board &board, City city);
  virtual Player &treat(City city) override;
  virtual Player &fly_direct(City city) override;
  virtual Player &drive(City city) override;
  virtual Player &fly_shuttle(City city) override;
  virtual Player &fly_charter(City city) override;
  void AutoHeal(); // Checks if disease is cured and heals it.
};
} // namespace pandemic

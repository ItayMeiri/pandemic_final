//
// Created by ischelle on 05/05/2021.
//

#pragma once
#include "Player.hpp"
namespace pandemic
{
class Dispatcher: public Player
{
public:
    Dispatcher(Board &board ,City city);
    virtual Player &fly_direct(City c) override;
    };
}



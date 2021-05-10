//
// Created by ischelle on 05/05/2021.
//

#pragma once
#include "City.hpp"
#include "Color.hpp"
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
namespace pandemic{

    class Board
    {
    public:
        struct CityData{
            Color col;
            int level = 0;
            bool center = 0;
            std::unordered_set<City> neighbors;
        };
        Board(); // This will read the file, and initialize all the CityData stats
        std::unordered_map<City, CityData> data_map; // city citydata
        std::unordered_map<std::string, City> enum_map; // string city
        std::unordered_map<std::string, Color> color_map; // string color
        std::unordered_set<Color> cured_diseases; // initialize this to false
        bool cured(Color c); // checks if color disease is cured
        int& operator[](City c);
        bool is_clean();
        void remove_cures();
        int get_level(City c);
        bool has_center(City c);
        Color get_color(City c);
        bool has_neighbor(City c, City t);
        void set_center(City c, bool center);
        void find_cure(Color c);
        bool valid_city(City c);
        void reduce_city_level(City c);
        void remove_stations();
        friend std::ostream& operator<<(std::ostream& os, const Board &b);
        void set_level(City city, int level);

    };


}


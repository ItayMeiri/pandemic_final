//
// Created by ischelle on 05/05/2021.
//
#include "Board.hpp"
namespace pandemic {
Board::Board() {
  // Populate Color map
  color_map.insert(std::make_pair("Yellow", Color::Yellow));
  color_map.insert(std::make_pair("Black", Color::Black));
  color_map.insert(std::make_pair("Blue", Color::Blue));
  color_map.insert(std::make_pair("Red", Color::Red));
  // Populate enum_map
  std::string file_path = "cities_map.txt";
  std::ifstream is(file_path);
  std::string str;
  int enum_counter = 0;
  while (std::getline(is, str)) {
    size_t index = str.find_first_of(' ');
    std::string substr = str.substr(0, index);
    enum_map.insert(std::make_pair(substr, City(enum_counter)));
    data_map.insert(std::make_pair(City(enum_counter), CityData{}));
    enum_counter++;
  }
  std::ifstream ifs(file_path);
  str = "";
  while (std::getline(ifs, str)) {
    Color c = Color::Yellow;
    City cit = City::Algiers;
    std::istringstream istr(str);
    int counter = 0;
    do {
      std::string sub;
      istr >> sub; // Will split the words
      if (sub.empty()) {
        break;
      }
      if (counter == 0) { // Update current city
        cit = enum_map.at(sub);
      }
      if (counter == 1) { // Initialize color
        c = color_map.at(sub);
        data_map.at(cit).col = c;
      }
      if (counter > 1) { // Update Neighbors
        City ni = enum_map.at(sub);
        // insert neighbor to my city
        data_map.at(cit).neighbors.insert(ni);
      }
      counter++;
    } while (istr);
  }
  // The units file is incomplete, this makes sure the connections are up to
  // date.
  data_map.at(City::Manila).neighbors.insert(City::HongKong);
  data_map.at(City::HongKong).neighbors.insert(City::Manila);
}
bool Board::cured(Color c) {
  return cured_diseases.find(c) != cured_diseases.end();
}
int &Board::operator[](City c) {
  if (data_map.find(c) == data_map.end()) {
    throw std::invalid_argument("No such city");
  }
  return data_map.at(c).level;
}
bool Board::is_clean() {
  for (auto &it : data_map) {
    if (it.second.level > 0) {
      return false;
    }
  }
  return true;
}
void Board::remove_cures() {
  cured_diseases.clear(); // for testing purposes
}
std::ostream &operator<<(std::ostream &os, const Board &b) {

  for (const auto &it : b.enum_map) {
    Board::CityData temp = b.data_map.at(it.second);
    os << it.first << ": "
       << "With research center: ";
    if (temp.center) {
      os << "True";
    } else {
      os << "False";
    }
    os << " , Pollution level: " << temp.level << std::endl;
  }
  return os;
}

int Board::get_level(City c) {
  if (data_map.find(c) == data_map.end()) {
    return 0;
  }
  return data_map.at(c).level;
}
bool Board::has_center(City c) {
  if (data_map.find(c) == data_map.end()) {
    return false;
  }
  return data_map.at(c).center;
}
Color Board::get_color(City c) {
  if (data_map.find(c) == data_map.end()) {
    throw std::invalid_argument("Bad city at get_color");
  }
  return data_map.at(c).col;
}
bool Board::has_neighbor(City c, City t) {
  return data_map.at(c).neighbors.find(t) != data_map.at(c).neighbors.end();
}

void Board::set_center(City c, bool center) {
  if (valid_city(c)) {
    data_map.at(c).center = center;
  }
}

bool Board::valid_city(City c) { return data_map.find(c) != data_map.end(); }
void Board::reduce_city_level(City c) {
  if (valid_city(c)) {
    data_map.at(c).level = 0;
  }
}

void Board::remove_stations() {
  for (auto &it : data_map) {
    it.second.center = false;
  }
}
} // namespace pandemic

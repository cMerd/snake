#include "../inc/apple.hpp"
#include "../inc/game.hpp"
#include <random>

void apple::get_new() {
  std::random_device rd;
  std::uniform_int_distribution<int> x_generator(
      1, game::get_resulution().first / game::get_block_size() - 1);
  std::uniform_int_distribution<int> y_generator(
      1, game::get_resulution().second / game::get_block_size() - 1);
  this->pos.first = x_generator(rd);
  this->pos.second = y_generator(rd);
}

std::pair<int, int> apple::get_pos() const { return this->pos; }

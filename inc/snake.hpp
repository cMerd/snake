#pragma once

#include "block.hpp"
#include "direction.hpp"
#include <utility>
#include <vector>

class snake {
public:
  snake();

  void move(const std::vector<std::vector<BLOCK>> &game_map);
  void change_direction(DIRECTION d);

  std::pair<int, int> get_pos() const;
  std::vector<std::pair<int, int>> get_tail_pos() const;
  bool game_over() const;
  static int get_frame_per_move();
  int get_score() const;

private:
  bool is_game_over = false;
  std::pair<int, int> head_pos;
  std::vector<std::pair<int, int>> tail_pos;
  DIRECTION direction;
  constexpr static int FRAME_PER_MOVE = 12;
  int score = 0;
};

#pragma once

#include "block.hpp"
#include "snake.hpp"
#include <utility>
#include <vector>
#include "apple.hpp"
#include <raylib.h>

class game {
public:
  game(bool debug_log);
  ~game();
  void run();

  static std::pair<int, int> get_resulution();
  static int get_block_size();

private:
  void init_map();
  void update_map();
  void get_input();

  void draw_map() const;
  void draw_block(int x, int y, BLOCK type) const;
  bool should_run() const;

  constexpr static int BLOCK_SIZE = 32;
  constexpr static int SCREEN_WIDTH = (40 * BLOCK_SIZE);
  constexpr static int SCREEN_HEIGHT = (30 * BLOCK_SIZE);
  constexpr static int FRAME_RATE = 60;
  constexpr static Color BG1 = (Color){9, 114, 235, 255};
  constexpr static Color BG2 = (Color){115, 226, 230, 255};

  std::vector<std::vector<BLOCK>> game_map;
  snake player;
  apple food;
  int frame_count = 0;
};

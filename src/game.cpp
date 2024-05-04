#include "../inc/game.hpp"
#include <raylib.h>
#include <stdexcept>
#include <unistd.h>
#include <vector>

game::game(bool debug_log) {
  if (!debug_log) {
    SetTraceLogLevel(LOG_NONE);
  }
  InitWindow(this->SCREEN_WIDTH, this->SCREEN_HEIGHT, "Snake");
  SetTargetFPS(this->FRAME_RATE);
}

game::~game() { CloseWindow(); }

void game::run() {
  this->food.get_new();
  this->init_map();
  while (this->should_run()) {
    this->frame_count++;
    if (this->frame_count == 60) {
      this->frame_count = 0;
    }
    BeginDrawing();
    ClearBackground(BLACK);
    this->get_input();
    if (this->frame_count % this->player.get_frame_per_move() == 0) {
      player.move(this->game_map);
    }
    this->update_map();
    this->draw_map();
    EndDrawing();
    if (this->player.game_over()) {
      DrawText(
          (std::string("Score: ") + std::to_string(this->player.get_score()))
              .c_str(),
          50, 50, 50, WHITE);
      DrawText("ESC to exit", 50, 150, 40, WHITE);
      if (IsKeyPressed(KEY_ESCAPE)) {
        break;
      }
      continue;
    }
  }
}

bool game::should_run() const { return !(WindowShouldClose()); }

void game::init_map() {
  game_map = std::vector<std::vector<BLOCK>>(
      this->SCREEN_WIDTH / this->BLOCK_SIZE,
      std::vector<BLOCK>(this->SCREEN_HEIGHT / this->BLOCK_SIZE, BLOCK::EMPTY));
}

void game::draw_map() const {
  for (size_t i = 0; i < this->game_map.size(); i++) {
    for (size_t j = 0; j < this->game_map[i].size(); j++) {
      int x = i * this->BLOCK_SIZE;
      int y = j * this->BLOCK_SIZE;
      this->draw_block(x, y, this->game_map[i][j]);
    }
  }
}

void game::draw_block(int x, int y, BLOCK type) const {
  switch (type) {
  case EMPTY:
    DrawLine(x, y, x + this->BLOCK_SIZE, y, BROWN);
    DrawLine(x, y, x, y + this->BLOCK_SIZE, BROWN);
    DrawLine(x + this->BLOCK_SIZE, y, x + this->BLOCK_SIZE,
             y + this->BLOCK_SIZE, BROWN);
    break;
  case SNAKE_TAIL:
  case SNAKE_HEAD:
    DrawRectangle(x, y, this->BLOCK_SIZE, this->BLOCK_SIZE, GREEN);
    break;
  case APPLE:
    DrawRectangle(x, y, this->BLOCK_SIZE, this->BLOCK_SIZE, RED);
    break;
  default:
    throw std::logic_error("Invalid block type");
    break;
  }
}

std::pair<int, int> game::get_resulution() {
  return {SCREEN_WIDTH, SCREEN_HEIGHT};
}

int game::get_block_size() { return BLOCK_SIZE; }

void game::update_map() {
  if (!this->player.game_over()) {
    if (this->game_map[this->player.get_pos().first]
                      [this->player.get_pos().second] == BLOCK::APPLE) {
      this->food.get_new();
    }
  }
  while (
      this->game_map[this->food.get_pos().first][this->food.get_pos().second] ==
          BLOCK::SNAKE_HEAD or
      this->game_map[this->food.get_pos().first][this->food.get_pos().second] ==
          BLOCK::SNAKE_TAIL) {
    this->food.get_new();
  }
  for (size_t i = 0; i < this->game_map.size(); i++) {
    for (size_t j = 0; j < this->game_map[i].size(); j++) {
      this->game_map[i][j] = BLOCK::EMPTY;
    }
  }
  if (!this->player.game_over()) {
    this->game_map[this->player.get_pos().first]
                  [this->player.get_pos().second] = BLOCK::SNAKE_HEAD;
    const std::vector<std::pair<int, int>> player_pos =
        this->player.get_tail_pos();
    for (const auto &[x, y] : player_pos) {
      game_map[x][y] = BLOCK::SNAKE_TAIL;
    }
    this->game_map[this->food.get_pos().first][this->food.get_pos().second] =
        BLOCK::APPLE;
  }
}

void game::get_input() {
  if (IsKeyPressed(KEY_W)) {
    this->player.change_direction(UP);
  }
  if (IsKeyPressed(KEY_S)) {
    this->player.change_direction(DOWN);
  }
  if (IsKeyPressed(KEY_D)) {
    this->player.change_direction(RIGHT);
  }
  if (IsKeyPressed(KEY_A)) {
    this->player.change_direction(LEFT);
  }
}

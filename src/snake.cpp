#include "../inc/snake.hpp"
#include "../inc/game.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

snake::snake() {
  this->head_pos.first =
      game::get_resulution().first / game::get_block_size() / 2;
  this->head_pos.second =
      game::get_resulution().second / game::get_block_size() / 2;
  this->direction = DIRECTION::UP;
}

void snake::move(const std::vector<std::vector<BLOCK>> &game_map) {
  std::pair<int, int> change;
  switch (this->direction) {
  case RIGHT:
    change = {1, 0};
    break;
  case LEFT:
    change = {-1, 0};
    break;
  case UP:
    change = {0, -1};
    break;
  case DOWN:
    change = {0, 1};
    break;
  default:
    throw std::logic_error("Invalid direction");
    return;
    break;
  }
  this->tail_pos.push_back(head_pos);
  if (!this->tail_pos.empty()) {
    for (int i = this->tail_pos.size() - 1; i >= 0; i--) {
      if (i == 0) {
        this->tail_pos[i] = this->head_pos;
      } else {
        this->tail_pos[i] = this->tail_pos[i - 1];
      }
    }
  }
  this->head_pos.first += change.first;
  this->head_pos.second += change.second;
  if (head_pos.first < 0 or head_pos.first >= (int)game_map.size() or
      head_pos.second < 0 or
      head_pos.second >= (int)game_map[head_pos.first].size()) {
    this->is_game_over = true;
    return;
  }
  if (game_map[head_pos.first][head_pos.second] == BLOCK::SNAKE_TAIL) {
    this->is_game_over = true;
    return;
  }
  if (game_map[head_pos.first][head_pos.second] != BLOCK::APPLE) {
    if (!this->tail_pos.empty()) {
      this->tail_pos.pop_back();
    }
  } else {
    this->score++;
  }
}

void snake::change_direction(DIRECTION d) { this->direction = d; }

bool snake::game_over() const { return this->is_game_over; }

std::pair<int, int> snake::get_pos() const { return this->head_pos; }

std::vector<std::pair<int, int>> snake::get_tail_pos() const {
  return this->tail_pos;
}

int snake::get_frame_per_move() { return FRAME_PER_MOVE; }

int snake::get_score() const { return this->score; }

#pragma once

#include <utility>

class apple {
public:
  void get_new();
  std::pair<int, int> get_pos() const;
private:
  std::pair<int, int> pos;
};


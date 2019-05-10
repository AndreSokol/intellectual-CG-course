#pragma once

#include <mutex>
#include <queue>

namespace render_queue {
struct Task {
  int s_x = 0;
  int s_y = 0;
  int f_x = 0;
  int f_y = 0;
};

class Queue {
public:
  Queue(int height, int width, int block_size);

  bool pop(Task &);

  unsigned long size();

private:
  void fill(int height, int width, int block_size);

  std::queue<Task> _data;
  std::mutex _mutex;
};
} // namespace render_queue

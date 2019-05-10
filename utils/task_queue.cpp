#include "task_queue.hpp"

#include <algorithm>
#include <iostream>

namespace render_queue {
Queue::Queue(int height, int width, int block_size) {
  fill(height, width, block_size);
}

void Queue::fill(int height, int width, int block_size) {
  for (int i = 0; i * block_size < width; i++) {
    for (int j = 0; j * block_size < height; j++) {
      _data.push(Task{i * block_size, j * block_size,
                      std::min((i + 1) * block_size, width),
                      std::min((j + 1) * block_size, height)});
    }
  }
}

bool Queue::pop(Task &task) {
  _mutex.lock();
  if (_data.empty()) {
    _mutex.unlock();
    return false;
  }

  task = _data.front();
  _data.pop();
  _mutex.unlock();

  return true;
}

unsigned long Queue::size() { return _data.size(); }
} // namespace render_queue

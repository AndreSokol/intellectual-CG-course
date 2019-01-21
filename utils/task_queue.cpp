#include "task_queue.hpp"
#include "../core/gl_const.hpp"

#include <algorithm>
#include <iostream>

namespace render_queue {
Queue::Queue(int height, int width) {
  fill(height, width);
}

void Queue::fill(int height, int width) {
  for (int i = 0; i * BLOCK_SIZE < width; i++) {
    for (int j = 0; j * BLOCK_SIZE < height; j++) {
      _data.push(Task{i * BLOCK_SIZE,
                      j * BLOCK_SIZE,
                      std::min((i + 1) * BLOCK_SIZE, width),
                      std::min((j + 1) * BLOCK_SIZE, height)});
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

unsigned long Queue::size() {
  return _data.size();
}
}

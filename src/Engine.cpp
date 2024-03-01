//
// Created by Тимур Ахметзянов on 29.02.2024.
//

#include "../include/Engine.h"

void Engine::moveElmInThread() {
  for (int i = 0; i < distance_ * 1e6; ++i) {
    if (i % (int) 1e6 == 0) {
      emit move(1);
    }
  }
  emit finished();
}

void Engine::setDirection(int direction) {
  direction_ = direction;
}

int Engine::getDirection() const {
  return direction_;
}

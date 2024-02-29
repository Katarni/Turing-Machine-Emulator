//
// Created by Тимур Ахметзянов on 29.02.2024.
//

#include "../include/Engine.h"

void Engine::moveElm() {
  for (int i = 0; i < distance_ * 1e7; ++i) {
    if (i % (int)1e7 == 0) {
      emit move(1);
    }
  }
  emit finished();
}

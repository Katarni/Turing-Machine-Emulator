//
// Created by Тимур Ахметзянов on 29.02.2024.
//

#pragma once

#include "header.h"


class Engine : public QObject {
 Q_OBJECT

 public slots:

  void moveElmInThread();

  void moveElmOutThread();

  void setDirection(int direction);

  int getDirection() const;

 signals:

  void move(int);

  void finished();

 public:
  void addSpeed() {
    if (speed_ <= 1e5) return;
    speed_ >>= 1;
  }

  void removeSpeed() {
    speed_ <<= 1;
  }

 private:
  int distance_ = 60;
  int direction_ = 1;
  int speed_ = 1e7;
};

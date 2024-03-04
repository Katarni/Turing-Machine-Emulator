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

 private:
  int distance_ = 60;
  int direction_ = 1;
};

//
// Created by Тимур Ахметзянов on 29.02.2024.
//

#pragma once

#include "header.h"


class Engine : public QObject {
 Q_OBJECT

 public slots:

  void moveElm();

 signals:

  void move(int);

  void finished();

 private:
  int distance_ = 60;
};

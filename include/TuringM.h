//
// Created by Тимур Ахметзянов on 22.02.2024.
//

#pragma once

#include "header.h"


class TuringM : QMainWindow {
 Q_OBJECT

 public:
  TuringM();

  void start();

 private slots:
  void edit_left_cont();

 private:
  const int width = 1500, height = 800;
  const int close_ear_left_x = 390, close_ear_left_y = 150;
  const int open_ear_left_x = 12, open_ear_left_y = 150;
  const int open_cont_left_x = 90, open_cont_left_y = 125;
  const int close_cont_left_x = 468, close_cont_left_y = 125;

  bool left_opened = false;

  QMainWindow* window;
  QWidget* turing_head;
  QWidget* left_ear;
  QWidget* left_controller;

  QPushButton* open_left_controller;
};

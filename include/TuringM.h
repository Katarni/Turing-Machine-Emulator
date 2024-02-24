//
// Created by Тимур Ахметзянов on 22.02.2024.
//

#pragma once

#include "header.h"


class TuringM : QMainWindow {
 Q_OBJECT

 public:
  TuringM();

 private slots:
  void edit_left_cont();
  void edit_right_cont();

 private:
  const int width = 1500, height = 800;

  const int close_ear_left_x = 370, close_ear_left_y = 150;
  const int open_ear_left_x = -8, open_ear_left_y = 150;
  const int open_cont_left_x = 70, open_cont_left_y = 125;
  const int close_cont_left_x = 448, close_cont_left_y = 125;

  const int close_ear_right_x = 860, close_ear_right_y = 150;
  const int open_ear_right_x = 1233, open_ear_right_y = 150;
  const int open_cont_right_x = 840, open_cont_right_y = 125;
  const int close_cont_right_x = 462, close_cont_right_y = 125;

  bool left_opened = false;
  bool right_opened = false;

  QMainWindow* window;
  QWidget* turing_head;
  QWidget* left_ear;
  QWidget* left_controller;
  QWidget* right_ear;
  QWidget* right_controller;

  QPushButton* open_left_controller;
  QPushButton* open_right_controller;
};

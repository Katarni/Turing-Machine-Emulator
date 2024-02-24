//
// Created by Тимур Ахметзянов on 22.02.2024.
//

#include "../include/TuringM.h"

TuringM::TuringM() {
  window = new QMainWindow();
  window->setWindowFlags(Qt::FramelessWindowHint);
  window->setFixedSize(width, height);
  window->setStyleSheet("QMainWindow { background: transparent; }");
  window->setAttribute(Qt::WA_TranslucentBackground, true);

  turing_head = new QWidget(window);
  turing_head->setFixedSize(700, 800);
  turing_head->move(400, 0);
  turing_head->setStyleSheet("QWidget { background: url(../img/turing.png);"
                             "background-position: center center;"
                             "background-repeat: no-repeat; }");

  left_ear = new QWidget(window);
  left_ear->setFixedSize(220, 400);
  left_ear->move(close_ear_left_x, close_ear_left_y);
  left_ear->setStyleSheet("QWidget { background: url(../img/left_ear.png); }");
  left_ear->stackUnder(turing_head);

  left_controller = new QWidget(window);
  left_controller->setFixedSize(550, 450);
  left_controller->move(close_cont_left_x, close_cont_left_y);
  left_controller->setStyleSheet("QWidget { background: url(../img/left_controller.png); }");
  left_controller->stackUnder(turing_head);
  left_controller->hide();

  open_left_controller = new QPushButton(window);
  open_left_controller->resize(50, 45);
  open_left_controller->move(415, 353);
  open_left_controller->setStyleSheet("QPushButton { background: transparent;"
                                                    "color: #184C01;"
                                                    "font-size: 45px; } ");
  open_left_controller->setText("<");
  connect(open_left_controller, SIGNAL(released()), this, SLOT(edit_left_cont()));

  window->show();
}

void TuringM::edit_left_cont() {
  if (left_opened) {
    left_controller->hide();
    left_controller->move(close_cont_left_x, close_cont_left_y);
    left_ear->move(close_ear_left_x, close_ear_left_y);
    open_left_controller->move(415, 353);
    open_left_controller->setText("<");
  } else {
    left_controller->show();
    left_controller->move(open_cont_left_x, open_cont_left_y);
    left_ear->move(open_ear_left_x, open_ear_left_y);
    open_left_controller->move(37, 353);
    open_left_controller->setText(">");
  }
  left_opened = !left_opened;
  window->update();
}

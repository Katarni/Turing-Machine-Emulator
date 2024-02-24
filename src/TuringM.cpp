//
// Created by Тимур Ахметзянов on 22.02.2024.
//

#include "../include/TuringM.h"

TuringM::TuringM() {
  window_ = new QMainWindow();
  window_->setWindowFlags(Qt::FramelessWindowHint);
  window_->setFixedSize(width, height);
  window_->setStyleSheet("QMainWindow { background: transparent; }");
  window_->setAttribute(Qt::WA_TranslucentBackground, true);

  turing_head_ = new QWidget(window_);
  turing_head_->setFixedSize(700, 800);
  turing_head_->move(380, 0);
  turing_head_->setStyleSheet("QWidget { background: url(../img/turing.png);"
                             "background-position: center center;"
                             "background-repeat: no-repeat; }");

  //// Left Side
  left_ear_ = new QWidget(window_);
  left_ear_->setFixedSize(220, 400);
  left_ear_->move(close_ear_left_x_, close_ear_left_y_);
  left_ear_->setStyleSheet("QWidget { background: url(../img/left_ear.png); }");
  left_ear_->stackUnder(turing_head_);

  left_controller_ = new QWidget(window_);
  left_controller_->setFixedSize(550, 450);
  left_controller_->move(close_cont_left_x_, close_cont_left_y_);
  left_controller_->setStyleSheet("QWidget { background: url(../img/left_controller.png); }");
  left_controller_->stackUnder(turing_head_);
  left_controller_->hide();

  open_left_controller_ = new QPushButton(window_);
  open_left_controller_->resize(50, 45);
  open_left_controller_->move(395, 353);
  open_left_controller_->setStyleSheet("QPushButton { background: transparent;"
                                                    "color: #184C01;"
                                                    "font-size: 45px; } ");
  open_left_controller_->setText("<");
  connect(open_left_controller_, SIGNAL(released()), this, SLOT(editLeftCont()));

  //// Right Side
  right_ear_ = new QWidget(window_);
  right_ear_->setFixedSize(220, 400);
  right_ear_->move(close_ear_right_x_, close_ear_right_y_);
  right_ear_->setStyleSheet("QWidget { background: url(../img/right_ear.png); }");
  right_ear_->stackUnder(turing_head_);

  right_controller_ = new QWidget(window_);
  right_controller_->setFixedSize(550, 450);
  right_controller_->move(close_cont_right_x_, close_cont_right_y_);
  right_controller_->setStyleSheet("QWidget { background: url(../img/right_controller.png); }");
  right_controller_->stackUnder(turing_head_);
  right_controller_->hide();

  open_right_controller_ = new QPushButton(window_);
  open_right_controller_->resize(50, 45);
  open_right_controller_->move(1020, 353);
  open_right_controller_->setStyleSheet("QPushButton { background: transparent;"
                                      "color: #184C01;"
                                      "font-size: 45px; } ");
  open_right_controller_->setText(">");
  connect(open_right_controller_, SIGNAL(released()), this, SLOT(editRightCont()));

  window_->show();
}

void TuringM::editLeftCont() {
  if (left_opened_) {
    left_controller_->hide();
    left_controller_->move(close_cont_left_x_, close_cont_left_y_);
    left_ear_->move(close_ear_left_x_, close_ear_left_y_);
    open_left_controller_->move(395, 353);
    open_left_controller_->setText("<");
  } else {
    left_controller_->show();
    left_controller_->move(open_cont_left_x_, open_cont_left_y_);
    left_ear_->move(open_ear_left_x_, open_ear_left_y_);
    open_left_controller_->move(17, 353);
    open_left_controller_->setText(">");
  }
  left_opened_ = !left_opened_;
}

void TuringM::editRightCont() {
  if (right_opened_) {
    right_controller_->hide();
    right_controller_->move(close_cont_right_x_, close_cont_right_y_);
    right_ear_->move(close_ear_right_x_, close_ear_right_y_);
    open_right_controller_->move(1020, 353);
    open_right_controller_->setText(">");
  } else {
    right_controller_->show();
    right_controller_->move(open_cont_right_x_, open_cont_right_y_);
    right_ear_->move(open_ear_right_x_, open_ear_right_y_);
    open_right_controller_->move(1393, 353);
    open_right_controller_->setText("<");
  }
  right_opened_ = !right_opened_;
}

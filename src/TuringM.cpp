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

  exit_btn_ = new QPushButton(window_);
  exit_btn_->resize(40, 40);
  exit_btn_->move(705, 20);
  exit_btn_->setStyleSheet("QPushButton { background: transparent;"
                                        "border: 2px solid red;"
                                        "border-radius: 20px;"
                                        "color: red;"
                                        "font-size: 30px }");
  exit_btn_->setText("X");
  connect(exit_btn_, SIGNAL(released()), this, SLOT(exit()));

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
                                                    "color: #184c01;"
                                                    "font-size: 45px; } ");
  open_left_controller_->setText("<");
  connect(open_left_controller_, SIGNAL(released()), this, SLOT(editLeftCont()));

  //// Alphabets
  tape_alphabet_edit_ = new QLineEdit(window_);
  tape_alphabet_edit_->resize(170, 45);
  tape_alphabet_edit_->move(180, 210);
  tape_alphabet_edit_->setStyleSheet("QLineEdit { padding-left: 5px; "
                                                  "font-size: 25px;"
                                                  "background: #9ea3a2; }");
  tape_alphabet_edit_->setPlaceholderText("Tape's");
  tape_alphabet_edit_->setDisabled(true);
  tape_alphabet_edit_->hide();

  heads_alphabet_edit_ = new QLineEdit(window_);
  heads_alphabet_edit_->resize(170, 45);
  heads_alphabet_edit_->move(180, 265);
  heads_alphabet_edit_->setStyleSheet("QLineEdit { padding-left: 5px; "
                                                  "font-size: 25px;"
                                                  "background: #9ea3a2; }");
  heads_alphabet_edit_->setPlaceholderText("Head's");
  heads_alphabet_edit_->setDisabled(true);
  heads_alphabet_edit_->hide();

  confirm_alphabets_ = new QPushButton(window_);
  confirm_alphabets_->resize(100, 50);
  confirm_alphabets_->move(365, 210);
  confirm_alphabets_->setStyleSheet("QPushButton { background: #9ea3a2;"
                                                  "border-radius: 10px;"
                                                  "font-size: 20px }");
  confirm_alphabets_->setText("Confirm");
  confirm_alphabets_->setDisabled(true);
  confirm_alphabets_->hide();

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
    closeLeftElms();
  } else {
    left_controller_->show();
    left_controller_->move(open_cont_left_x_, open_cont_left_y_);
    left_ear_->move(open_ear_left_x_, open_ear_left_y_);
    open_left_controller_->move(17, 353);
    openLeftElms();
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

void TuringM::exit() {
  std::exit(0);
}

void TuringM::closeLeftElms() {
  tape_alphabet_edit_->setDisabled(true);
  tape_alphabet_edit_->hide();
  heads_alphabet_edit_->setDisabled(true);
  confirm_alphabets_->setDisabled(true);
  confirm_alphabets_->hide();
  heads_alphabet_edit_->hide();
  open_left_controller_->setText(">");
}

void TuringM::openLeftElms() {
  tape_alphabet_edit_->setDisabled(false);
  tape_alphabet_edit_->show();
  heads_alphabet_edit_->setDisabled(false);
  confirm_alphabets_->setDisabled(false);
  confirm_alphabets_->show();
  heads_alphabet_edit_->show();
  open_left_controller_->setText("<");
}

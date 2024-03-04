//
// Created by Тимур Ахметзянов on 22.02.2024.
//

#include "../include/App.h"

App::App() {
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
  exit_btn_->resize(30, 30);
  exit_btn_->move(710, 20);
  exit_btn_->setStyleSheet("QPushButton { background: #7d5100;"
                           "border: 2px solid #e9ca5e;"
                           "border-radius: 15px;"
                           "color: #e9ca5e;"
                           "font-size: 20px }"
                           "QPushButton:pressed { background: yellow; }");
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

  open_left_controller_btn_ = new QPushButton(window_);
  open_left_controller_btn_->resize(50, 45);
  open_left_controller_btn_->move(395, 353);
  open_left_controller_btn_->setStyleSheet("QPushButton { background: transparent;"
                                           "color: #184c01;"
                                           "font-size: 45px; } ");
  open_left_controller_btn_->setText("<");
  connect(open_left_controller_btn_, SIGNAL(released()), this, SLOT(editLeftCont()));

  word_edit_ = new QLineEdit(window_);
  word_edit_->resize(300, 45);
  word_edit_->move(180, 330);
  word_edit_->setStyleSheet("QLineEdit { padding-left: 5px; "
                            "font-size: 25px;"
                            "background: #9ea3a2; }"
                            "QLineEdit[text=\"\"] { color: #fff; }");
  word_edit_->setPlaceholderText("Word");
  word_edit_->hide();
  word_edit_->setDisabled(true);

  set_word_btn_ = new QPushButton(window_);
  set_word_btn_->resize(75, 45);
  set_word_btn_->move(180, 390);
  set_word_btn_->setStyleSheet("QPushButton { background: #9ea3a2;"
                               "border-radius: 10px;"
                               "font-size: 20px;"
                               "color: #fff; }"
                               "QPushButton:pressed { margin: 2px 2px 2px 2px; }");
  set_word_btn_->setText("Set");
  set_word_btn_->setDisabled(true);
  set_word_btn_->hide();
  connect(set_word_btn_, SIGNAL(released()), this, SLOT(setWord()));

  //// Alphabets
  tape_alphabet_edit_ = new QLineEdit(window_);
  tape_alphabet_edit_->resize(170, 45);
  tape_alphabet_edit_->move(180, 210);
  tape_alphabet_edit_->setStyleSheet("QLineEdit { padding-left: 5px; "
                                     "font-size: 25px;"
                                     "background: #9ea3a2; }"
                                     "QLineEdit[text=\"\"] { color: #fff; }");
  tape_alphabet_edit_->setPlaceholderText("Tape's");
  tape_alphabet_edit_->setDisabled(true);
  tape_alphabet_edit_->hide();

  heads_alphabet_edit_ = new QLineEdit(window_);
  heads_alphabet_edit_->resize(170, 45);
  heads_alphabet_edit_->move(180, 265);
  heads_alphabet_edit_->setStyleSheet("QLineEdit { padding-left: 5px; "
                                      "font-size: 25px;"
                                      "background: #9ea3a2; }"
                                      "QLineEdit[text=\"\"] { color: #fff; }");
  heads_alphabet_edit_->setPlaceholderText("Head's");
  heads_alphabet_edit_->setDisabled(true);
  heads_alphabet_edit_->hide();

  confirm_alphabets_btn_ = new QPushButton(window_);
  confirm_alphabets_btn_->resize(100, 50);
  confirm_alphabets_btn_->move(365, 210);
  confirm_alphabets_btn_->setStyleSheet("QPushButton { background: #9ea3a2;"
                                        "border-radius: 10px;"
                                        "font-size: 20px;"
                                        "color: #fff; }"
                                        "QPushButton:pressed { margin: 2px 2px 2px 2px; }");
  confirm_alphabets_btn_->setText("Confirm");
  confirm_alphabets_btn_->setDisabled(true);
  confirm_alphabets_btn_->hide();
  connect(confirm_alphabets_btn_, SIGNAL(released()), this, SLOT(confirmAlphabets()));

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

  open_right_controller_btn_ = new QPushButton(window_);
  open_right_controller_btn_->resize(50, 45);
  open_right_controller_btn_->move(1020, 353);
  open_right_controller_btn_->setStyleSheet("QPushButton { background: transparent;"
                                            "color: #184c01;"
                                            "font-size: 45px; } ");
  open_right_controller_btn_->setText(">");
  connect(open_right_controller_btn_, SIGNAL(released()), this, SLOT(editRightCont()));

  //// Table
  cells_.resize(turing_.getTable().size());

  table_label_ = new QLabel(window_);
  table_label_->resize((int) cells_[0].size() * table_cell_width_,
                       (int) cells_.size() * table_cell_height_);
  table_label_->move(975, 205);
  table_label_->setStyleSheet("QTableWidget { background: #9ea3a2; }");
  table_label_->hide();
  table_label_->setDisabled(true);

  table_scroll_area_ = new QScrollArea(window_);
  table_scroll_area_->resize(308, 250);
  table_scroll_area_->move(975, 205);
  table_scroll_area_->setWidget(table_label_);
  table_scroll_area_->setStyleSheet("QScrollArea QScrollBar::handle { background: #fff;"
                                    "border-radius: 8px; }"
                                    "QScrollArea QScrollBar { background: #fff;"
                                    "border: 1px solid #9ea3a2; }"
                                    "QScrollArea { background: #9ea3a2; }");
  table_scroll_area_->setDisabled(true);
  table_scroll_area_->hide();

  add_row_btn_ = new QPushButton(window_);
  add_row_btn_->resize(37, 37);
  add_row_btn_->move(975, 458);
  add_row_btn_->setText("+");
  add_row_btn_->setStyleSheet("QPushButton { background: #9ea3a2; "
                              "color: #fff;"
                              "border-radius: 5px;"
                              "font-size: 25px;"
                              "padding-bottom: 3px;"
                              "text-align: center; }"
                              "QPushButton:pressed { margin: 2px 2px 2px 2px; }");
  connect(add_row_btn_, SIGNAL(released()), this, SLOT(addRow()));
  add_row_btn_->setDisabled(true);
  add_row_btn_->hide();

  delete_row_btn_ = new QPushButton(window_);
  delete_row_btn_->resize(37, 37);
  delete_row_btn_->move(1022, 458);
  delete_row_btn_->setText("-");
  delete_row_btn_->setStyleSheet("QPushButton { background: #9ea3a2; "
                                 "color: #fff;"
                                 "border-radius: 5px;"
                                 "font-size: 25px;"
                                 "padding-bottom: 3px;"
                                 "text-align: center; }"
                                 "QPushButton:pressed { margin: 2px 2px 2px 2px; }");
  connect(delete_row_btn_, SIGNAL(released()), this, SLOT(deleteRow()));
  delete_row_btn_->setDisabled(true);
  delete_row_btn_->hide();

  updateTable();

  //// Tape Window
  curr_word_ldl_ = new QLabel(turing_head_);
  curr_word_ldl_->move(160, 170);
  curr_word_ldl_->resize(200, 40);
  curr_word_ldl_->setStyleSheet("QLabel { background: transparent;"
                                "font-size: 25px;"
                                "color: #9ea3a2; }");
  curr_word_ldl_->setText("Current word:");

  curr_word_holder_ldl_ = new QLabel(turing_head_);
  curr_word_holder_ldl_->move(320, 175);
  curr_word_holder_ldl_->resize(200, 30);
  curr_word_holder_ldl_->setStyleSheet("QLabel { border-bottom: 2px solid #9ea3a2;"
                                       "background: transparent;"
                                       "font-size: 30px;"
                                       "color: #9ea3a2; }");

  tape_.resize(7);
  for (int i = 0; i < 7; ++i) {
    tape_[i] = new QLabel(turing_head_);
    tape_[i]->resize(tape_cell_width_, tape_cell_height_);
    tape_[i]->move(142 + tape_cell_width_ * i, 260);
    tape_[i]->setStyleSheet("QLabel { border: 2px solid #9ea3a2;"
                            "background: transparent;"
                            "font-size: 30px;"
                            "padding-bottom: 7px;"
                            "color: #9ea3a2; }");
    tape_[i]->setAlignment(Qt::AlignCenter);
  }

  left_arrow_btn_ = new QPushButton(turing_head_);
  left_arrow_btn_->resize(40, 40);
  left_arrow_btn_->move(300, 445);
  left_arrow_btn_->setStyleSheet("QPushButton { border-radius: 20px;"
                                 "background: #eeca5a;"
                                 "font-size: 25px;"
                                 "padding-bottom: 3px; }");
  left_arrow_btn_->setText("<-");
  connect(left_arrow_btn_, SIGNAL(released()), this, SLOT(moveHeadToLeft()));

  right_arrow_btn_ = new QPushButton(turing_head_);
  right_arrow_btn_->resize(40, 40);
  right_arrow_btn_->move(350, 445);
  right_arrow_btn_->setStyleSheet("QPushButton { border-radius: 20px;"
                                  "background: #eeca5a;"
                                  "font-size: 25px;"
                                  "padding-bottom: 3px; }");
  right_arrow_btn_->setText("->");
  connect(right_arrow_btn_, SIGNAL(released()), this, SLOT(moveHeadToRight()));

  head_lbl_ = new QLabel(turing_head_);
  head_lbl_->resize(tape_cell_width_, tape_cell_height_);
  head_lbl_->move(142 + tape_cell_width_ * heads_curr_lbl_, 260);
  head_lbl_->setStyleSheet("QLabel { background: transparent;"
                           "border: 6px solid #eeca5a;"
                           "border-radius: 5px; }");

  message_lbl_ = new QLabel(turing_head_);
  message_lbl_->resize(150, 50);
  message_lbl_->move(280, 350);
  message_lbl_->setAlignment(Qt::AlignCenter);
  message_lbl_->setStyleSheet("QLabel { background: transparent; }");

  //// Work buttons
  next_step_btn_ = new QPushButton(turing_head_);
  next_step_btn_->resize(40, 40);
  next_step_btn_->move(200, 80);
  next_step_btn_->setStyleSheet("QPushButton { border-radius: 20px;"
                                "background: #eeca5a;"
                                "font-size: 25px;"
                                "padding-bottom: 3px; }");
  next_step_btn_->setText(">|");
  connect(next_step_btn_, SIGNAL(released()), this, SLOT(nextStep()));

  play_btn_ = new QPushButton(turing_head_);
  play_btn_->resize(40, 40);
  play_btn_->move(255, 80);
  play_btn_->setStyleSheet("QPushButton { border-radius: 20px;"
                           "background: #eeca5a;"
                           "font-size: 25px;"
                           "padding-bottom: 3px; }");
  play_btn_->setText(">");
  connect(play_btn_, SIGNAL(released()), this, SLOT(playWithTuring()));

  pause_btn_ = new QPushButton(turing_head_);
  pause_btn_->resize(40, 40);
  pause_btn_->move(310, 80);
  pause_btn_->setStyleSheet("QPushButton { border-radius: 20px;"
                            "background: #eeca5a;"
                            "font-size: 25px;"
                            "padding-bottom: 3px; }");
  pause_btn_->setText("||");

  stop_btn_ = new QPushButton(turing_head_);
  stop_btn_->resize(40, 40);
  stop_btn_->move(365, 80);
  stop_btn_->setStyleSheet("QPushButton { border-radius: 20px;"
                           "background: #eeca5a;"
                           "font-size: 25px;"
                           "padding-bottom: 3px; }");
  stop_btn_->setText("[x]");

  //// connect local engine
  move_engine_ = new Engine;

  move_thread_ = new QThread;
  connect(move_thread_, &QThread::started, move_engine_, &Engine::moveElmInThread);
  connect(move_engine_, &Engine::move, this, [this](int dis) {
    this->head_lbl_->move(head_lbl_->x() + dis * move_engine_->getDirection(), head_lbl_->y());
  });
  connect(move_engine_, &Engine::finished, this, [this]() {
    this->right_arrow_btn_->setDisabled(false);
    this->left_arrow_btn_->setDisabled(false);
  });
  connect(move_engine_, &Engine::finished, move_thread_, &QThread::quit);

  //// connect turing's engine

  resetTape();
  window_->show();
}

void App::editLeftCont() {
  if (left_opened_) {
    left_controller_->hide();
    left_controller_->move(close_cont_left_x_, close_cont_left_y_);
    left_ear_->move(close_ear_left_x_, close_ear_left_y_);
    open_left_controller_btn_->move(395, 353);
    closeLeftElms();
  } else {
    left_controller_->show();
    left_controller_->move(open_cont_left_x_, open_cont_left_y_);
    left_ear_->move(open_ear_left_x_, open_ear_left_y_);
    open_left_controller_btn_->move(17, 353);
    openLeftElms();
  }
  left_opened_ = !left_opened_;
}

void App::editRightCont() {
  if (right_opened_) {
    right_controller_->hide();
    right_controller_->move(close_cont_right_x_, close_cont_right_y_);
    right_ear_->move(close_ear_right_x_, close_ear_right_y_);
    open_right_controller_btn_->move(1020, 353);
    closeRightElms();
  } else {
    right_controller_->show();
    right_controller_->move(open_cont_right_x_, open_cont_right_y_);
    right_ear_->move(open_ear_right_x_, open_ear_right_y_);
    open_right_controller_btn_->move(1393, 353);
    openRightElms();
  }
  right_opened_ = !right_opened_;
}

void App::exit() {
  std::exit(0);
}

void App::closeLeftElms() {
  message_lbl_->setText("");
  tape_alphabet_edit_->setDisabled(true);
  tape_alphabet_edit_->hide();
  heads_alphabet_edit_->setDisabled(true);
  confirm_alphabets_btn_->setDisabled(true);
  confirm_alphabets_btn_->hide();
  heads_alphabet_edit_->hide();
  open_left_controller_btn_->setText("<");
  word_edit_->hide();
  word_edit_->setDisabled(true);
  set_word_btn_->hide();
  set_word_btn_->setDisabled(true);
}

void App::openLeftElms() {
  message_lbl_->setText("");
  tape_alphabet_edit_->setDisabled(false);
  tape_alphabet_edit_->show();
  heads_alphabet_edit_->setDisabled(false);
  confirm_alphabets_btn_->setDisabled(false);
  confirm_alphabets_btn_->show();
  heads_alphabet_edit_->show();
  open_left_controller_btn_->setText(">");
  word_edit_->show();
  word_edit_->setDisabled(!set_alphabets_);
  set_word_btn_->show();
  set_word_btn_->setDisabled(!set_alphabets_);
}

void App::closeRightElms() {
  message_lbl_->setText("");
  open_right_controller_btn_->setText(">");
  table_label_->hide();
  table_label_->setDisabled(true);
  table_scroll_area_->setDisabled(true);
  table_scroll_area_->hide();
  add_row_btn_->setDisabled(true);
  add_row_btn_->hide();
  delete_row_btn_->setDisabled(true);
  delete_row_btn_->hide();
}

void App::openRightElms() {
  message_lbl_->setText("");
  open_right_controller_btn_->setText("<");
  table_label_->show();
  table_label_->setDisabled(!set_alphabets_);
  table_scroll_area_->setDisabled(!set_alphabets_);
  table_scroll_area_->show();
  add_row_btn_->setDisabled(!set_alphabets_);
  add_row_btn_->show();
  delete_row_btn_->setDisabled(!set_alphabets_);
  delete_row_btn_->show();
}

void App::confirmAlphabets() {
  message_lbl_->setText("");
  auto tape = tape_alphabet_edit_->text().toStdString();
  auto head = heads_alphabet_edit_->text().toStdString();

  backupTable();

  if (!turing_.changeAlphabets(tape, head)) {
    tape_alphabet_edit_->setText("incorrect");
    heads_alphabet_edit_->setText("incorrect");
    return;
  }

  set_alphabets_ = true;
  updateTable();
}

void App::updateTable() {
  if (right_opened_) closeRightElms();

  for (auto &row: cells_) {
    for (auto &cell: row) {
      delete cell;
    }
  }

  cells_.resize(turing_.size());

  for (int i = 0; i < cells_.size(); ++i) {
    cells_[i].resize(turing_(i).size());
    for (int j = 0; j < cells_[i].size(); ++j) {
      cells_[i][j] = new QLineEdit(table_label_);
      cells_[i][j]->resize(table_cell_width_, table_cell_height_);
      cells_[i][j]->move(table_cell_width_ * j, table_cell_height_ * i);
      cells_[i][j]->setAlignment(Qt::AlignCenter);
      cells_[i][j]->setText(QString::fromStdString(turing_(i, j)));
      cells_[i][j]->setStyleSheet("QLabel { border: 1px solid #000;"
                                  "background: #fff;"
                                  "color: #000; }");
    }
  }

  for (auto &cell: cells_) {
    cell[0]->setReadOnly(true);
  }

  for (auto &i: cells_[0]) {
    i->setReadOnly(true);
  }

  table_label_->resize((int) cells_[0].size() * table_cell_width_,
                       (int) cells_.size() * table_cell_height_);

  if (right_opened_) openRightElms();
  if (left_opened_) openLeftElms();
}

void App::addRow() {
  message_lbl_->setText("");
  backupTable();
  turing_.addRow();
  updateTable();
}

void App::deleteRow() {
  message_lbl_->setText("");
  backupTable();
  turing_.deleteRow();
  updateTable();
}

void App::backupTable() {
  for (int i = 1; i < turing_.size(); ++i) {
    for (int j = 1; j < turing_(i).size(); ++j) {
      turing_(i, j) = cells_[i][j]->text().toStdString();
    }
  }
}

void App::setWord() {
  message_lbl_->setText("");
  std::string word = word_edit_->text().toStdString();

  if (!turing_.setWord(word)) {
    word_edit_->setText("incorrect");
    return;
  }

  curr_word_holder_ldl_->setText(QString::fromStdString(word));
  resetTape();
}

void App::resetTape() {
  message_lbl_->setText("");
  turing_.setCurrPos(turing_.recoverCurrPos());
  left_border_ = turing_.getCurrPos();
  right_border_ = left_border_ + 7;

  for (int i = 0; i < 7; ++i) {
    char letter = turing_.getElm(left_border_ + i);
    if (letter == -1) {
      tape_[i]->setText(QString::fromStdString("/\\"));
    } else {
      tape_[i]->setText(QChar(letter));
    }
  }

  heads_curr_lbl_ = 0;
  head_lbl_->move(142 + tape_cell_width_ * heads_curr_lbl_, 260);
}

void App::moveHeadToRight() {
  message_lbl_->setText("");
  if (!from_step_) works_ = false;

  if (heads_curr_lbl_ == 6) {
    left_border_ += 2;
    right_border_ += 2;
    --heads_curr_lbl_;
    setTape();
    return;
  }
  ++heads_curr_lbl_;

  move_engine_->setDirection(1);
  right_arrow_btn_->setDisabled(true);
  left_arrow_btn_->setDisabled(true);

  move_engine_->moveToThread(move_thread_);
  move_thread_->start();
}

void App::moveHeadToLeft() {
  message_lbl_->setText("");
  if (!from_step_) works_ = false;

  if (heads_curr_lbl_ == 0) {
    left_border_ -= 2;
    right_border_ -= 2;
    ++heads_curr_lbl_;
    setTape();
    return;
  }
  --heads_curr_lbl_;

  move_engine_->setDirection(-1);
  right_arrow_btn_->setDisabled(true);
  left_arrow_btn_->setDisabled(true);

  move_engine_->moveToThread(move_thread_);
  move_thread_->start();
}

void App::nextStep() {
  backupTable();
  if (!works_) {
    resetTape();
    works_ = true;
  }

  int ret = turing_.nextStep();
  if (ret == -1e5) {
    callError();
    return;
  }

  setTape();

  if (ret == 100) {
    callStop();
    return;
  }

  from_step_ = true;
  if (ret < 0) {
    moveHeadToLeft();
  } else if (ret > 0) {
    moveHeadToRight();
  }
  from_step_ = false;

  if (ret == 10 || ret == -10) {
    callStop();
  }
}

void App::setTape() {
  for (int i = 0; i < 7; ++i) {
    char letter = turing_.getElm(left_border_ + i);
    if (letter == -1) {
      tape_[i]->setText(QString::fromStdString("/\\"));
    } else {
      tape_[i]->setText(QChar(letter));
    }
  }

  head_lbl_->move(142 + tape_cell_width_ * heads_curr_lbl_, 260);
}

void App::callError() {
  works_ = false;

  message_lbl_->setStyleSheet("QLabel { background: transparent;"
                              "color: red;"
                              "font-size: 25px; }");
  message_lbl_->setText("error");
}

void App::callStop() {
  works_ = false;

  message_lbl_->setStyleSheet("QLabel { background: transparent;"
                              "color: #9ea3a2;"
                              "font-size: 25px; }");
  message_lbl_->setText("stopped");
}

void App::playWithTuring() {
  if (!works_) {
    setTape();
    works_ = true;
  }


}

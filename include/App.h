//
// Created by_ Тимур Ахметзянов on 22.02.2024.
//

#pragma once

#include "Turing.h"
#include "header.h"


class App : QMainWindow {
 Q_OBJECT

 public:
  App();

 private slots:

  void editLeftCont();

  void editRightCont();

  static void exit();

  void confirmAlphabets();

  void addRow();

  void deleteRow();

  void setWord();

 private:
  const int table_cell_width_ = 70, table_cell_height_ = 40;
  const int tape_cell_width_ = 60, tape_cell_height_ = 60;
  const int width = 1500, height = 800;
  const int close_ear_left_x_ = 370, close_ear_left_y_ = 150;
  const int open_ear_left_x_ = -8, open_ear_left_y_ = 150;
  const int open_cont_left_x_ = 70, open_cont_left_y_ = 125;
  const int close_cont_left_x_ = 448, close_cont_left_y_ = 125;
  const int close_ear_right_x_ = 860, close_ear_right_y_ = 150;
  const int open_ear_right_x_ = 1233, open_ear_right_y_ = 150;
  const int open_cont_right_x_ = 840, open_cont_right_y_ = 125;
  const int close_cont_right_x_ = 462, close_cont_right_y_ = 125;

  bool left_opened_ = false;
  bool right_opened_ = false;
  bool set_alphabets_ = false;

  Turing turing_;

  QMainWindow *window_;

  QWidget *turing_head_;
  QWidget *left_ear_;
  QWidget *left_controller_;
  QWidget *right_ear_;
  QWidget *right_controller_;

  QPushButton *open_left_controller_btn_;
  QPushButton *open_right_controller_btn_;
  QPushButton *exit_btn_;
  QPushButton *confirm_alphabets_btn_;
  QPushButton *add_row_btn_;
  QPushButton *delete_row_btn_;
  QPushButton *set_word_btn_;

  QLineEdit *tape_alphabet_edit_;
  QLineEdit *heads_alphabet_edit_;
  QLineEdit *word_edit_;
  std::vector<std::vector<QLineEdit *>> cells_;

  QLabel *table_label_;
  QLabel *curr_word_ldl_;
  std::vector<QLabel*> tape_;

  QScrollArea *table_scroll_area_;

  void closeLeftElms();

  void openLeftElms();

  void closeRightElms();

  void openRightElms();

  void updateTable();

  void backupTable();

  void setTape();
};

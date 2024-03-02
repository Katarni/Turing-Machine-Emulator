//
// Created by Тимур Ахметзянов on 25.02.2024.
//

#pragma once

#include "header.h"
#include "Engine.h"


class Turing: public QObject {
  Q_OBJECT

 public:
  Turing();

  bool changeAlphabets(std::string &new_tape, std::string &new_head);

  void updateTable(bool clean);

  const std::vector<std::vector<std::string>> &getTable() const;

  std::string &operator()(int i, int j);

  const std::string &operator()(int i, int j) const;

  std::vector<std::string> &operator()(int i);

  const std::vector<std::string> &operator()(int i) const;

  const size_t &size() const {
    return table_.size();
  }

  void addRow();

  void deleteRow();

  bool setWord(const std::string &word);

  const std::string &getCurrWord();

  int recoverCurrPos() const;

  void setCurrPos(int currPos);

  int getCurrPos() const;

  char getElm(int i);

  int nextStep();

 private:
  int lambda_pos_ = 1;
  int curr_pos_ = 5e3;
  int curr_state_ = 0;

  std::vector<char> tape_;

  std::string heads_alphabet_, tapes_alphabet_, start_word_;
  std::vector<std::vector<std::string>> table_;
};

//
// Created by Тимур Ахметзянов on 25.02.2024.
//

#include "header.h"

class Turing {
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

  const int &getCurrentPos() const;

  void start();

 private:
  int lambda_pos_ = 1;
  int curr_pos_ = 5e3;

  std::vector<char> tape_;

  std::string heads_alphabet_, tapes_alphabet_, start_word_;
  std::vector<std::vector<std::string>> table_;
};

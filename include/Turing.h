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

  void setTable(const std::vector<std::vector<std::string>> &table);

 private:
  int lambda_pos_ = 1;
  int crt_pos_;
  std::vector<char> tape_;

  std::string heads_alphabet_, tapes_alphabet_;
  std::vector<std::vector<std::string>> table_;
};

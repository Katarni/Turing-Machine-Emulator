//
// Created by Тимур Ахметзянов on 25.02.2024.
//

#include "header.h"

class Turing {
 public:
  Turing();

  void changeAlphabets(std::string &new_tape, std::string &new_head);

  void updateTable(bool clean);

 private:
  int lambda_pos = 1;
  std::vector<char> tape;

  std::string heads_alphabet_, tapes_alphabet_;
  std::vector<std::vector<std::string>> table_;
};

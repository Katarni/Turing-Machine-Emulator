//
// Created by Тимур Ахметзянов on 25.02.2024.
//

#include "../include/Turing.h"

Turing::Turing() {
  tape.resize(1e6, -1);
  heads_alphabet_ = "";
  tapes_alphabet_ = "";
  table_.resize(1);
  table_[0].resize(2);
  table_[0][1] = "-1";
}

void Turing::changeAlphabets(const std::string &new_tape, const std::string &new_head) {

}

void Turing::updateTable(bool clean) {

}

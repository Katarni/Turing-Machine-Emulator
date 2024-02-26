//
// Created by Тимур Ахметзянов on 25.02.2024.
//

#include "../include/Turing.h"

Turing::Turing() {
  tape_.resize(1e5, -1);
  crt_pos_ = 1e5 / 2;
  heads_alphabet_ = "";
  tapes_alphabet_ = "";
  table_.resize(1);
  table_[0].resize(2);
  table_[0][1] = "/\\";
}

bool Turing::changeAlphabets(std::string &new_tape, std::string &new_head) {
  // проверить алфавиты на корректность

  for (char c : tapes_alphabet_) {
    if (new_tape.find(c) == std::string::npos) {
      tapes_alphabet_.swap(new_tape);
      heads_alphabet_.swap(new_head);
      updateTable(true);
      return true;
    }
  }

  tapes_alphabet_.swap(new_tape);
  for (char c : heads_alphabet_) {
    if (new_head.find(c) == std::string::npos) {
      heads_alphabet_.swap(new_head);
      updateTable(true);
      return true;
    }
  }

  heads_alphabet_.swap(new_head);
  updateTable(false);
  return true;
}

void Turing::updateTable(bool clean) {
  if (clean) {
    table_.resize(1);
    table_[0].resize(2 + heads_alphabet_.size() + tapes_alphabet_.size());
    lambda_pos_ = 1 + (int)tapes_alphabet_.size();
    for (int i = 1; i < lambda_pos_; ++i) {
      table_[0][i] = tapes_alphabet_[i - 1];
    }

    table_[0][lambda_pos_] = "/\\";
    for (int i = lambda_pos_ + 1; i < table_[0].size(); ++i) {
      table_[0][i] = heads_alphabet_[i - lambda_pos_ - 1];
    }
    return;
  }

  std::unordered_set<char> letters;
  for (const char& c : tapes_alphabet_) letters.insert(c);

  for (int i = 1; i < lambda_pos_; ++i) {
    letters.erase(table_[0][i][0]);
  }

  for (auto& row : table_) {
    row.resize(row.size() + letters.size());
    for (int j = (int)row.size() - (int)letters.size() - 1; j >= lambda_pos_; --j) {
      row[j + letters.size()] = row[j];
    }
  }

  for (const char& c : letters) {
    table_[0][lambda_pos_] = c;
    ++lambda_pos_;
  }

  letters.clear();
  for (const char& c : heads_alphabet_) letters.insert(c);

  for (int i = lambda_pos_ + 1; i < table_[0].size(); ++i) {
    letters.erase(table_[0][i][0]);
  }

  for (auto& row : table_) {
    row.resize(row.size() + letters.size());
  }

  int j = (int)table_[0].size() - (int)letters.size();
  for (const char& c : letters) {
    table_[0][j++] = c;
  }
}

const std::vector<std::vector<std::string>> &Turing::getTable() const {
  return table_;
}

void Turing::setTable(const std::vector<std::vector<std::string>> &table) {
  table_ = table;
}

std::string &Turing::operator()(int i, int j) {
  return table_[i][j];
}

const std::string &Turing::operator()(int i, int j) const {
  return table_[i][j];
}

std::vector<std::string> &Turing::operator()(int i) {
  return table_[i];
}

const std::vector<std::string> &Turing::operator()(int i) const {
  return table_[i];
}

void Turing::addRow() {
  table_.resize(table_.size() + 1);
  table_.back().resize(table_[0].size());
  table_.back()[0] = "q" + std::to_string(table_.size() - 2);
}

void Turing::deleteRow() {
  if (table_.size() == 1) return;

  table_.resize(table_.size() - 1);
}

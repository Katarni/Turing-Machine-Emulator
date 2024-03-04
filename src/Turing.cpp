//
// Created by Тимур Ахметзянов on 25.02.2024.
//

#include "../include/Turing.h"

Turing::Turing() {
  tape_.resize(1e4, '^');
  heads_alphabet_ = "";
  tapes_alphabet_ = "";
  table_.resize(1);
  table_[0].resize(2);
  table_[0][1] = "^";
  addRow();
}

bool Turing::changeAlphabets(std::string &new_tape, std::string &new_head) {
  // проверить алфавиты на корректность

  std::unordered_set<char> letters;
  for (char c : new_tape) {
    letters.insert(c);
  }
  for (char c : new_head) {
    letters.insert(c);
  }

  if (new_head.size() + new_tape.size() != letters.size()) {
    return false;
  }

  for (char c: tapes_alphabet_) {
    if (new_tape.find(c) == std::string::npos) {
      tapes_alphabet_.swap(new_tape);
      heads_alphabet_.swap(new_head);
      updateTable(true);
      return true;
    }
  }

  tapes_alphabet_.swap(new_tape);
  for (char c: heads_alphabet_) {
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
    lambda_pos_ = 1 + (int) tapes_alphabet_.size();
    for (int i = 1; i < lambda_pos_; ++i) {
      table_[0][i] = tapes_alphabet_[i - 1];
    }

    table_[0][lambda_pos_] = "^";
    for (int i = lambda_pos_ + 1; i < table_[0].size(); ++i) {
      table_[0][i] = heads_alphabet_[i - lambda_pos_ - 1];
    }

    addRow();
    return;
  }

  std::unordered_set<char> letters;
  for (const char &c: tapes_alphabet_) letters.insert(c);

  for (int i = 1; i < lambda_pos_; ++i) {
    letters.erase(table_[0][i][0]);
  }

  for (auto &row: table_) {
    row.resize(row.size() + letters.size());
    for (int j = (int) row.size() - (int) letters.size() - 1; j >= lambda_pos_; --j) {
      row[j + letters.size()] = row[j];
    }
  }

  for (const char &c: letters) {
    table_[0][lambda_pos_] = c;
    ++lambda_pos_;
  }

  letters.clear();
  for (const char &c: heads_alphabet_) letters.insert(c);

  for (int i = lambda_pos_ + 1; i < table_[0].size(); ++i) {
    letters.erase(table_[0][i][0]);
  }

  for (auto &row: table_) {
    row.resize(row.size() + letters.size());
  }

  int j = (int) table_[0].size() - (int) letters.size();
  for (const char &c: letters) {
    table_[0][j++] = c;
  }
}

const std::vector<std::vector<std::string>> &Turing::getTable() const {
  return table_;
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
  if (table_.size() <= 2) return;

  table_.resize(table_.size() - 1);
}

bool Turing::setWord(const std::string &word) {
  // проверить на корректность

  for (char &letter: tape_) {
    letter = -1;
  }
  curr_pos_ = 5e3;
  for (int i = curr_pos_; i < curr_pos_ + word.size(); ++i) {
    tape_[i] = word[i - curr_pos_];
  }

  start_word_ = word;

  return true;
}

const std::string &Turing::getCurrWord() {
  int start = -1, end = -1;
  for (int i = 0; i < tape_.size(); ++i) {
    if (tape_[i] != -1 && start == -1) {
      start = i;
    }
    if (tape_[i] != -1) {
      end = i + 1;
    }
  }

  std::string word, space = "^";
  for (int i = start; i < end; ++i) {
    if (tape_[i] == -1) {
      word.insert(word.end(), space.begin(), space.end());
    } else {
      word.push_back(tape_[i]);
    }
  }

  return word;
}

int Turing::recoverCurrPos() const {
  for (int i = 0; i < tape_.size(); ++i) {
    if (tape_[i] != -1) return i;
  }
  return 5e3;
}

void Turing::setCurrPos(int currPos) {
  curr_pos_ = currPos;
}

int Turing::getCurrPos() const {
  return curr_pos_;
}

char Turing::getElm(int i) {
  return tape_[i];
}

int Turing::nextStep() {
  int curr_cell = -1;
  for (int i = 1; i < table_[0].size(); ++i) {
    if (table_[0][i][0] == tape_[curr_pos_]) {
      curr_cell = i;
    }
  }

  if (curr_cell == -1 ||
      table_[curr_state_ + 1][curr_cell].empty() ||
      table_[curr_state_ + 1][curr_cell].size() > 3) {
    return -1e5;
  }

  int ret = 0;
  bool last = false;
  for (char c : table_[curr_state_ + 1][curr_cell]) {
    if (c == 'L') {
      ret = -1;
      --curr_pos_;
      continue;
    }

    if (c == 'R') {
      ret = 1;
      ++curr_pos_;
      continue;
    }

    if (c == '!') {
      last = true;
      continue;
    }

    if (c >= '0' && c <= '9') {
      if (c - '0' >= table_.size() - 1) return -1e5;
      curr_state_ = c - '0';
      continue;
    }

    if (tapes_alphabet_.find(c) == std::string::npos &&
        heads_alphabet_.find(c) == std::string::npos) {
      return -1e5;
    }

    tape_[curr_pos_] = c;
  }

  if (last && ret != 0) return ret * 10;
  else if (last) return 100;

  return ret;
}

void Turing::play() {

}

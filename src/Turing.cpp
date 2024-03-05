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

  move_engine = new Engine;
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
    if ((int)letters.size() == 0) continue;
    for (int j = (int) row.size() - (int) letters.size() - 1; j >= lambda_pos_; --j) {
      row[j + letters.size()] = row[j];
      row[j].clear();
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
  for (char c : word) {
    if (heads_alphabet_.find(c) == std::string::npos &&
      tapes_alphabet_.find(c) == std::string::npos) {
      return false;
    }
  }

  for (char &letter: tape_) {
    letter = '^';
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
    if (tape_[i] != '^' && start == -1) {
      start = i;
    }
    if (tape_[i] != '^') {
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
    if (tape_[i] != '^') return i;
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
      break;
    }
  }

  if (curr_cell == -1 ||
      table_[curr_state_ + 1][curr_cell].empty() ||
      table_[curr_state_ + 1][curr_cell].size() > 4) {
    return -1e5;
  }

  int ret = 0;
  bool last = false;
  bool moved = false, edited = false, edit_state = false, state_current_edit = false;
  int state = -1;
  for (char c : table_[curr_state_ + 1][curr_cell]) {
    if (c == 'L') {
      if (moved) return -1e5;
      if (state_current_edit) {
        edit_state = true;
        state_current_edit = false;
        if (state >= table_.size() - 1) {
          return -1e5;
        }
        if (state != -1) {
          emit stateChanged(curr_state_, state);
        }
        curr_state_ = state == -1 ? curr_state_ : state;
      }
      ret = -1;
      --curr_pos_;
      moved = true;
      continue;
    }

    if (c == 'R') {
      if (moved) return -1e5;
      if (state_current_edit) {
        edit_state = true;
        state_current_edit = false;
        if (state >= table_.size() - 1) {
          return -1e5;
        }
        if (state != -1) {
          emit stateChanged(curr_state_, state);
        }
        curr_state_ = state == -1 ? curr_state_ : state;
      }
      ret = 1;
      ++curr_pos_;
      moved = true;
      continue;
    }

    if (c == '!') {
      last = true;
      continue;
    }

    if (c >= '0' && c <= '9') {
      if (edit_state) return -1e5;
      if (state == -1) state = 0;
      state = state * 10 + c - '0';
      state_current_edit = true;
      continue;
    }

    if (tapes_alphabet_.find(c) == std::string::npos &&
        heads_alphabet_.find(c) == std::string::npos) {
      return -1e5;
    }

    if (edited) return -1e5;
    if (state_current_edit) {
      edit_state = true;
      state_current_edit = false;
      if (state != -1) {
        emit stateChanged(curr_state_, state);
      }
      curr_state_ = state == -1 ? curr_state_ : state;
    }
    tape_[curr_pos_] = c;
    edited = true;
  }

  if (state_current_edit) {
    if (state >= table_.size() - 1) {
      return -1e5;
    }
    if (state != -1) {
      emit stateChanged(curr_state_, state);
    }
    curr_state_ = state == -1 ? curr_state_ : state;
  }

  if (last && ret != 0) return ret * 10;
  else if (last) return 100;

  return ret;
}

void Turing::play() {
  while (true) {
    if (paused_) {
      emit paused();
      return;
    }

    if (force_stop_) {
      emit forceStop();
      return;
    }

    int ret = nextStep();

    if (ret == -1e5) {
      emit error();
      return;
    }

    if (ret == 100) {
      emit stopped();
      return;
    }

    if (ret < 0) {
      emit readyToMove(false);
      move_engine->setDirection(-1);
      move_engine->moveElmOutThread();
    } else {
      emit readyToMove(true);
      move_engine->setDirection(1);
      move_engine->moveElmOutThread();
    }

    if (ret == 10 || ret == -10) {
      emit stopped();
      return;
    }
  }
}

void Turing::setPaused(bool paused) {
  paused_ = paused;
}

void Turing::setForceStop(bool force_stop) {
  force_stop_ = force_stop;
}

bool Turing::cantStop() {
  for (int i = 1; i < table_.size(); ++i) {
    for (int j = 1; j < table_[i].size(); ++j) {
      if (table_[i][j].find('!') != std::string::npos) {
        return false;
      }
    }
  }
  return true;
}

void Turing::setCurrState(int curr_state) {
  curr_state_ = curr_state;
}

int Turing::getCurrState() const {
  return curr_state_;
}

void Turing::resetWord() {
  setWord(start_word_);
}

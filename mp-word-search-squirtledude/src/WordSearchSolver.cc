#include "WordSearchSolver.hpp"
#include <cstddef>
#include <limits>
bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}
WordLocation WordSearchSolver::FindWord(const std::string& word){
  WordLocation toreturn;
  if (FindWord(word, CheckDirection::kHorizontal).word == word){
    toreturn.word = FindWord(word, CheckDirection::kHorizontal).word;
    toreturn.char_positions = FindWord(word, CheckDirection::kHorizontal).char_positions;
  } else if (FindWord(word, CheckDirection::kVertical).word == word){
    toreturn.word = FindWord(word, CheckDirection::kVertical).word;
    toreturn.char_positions = FindWord(word, CheckDirection::kVertical).char_positions;
  } else if (FindWord(word, CheckDirection::kRightDiag).word == word){
    toreturn.word = FindWord(word, CheckDirection::kRightDiag).word;
    toreturn.char_positions = FindWord(word, CheckDirection::kRightDiag).char_positions;
  } else if (FindWord(word, CheckDirection::kLeftDiag).word == word){
    toreturn.word = FindWord(word, CheckDirection::kLeftDiag).word;
    toreturn.char_positions = FindWord(word, CheckDirection::kLeftDiag).char_positions;
  }
  return toreturn;
}
WordSearchSolver::WordSearchSolver(const std::vector<std::vector<char>>& puzzle) : puzzle_(puzzle){
  puzzle_height_ = puzzle.size();
  puzzle_width_ = puzzle.at(0).size();
}
WordLocation WordSearchSolver::FindWord(const std::string& word, CheckDirection direction){
  WordLocation toreturn;
  if (direction == CheckDirection::kHorizontal){
    toreturn.word = CheckHorizontal(word).word;
    toreturn.char_positions = CheckHorizontal(word).char_positions;
  } else if (direction == CheckDirection::kVertical){
    toreturn.word = CheckVertical(word).word;
    toreturn.char_positions = CheckVertical(word).char_positions;
  } else if (direction == CheckDirection::kRightDiag){
    toreturn.word = CheckRightDiag(word).word;
    toreturn.char_positions = CheckRightDiag(word).char_positions;
  } else if (direction == CheckDirection::kLeftDiag){
    toreturn.word = CheckLeftDiag(word).word;
    toreturn.char_positions = CheckLeftDiag(word).char_positions;
  }
  return toreturn;
}
WordLocation WordSearchSolver::CheckHorizontal(const std::string& word){
  WordLocation toreturn;
  for (size_t i = 0; i < puzzle_height_; ++i){
    for (size_t j = 0; j < puzzle_width_; ++j){
      if (puzzle_.at(i).at(j) == word[0]){
        if (ForwardHorizontalTraversal(word, i, j)){
          toreturn.word = word;
          size_t tempwidth = j;
          size_t trav = 0;
          while (trav < word.size()){
            CharPositions entry = {' ', 0, 0};
            entry.character = word[trav];
            entry.row = i;
            entry.col = tempwidth;
            toreturn.char_positions.push_back(entry);
            tempwidth++;
            trav++;
          }
        }
      }
    }
  }
  return toreturn;
}
WordLocation WordSearchSolver::CheckVertical(const std::string& word){
  WordLocation toreturn;
  for (size_t i = 0; i < puzzle_height_; ++i){
    for (size_t j = 0; j < puzzle_width_; ++j){
      if (puzzle_.at(i).at(j) == word[0]){
        if (VerticalTraversal(word, i, j)){
          toreturn.word = word;
          size_t tempheight = i;
          size_t trav = 0;
          while (trav < word.size()){
            CharPositions entry = {' ', 0, 0};
            entry.character = word[trav];
            entry.row = tempheight;
            entry.col = j;
            toreturn.char_positions.push_back(entry);
            tempheight++;
            trav++;
          }
        }
      }
    }
  }
  return toreturn;
}
WordLocation WordSearchSolver::CheckRightDiag(const std::string& word){
  WordLocation toreturn;
  for (size_t i = 0; i < puzzle_height_; ++i){
    for (size_t j = 0; j < puzzle_width_; ++j){
      if (puzzle_.at(i).at(j) == word[0]){
        if (RightDiagTraversal(word, i, j)){
          toreturn.word = word;
          size_t tempheight = i;
          size_t tempwidth = j;
          size_t trav = 0;
          while (trav < word.size()){
            CharPositions entry = {' ', 0, 0};
            entry.character = word[trav];
            entry.row = tempheight;
            entry.col = tempwidth;
            toreturn.char_positions.push_back(entry);
            tempheight++;
            tempwidth++;
            trav++;
          }
        }
      }
    }
  }
  return toreturn;
}
WordLocation WordSearchSolver::CheckLeftDiag(const std::string& word){
  WordLocation toreturn;
  for (size_t i = 0; i < puzzle_height_; ++i){
    for (size_t j = 0; j < puzzle_width_; ++j){
      if (puzzle_.at(i).at(j) == word[0]){
        if (LeftDiagTraversal(word, i, j)){
          toreturn.word = word;
          size_t tempheight = i;
          size_t tempwidth = j;
          size_t trav = 0;
          while (trav < word.size()){
            CharPositions entry = {' ', 0, 0};
            entry.character = word[trav];
            entry.row = tempheight;
            entry.col = tempwidth;
            toreturn.char_positions.push_back(entry);
            tempheight++;
            tempwidth--;
            trav++;
          }
        }
      }
    }
  }
  return toreturn;
}
bool WordSearchSolver::RightDiagTraversal(const std::string& word, size_t i, size_t j){
  size_t trav = 0;
  std::string compare;
  while (trav < word.size() && LocationInBounds(i, j)){
    compare += puzzle_.at(i).at(j);
    i++;
    j++;
    trav++;
  }
  return (word == compare);
}
bool WordSearchSolver::LeftDiagTraversal(const std::string& word, size_t i, size_t j){
  size_t trav = 0;
  std::string compare;
  while (trav < word.size() && LocationInBounds(i, j)){
    compare += puzzle_.at(i).at(j);
    i++;
    j--;
    trav++;
  }
  return (word == compare);
}
bool WordSearchSolver::VerticalTraversal(const std::string& word, size_t i, size_t j){
  std::string toreturn;
  size_t trav = 0;
  while (trav < word.size() && LocationInBounds(i, j)){
    toreturn += puzzle_.at(i).at(j);
    i++;
    trav++;
  }
  return (word == toreturn);
}
bool WordSearchSolver::ForwardHorizontalTraversal(const std::string& word, size_t i, size_t j){
  std::string toreturn;
  size_t temp = 0;
  while (temp < word.size() && LocationInBounds(i, j)){
    toreturn += puzzle_.at(i).at(j);
    j++;
    temp++;
  }
  return (word == toreturn);
}
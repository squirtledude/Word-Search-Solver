#ifndef WORDSEARCHSOLVER_HPP
#define WORDSEARCHSOLVER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "WordLocation.hpp"

enum class CheckDirection { kHorizontal, kVertical, kLeftDiag, kRightDiag };

class WordSearchSolver {
public:
  WordSearchSolver(const std::vector<std::vector<char>>& puzzle);
  WordLocation FindWord(const std::string& word);
  WordLocation FindWord(const std::string& word, CheckDirection direction);
  

private:
  WordLocation CheckHorizontal(const std::string& word);
  WordLocation CheckVertical(const std::string& word);
  WordLocation CheckRightDiag(const std::string& word);
  WordLocation CheckLeftDiag(const std::string& word);
  bool LocationInBounds(size_t row, size_t col) const;
  bool ForwardHorizontalTraversal(const std::string& word, size_t i, size_t j);
  bool VerticalTraversal(const std::string& word, size_t i, size_t j);
  bool RightDiagTraversal(const std::string& word, size_t i, size_t j);
  bool LeftDiagTraversal(const std::string& word, size_t i, size_t j);
  std::vector<std::vector<char>> puzzle_;
  size_t puzzle_height_;
  size_t puzzle_width_;
};

#endif
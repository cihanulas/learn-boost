// Algorithms.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include "Algorithms.h"

#include <vector>

int main() {
  EvaluateAllOf(std::vector<int>{1, 2, 3}, greter_than_1, false);
  EvaluateAllOf(std::vector<int>{4, 2, 3}, greter_than_1, true);

  // only one of
  EvaluateOneOf(std::vector<int>{0, 0, 3}, isOdd, true);
  EvaluateOneOf(std::vector<int>{2, 4, 6}, isOdd, false);

  EvaluateOneOf(std::vector<int>{0, 0, 0}, greter_than_1, false);
  EvaluateOneOf(std::vector<int>{0, 2, 2}, greter_than_1, false);  //**
  EvaluateOneOf(std::vector<int>{0, 0, 2}, greter_than_1, true);

  // any one of
  EvaluateAnyOf(std::vector<int>{0, 0, 0}, greter_than_1, false);
  EvaluateAnyOf(std::vector<int>{0, 2, 2}, greter_than_1, true);  //**
  EvaluateAnyOf(std::vector<int>{0, 0, 2}, greter_than_1, true);

  EvaluateIsSorted(std::vector<int>{0, 1, 2}, std::less<int>(), true);
  EvaluateIsSorted(std::vector<int>{0, 2, 1}, std::less<int>(), false);
  EvaluateIsSorted(std::vector<int>{3, 2, 1}, std::greater<int>(), true);
  EvaluateIsSorted(std::vector<int>{3, 1, 2}, std::less<int>(), false);
  // is permutation
  {
    std::vector<int> vec1{1, 2, 3, 14, 15};
    std::vector<int> vec2{15, 14, 3, 1, 2};
    bool state = boost::algorithm::is_permutation(vec1.begin(), vec1.end(),
                                                  vec2.begin());
    if (!state) std::cout << "IsPermutation NOK" << std::endl;
  }
  // partition vector
  {
    std::vector<int> vec = {
        3, 9, 0, 6, 4, 8, 2, 5, 7, 1};  // part1: 7,9, 8,6, 4*, part2: 0, 2, ..
    auto middle =
        boost::range::partition(vec, greter_than_5);  // return iterator 4.
    if (*middle != 4) std::cout << "Partition is NOK" << std::endl;
  }

  {
    std::vector<int> vec(5, 0);
    // Returns a reference to the input range.
    boost::range::iota(vec, 10);
    boost::copy(vec, std::ostream_iterator<int>(std::cout, " "));
  }
  // is equal
  {
    auto seq1 = {0, 1, 2};
    auto seq2 = {0, 1, 2, 3, 4};
    bool equal = std::equal(seq1.begin(), seq1.end(), seq2.begin());  // true
    bool not_equal =
        std::equal(seq2.begin(), seq2.end(), seq1.begin());  // false
    bool not_equal_2 = std::equal(seq1.begin(), seq1.end(), seq2.begin(),
                                  seq2.end());  // false
  }

  // mis match
  auto seq1 = {0, 1, 2};
  auto seq2 = {0, 1, 2, 3, 4};
  std::mismatch(seq1.begin(), seq1.end(), seq2.begin());  // <3, 3>
  std::mismatch(seq2.begin(), seq2.end(), seq1.begin());  // Undefined behavior
  std::mismatch(seq1.begin(), seq1.end(), seq2.begin(), seq2.end());  // <3, 3>
}
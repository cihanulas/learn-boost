#pragma once
#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/algorithm/cxx11/any_of.hpp>
#include <boost/algorithm/cxx11/is_permutation.hpp>
#include <boost/algorithm/cxx11/is_sorted.hpp>
#include <boost/algorithm/cxx11/one_of.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>  // iota
#include <functional>
#include <iostream>

static bool greter_than_1(int val) { return val > 1; }
static bool greter_than_5(int val) { return val > 5; }

static bool isOdd(int i) { return i % 2 == 1; }

template <class C>
static void Evaluate(const char* name, bool evaluation, bool expectation,
                     const C& vec) {
  if (evaluation != expectation) {
    std::cout << name << " NOK for" << std::endl;
    for (auto v : vec) {
      std::cout << v << " ";
    }
    std::cout << std::endl;
  }
}

template <class C, class Evaluater>
static void EvaluateAllOf(const C& vec, const Evaluater& ev, bool expectation) {
  bool evaluation = boost::algorithm::all_of(vec, ev);
  Evaluate(__FUNCTION__, evaluation, expectation, vec);
};

template <class C, class Evaluater>
static void EvaluateOneOf(const C& vec, const Evaluater& ev, bool expectation) {
  bool evaluation = boost::algorithm::one_of(vec, ev);
  Evaluate(__FUNCTION__, evaluation, expectation, vec);
};

template <class C, class Evaluater>
static void EvaluateAnyOf(const C& vec, const Evaluater& ev, bool expectation) {
  bool evaluation = boost::algorithm::any_of(vec, ev);
  Evaluate(__FUNCTION__, evaluation, expectation, vec);
};

template <class C, class Evaluater>
static void EvaluateIsSorted(const C& vec, const Evaluater& ev,
                             bool expectation) {
  bool evaluation = boost::algorithm::is_sorted(vec, ev);
  Evaluate(__FUNCTION__, evaluation, expectation, vec);
};

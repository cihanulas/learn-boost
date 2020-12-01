#include <algorithm>
#include <boost/lambda/lambda.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <iterator>
#include <vector>

void example_lexical_cast() {
  int s = 23;
  std::string str = boost::lexical_cast<std::string>(s);
  str = "asd" + boost::lexical_cast<std::string>(3.14);
  std::cout << "example_lexical_cast: " << str
            << boost::lexical_cast<std::string>('A') << std::endl;
  auto msg = boost::lexical_cast<std::array<char, 64>>(23);
  s = boost::lexical_cast<int>("234");  // s = 234
  try {
    s = boost::lexical_cast<int>("56.78");  // throw exception: bad_lexical_cast

  } catch (const boost::bad_lexical_cast& e) {
    std::cout << "bad lexical cast" << e.what() << std::endl;
  }

  try {
    s = boost::lexical_cast<int>("123w");  // throw exception: bad_lexical_cast

  } catch (const boost::bad_lexical_cast& e) {
    std::cout << "bad lexical cast" << e.what() << std::endl;
  }

  s = boost::lexical_cast<int>("123w", 3);  // ok 123. evaluate first three.
}

void example_regex() {
  std::string line;
  boost::regex pat("^Subject: (Re: |Aw: )*(.*)");

  while (std::cin) {
    std::getline(std::cin, line);
    boost::smatch matches;
    if (boost::regex_match(line, matches, pat))
      std::cout << matches[2] << std::endl;
  }
}

void example_variant() {
  boost::variant<int, std::string> u1,
      u2;  // u1 or u2 can store either int or string
  u1 = 2;
  u2 = "hello";
  std::cout << "u1: " << u1 << ", u2: " << u2 << std::endl;
  // int u12 = u1 * 2; // does not work. * is not overloaded.
  int u12 = boost::get<int>(u1) * 2;
  try {
    auto s_u12 = boost::get<std::string>(u1);  // throw exception of bad_get;
  } catch (boost::bad_get& e) {
    std::cout << e.what() << std::endl;
  }

  u1 = "good";  // it is now string
  u1 = 32;      // it is int again.

  // using Visitor Pattern
  class DoubleVisitor : public boost::static_visitor<> {
   public:
    void operator()(int& i) const {
      //
      i += i;
    }
    void operator()(std::string& str) const {
      //
      str += str;
    }
  };

  u1 = 2;
  boost::apply_visitor(DoubleVisitor(), u1);  // u1 becomes 4
  u2 = "hi";
  boost::apply_visitor(DoubleVisitor(), u2);  // u2 becomes hihi

  std::vector<boost::variant<int, std::string>> vec{1, "hello"};
  vec.push_back(2);
  vec.push_back("hi");
  DoubleVisitor f;
  for (auto v : vec) {
    boost::apply_visitor(f, v);
    std::cout << v << std::endl;
  }
}

int main() {
  example_variant();
  example_lexical_cast();
  example_regex();
}
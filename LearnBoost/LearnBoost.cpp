#include <algorithm>
#include <boost/any.hpp>
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

// data type is checked at compile time.
// So we can use Visitor.
// boost::variant stack based storage.
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

// boost::any can store any type of data and uses dynamic storage.
// boost::variant stack based storage (more efficient in terms of memory
// management).
// type can be checked only at compile type with .type() = typeid ();
void example_any() {
  boost::any x, y, z;
  x = std::string("s");
  x = 2.3;
  y = 'z';
  z = std::vector<int>();
  // std::cout << y << std::endl;// does not work << is not overloaded for any.
  std::cout << boost::any_cast<char>(y) << std::endl;  // returns a copy of 'z'
  std::cout << boost::any_cast<double>(x)
            << std::endl;  // returns a copy of 'z'

  try {
    std::cout << boost::any_cast<float>(x) << std::endl;  // throws bad_any_cast
  } catch (boost::bad_any_cast& e) {
    std::cout << e.what() << std::endl;
  }

  // check type
  if (y.type() == typeid(char)) std::cout << "y is char " << std::endl;

  boost::any empty_any;
  bool is_empty = empty_any.empty();

  /* THIS WILL CRASH
  boost::any_cast<std::vector<int>>(z).push_back(23);
  int i = boost::any_cast<std::vector<int>>(z)
              .back();  // crash. because z still empty. above statement makes a
                        // copy.
  */
  int i = 10;
  boost::any p = &i;
  int* pInt = boost::any_cast<int*>(p);  // returns a pointer
  *pInt = 20;
  std::cout << i << std::endl;

  std::vector<boost::any> m{2, 'a', p, boost::any()};

  struct Property {
    std::string name;
    boost::any value;
  };
  std::vector<Property> properties;
}

int main() {
  example_any();
  example_variant();
  example_lexical_cast();
  example_regex();
}
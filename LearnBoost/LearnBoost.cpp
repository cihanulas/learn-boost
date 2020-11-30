#include <algorithm>
#include <boost/lambda/lambda.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <iostream>
#include <iterator>

void example_lexical_cast() {
  int s = 23;
  std::string str = boost::lexical_cast<std::string>(s);
  str = "asd" + boost::lexical_cast<std::string>(3.14);
  std::cout << "example_lexical_cast: " << str << std::endl;
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

int main() {
  example_lexical_cast();
  example_regex();
}
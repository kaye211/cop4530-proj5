#include <iostream>
#include <string>
#include "hashtable.h"

using namespace std;
using namespace cop4530;


int main() {
  HashTable<string, int> table(101);
  auto t = make_pair("t", 42);
  table.insert(t);
  table.insert(make_pair("wow", 67));
  table.dump();

  std::cout << table.contains("t ") << std::endl;
  std::cout << table.contains("wow") << std::endl;
  std::cout << table.match(t) << std::endl;
  std::cout << table.match(make_pair("wow", 67)) << std::endl;
  std::cout << table.match(make_pair("wow", 64)) << std::endl;

  for (int i = 0; i < 100; i++) {
    table.insert(make_pair("a" + std::to_string(i), i));
  }

  table.dump();

  std::cout << table.remove("wow") << std::endl;
  std::cout << table.remove("a32") << std::endl;
  std::cout << table.remove("b40") <<std::endl;

  table.dump();

  return 0;
}

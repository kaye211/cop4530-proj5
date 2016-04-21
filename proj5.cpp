#include <iostream>
#include "passserver.h"

using namespace std;
using namespace cop4530;

void Menu() {
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

int main() {
  PassServer passServer;

  PassServer::Login login("th13", "ex4mpl3p4ssw0rd");
  passServer.addUser(login);
  passServer.addUser(make_pair("user1", "p4ssw0rd!"));
  passServer.addUser(make_pair("thelms501", "il1k3t0c0d3&"));
  passServer.dump();
  cout << passServer.size() << endl;
  cout << passServer.changePassword(make_pair("th13", "ex4mpl3p4ssw0rd"), "d0ubl3tr0bl3") << endl;
  passServer.dump();
  //Menu();

  return 0;
}

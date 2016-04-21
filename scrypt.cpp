#include <iostream>
#include <utility>
#include <unistd.h>
#include <string>
#include <cstring>
#ifndef __APPLE__
  #include <crypt.h>
#endif

using namespace std;

int main()
{
  pair <string, string> p;
  char salt[] = "$1$########";
  string key = "ex4mpl3p4ssw0rd";

  char * password = new char [100];
  strcpy ( password, crypt(key.c_str(), salt));
  cout << "Plaintext = " << key << endl;
  cout << "Encrypted = " << password << endl;
  delete [] password;
  return 0;
}

/**
* passserver.cpp
*
* COP4530 Project 5
* Author: Trevor Helms
* FSUID: th13
*/

#include <iostream>
#include <unistd.h>
#include <crypt.h>
#include "passserver.h"

using namespace cop4530;

constexpr char PassServer::SALT[];

PassServer::PassServer(std::size_t size) : HashTable(size) {}
PassServer::~PassServer() {}

bool PassServer::find(const Username& user) {
  return contains(user);
}

bool PassServer::addUser(const Login& login) {
  return insert(get_encrypted_login(login));
}

bool PassServer::addUser(Login&& login) {
  return addUser(login);
}

bool PassServer::removeUser(const Username& user) {
  return remove(user);
}

bool PassServer::changePassword(const Login& login, const Password& newpassword) {
  if (match(get_encrypted_login(login))) {
    return insert(get_encrypted_login(make_pair(login.first, newpassword)));
  }

  return false;
}

bool PassServer::load(const char* filename) {
  return HashTable<std::string, std::string>::load(filename);
}

bool PassServer::write_to_file(const char* filename) {
  return HashTable<std::string, std::string>::write_to_file(filename);
}

void PassServer::dump() const {
  HashTable<std::string, std::string>::dump();
}

std::size_t PassServer::size() {
  std::size_t size = 0;

  if (table != nullptr) {
    for (auto list : *table) {
      if (list != nullptr) {
        for (auto item : *list) {
          size++;
        }
      }
    }
  }

  return size;
}

PassServer::EncryptedPassword PassServer::encrypt(const Password& pw) {
  return crypt(pw.c_str(), PassServer::SALT);
}

PassServer::EncryptedLogin PassServer::get_encrypted_login(const Login& login) {
  return make_pair(login.first, encrypt(login.second));
}

/**
* passserver.h
*
* COP4530 Project 5
* Author: Trevor Helms
* FSUID: th13
*/

#ifndef PASSSERVER_H
#define PASSSERVER_H

#include <iostream>
#include <string>
#include <utility>
#include "hashtable.h"

namespace cop4530 {

  class PassServer : private HashTable<std::string, std::string> {
    public:
      typedef std::string Username;
      typedef std::string Password;
      typedef std::string EncryptedPassword;
      typedef std::pair<Username, Password> Login;
      typedef std::pair<Username, EncryptedPassword> EncryptedLogin;

      PassServer(std::size_t size = 101);
      ~PassServer();

      bool find(const Username& user);

      bool addUser(const Login& login);
      bool addUser(Login&& login);
      bool removeUser(const Username& user);
      bool changePassword(const Login& login, const Password& newpassword);

      bool load(const char* filename);
      bool write_to_file(const char* filename);
      void dump() const;

      std::size_t size();

    private:
      static constexpr char SALT[] = "$1$########";

      EncryptedPassword encrypt(const Password& pw);
      EncryptedLogin get_encrypted_login(const Login& login);
  };

}

#endif

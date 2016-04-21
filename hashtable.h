/**
* hashtable.h
*
* COP4530 Project 5
* Author: Trevor Helms
* FSUID: th13
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <list>
#include <utility>
#include <vector>

namespace cop4530 {

  template<typename K, typename V>
  class HashTable {
    public:
      typedef std::pair<K, V> KeyVal;

      explicit HashTable(std::size_t size = 101);
      ~HashTable();

      bool contains(const K &k) const;
      bool match(const KeyVal& kv) const;

      bool insert(const KeyVal& kv);
      bool insert(KeyVal&& kv);
      bool remove(const K& k);
      void clear();

      bool load(const char* filename);
      void dump() const;
      bool write_to_file(const char* filename);

      std::size_t myhash(const K& k) const;

    protected:
      // max_prime is used by the helpful functions provided to you.
      static const unsigned int max_prime = 1301081;

      // the default_capacity is used if the initial capacity of the underlying
      // vector of the hash table is zero.
      static const unsigned int default_capacity = 11;

      std::vector<std::list<KeyVal>*>* table;

    private:
      void make_empty();
      void rehash();

      unsigned long prime_below(unsigned long);
      void set_primes(std::vector<unsigned long>&);

  };

  #include "hashtable.hpp"

}

#endif

/**
* hashtable.hpp
*
* COP4530 Project 5
* Author: Trevor Helms
* FSUID: th13
*/

#include <iostream>

using namespace cop4530;


template<typename K, typename V>
HashTable<K, V>::HashTable(std::size_t size) {
  if (size <= 0)
    size = default_capacity;

  this->table = new std::vector<std::list<KeyVal>*>(prime_below(size), nullptr);
}

template<typename K, typename V>
HashTable<K, V>::~HashTable() {
  make_empty();
  delete table;
}

template<typename K, typename V>
bool HashTable<K, V>::contains(const K &k) const {
  std::size_t index = myhash(k);

  if (table->at(index) == nullptr)
    return false;

  for (auto item : *table->at(index))
    if (k == item.first)
      return true;

  return false;
}

template<typename K, typename V>
bool HashTable<K, V>::match(const KeyVal& kv) const {
  std::size_t index;

  if (contains(kv.first)) {
    index = myhash(kv.first);
  }
  else {
    return false;
  }

  for (auto item : *table->at(index)) {
    if (item.second == kv.second) {
      return true;
    }
  }

  return false;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(const KeyVal& kv) {
  std::size_t index = myhash(kv.first);

  if (table->at(index) == nullptr) {
    table->at(index) = new std::list<KeyVal>;
  }

  if (match(kv)) {
    return false;
  }

  if (contains(kv.first)) {
    auto itr = table->at(index)->begin();
    for (; itr != table->at(index)->end(); itr++) {
      if (itr->first == kv.first) {
        itr->second = kv.second;
        return true;
      }
    }

  }

  table->at(index)->push_back(kv);
  return true;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(KeyVal&& kv) {
  insert(kv);
  return true;
}

template<typename K, typename V>
bool HashTable<K, V>::remove(const K& k) {
  if (contains(k)) {
    std::size_t index = myhash(k);

    for (auto itr = table->at(index)->begin(); itr != table->at(index)->end(); itr++) {
      if (itr->first == k) {
        table->at(index)->erase(itr);
        return true;
      }
    }
  }

  return false;
}

template<typename K, typename V>
void HashTable<K, V>::clear() {
  make_empty();
}

template<typename K, typename V>
bool HashTable<K, V>::load(const char* filename) {
  return true;
}

template<typename K, typename V>
void HashTable<K, V>::dump() const {
  int i = 0;
  for (auto list : *table) {
    std::cout << "v[" << i << "]: ";

    if (list != nullptr) {
      for (auto item : *list) {
        if (list->front().first != item.first) {
          std::cout << ":";
        }
        std::cout << item.first << " " << item.second;
      }
    }

    std::cout << std::endl;
    i++;
  }
}

template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char* filename){
  return true;
}

template<typename K, typename V>
void HashTable<K, V>::make_empty() {
  if (table == nullptr)
    return;

  for (auto list : *table) {
    if (list == nullptr)
      return;

    delete list;
  }
}

template<typename K, typename V>
std::size_t HashTable<K, V>::myhash(const K& k) const {
  static std::hash<K> make_hash;
  return make_hash(k) % table->size();
}


// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template<typename K, typename V>
unsigned long HashTable<K, V>::prime_below(unsigned long n) {
  if (n > max_prime) {
    std::cerr << "** input too large for prime_below()\n";
    return 0;
  }
  if (n == max_prime) {
    return max_prime;
  }
  if (n <= 1) {
    std::cerr << "** input too small \n";
    return 0;
  }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  set_primes(v);
  while (n > 2) {
    if (v[n] == 1)
      return n;
    --n;
  }

  return 2;
}

// Sets all prime number indexes to 1. Called by method prime_below(n)
template<typename K, typename V>
void HashTable<K, V>::set_primes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i) {
    if (vprimes[i] == 1)
      for(j = i + i ; j < n; j += i)
        vprimes[j] = 0;
  }
}

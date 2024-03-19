#pragma once

#include "tree.h"
#include <iostream>

template <typename T> class EntryTable {
protected:
  List<T *> items;

public:
  EntryTable() { items = new std::vector<T *>(0); }
  T *add(T item) {
    const int n = items->size();
    for (int i = 0; i < n; i++) {
      T *p = items->at(i);
      if (*p == item)
        return p;
    }
    T *p = new T(item);
    items->push_back(p);
    return p;
  }
  void clear() {
    items->clear();
  }
};

using StringTable = EntryTable<std::string>;
using IntTable = EntryTable<std::string>;
using IdTable = EntryTable<std::string>;
extern StringTable stringtable;
extern IntTable inttable;
extern IdTable idtable;

template <typename K, typename V> class SymbolTable {
protected:
  List<List<std::pair<K, V>>> itemsList;

public:
  SymbolTable() {
    itemsList = new std::vector<List<std::pair<K, V>>>(0);
  }
  void enterScope() {
    List<std::pair<K, V>> newItems = new std::vector<std::pair<K, V>>(0);
    itemsList->push_back(newItems);
  }
  void exitScope() { itemsList->pop_back(); }
  V lookup(K item) {
    int n = itemsList->size();
    // start with the deepest nesting
    for (int i = n - 1; i >= 0; i--) {
      List<std::pair<K, V>> items = itemsList->at(i);
      int m = items->size();
      for (int j = 0; j < m; j++) {
        std::pair<K, V> current = items->at(j);
        if (current.first == item) {
          return current.second;
        }
      }
    }
    return nullptr;
  }
  V lookupFromCurrentScope(K item) {
    if (itemsList->size() == 0)
      return nullptr;
    List<std::pair<K, V>> items = itemsList->back();
    for (int j = 0; j < items->size(); j++) {
      std::pair<K, V> current = items->at(j);
      if (current.first == item) {
        return current.second;
      }
    }
    return nullptr;
  }
  bool addid(K key, V value) {
    if (itemsList->size() == 0) {
      return false;
    }
    List<std::pair<K, V>> currentScpoe = itemsList->back();
    currentScpoe->push_back({key, value});
    return true;
  }
  void clear() {
    itemsList->clear();
  }
};
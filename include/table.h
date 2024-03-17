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
};

using StringTable = EntryTable<std::string>;
using IntTable = EntryTable<std::string>;
using IdTable = EntryTable<std::string>;
extern StringTable stringtable;
extern IntTable inttable;
extern IdTable idtable;

template <typename T> class SymbolTable {
protected:
  List<List<T *>> itemsList;

public:
  void enterScope() {
    List<T *> newItems = new std::vector<T *>(0);
    itemsList->push_back(newItems);
  }
  void exitScope() {
    if (itemsList->size() == 0) {
      std::cerr << "can not exitScope without scope" << std::endl;
      return;
    }
    itemsList->pop_back();
  }
  T *lookup(T item) {
    int n = itemsList->size();
    // start with the deepest nesting
    for (int i = n - 1; i >= 0; i--) {
      List<T *> items = itemsList->at(i);
      int m = items->size();
      for (int j = 0; j < m; j++) {
        T *current = items->at(j);
        if (*current == item) {
          return current;
        }
      }
    }
    return nullptr;
  }
};
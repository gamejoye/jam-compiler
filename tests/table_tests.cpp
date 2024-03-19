#include <cstdio>
#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include "table.h"

TEST(TableTest1, 1) {
  SymbolTable<std::string, Symbol> tb;
  tb.enterScope();
  tb.addid("name", new std::string("gamejoye"));
  ASSERT_EQ(*tb.lookup("name"), "gamejoye");
  ASSERT_EQ(*tb.lookupFromCurrentScope("name"), "gamejoye");
  tb.enterScope();
  tb.addid("age", new std::string("20"));
  ASSERT_EQ(*tb.lookup("age"), "20");
  ASSERT_EQ(*tb.lookupFromCurrentScope("age"), "20");
  ASSERT_EQ(*tb.lookup("name"), "gamejoye");
  ASSERT_EQ(tb.lookupFromCurrentScope("name"), nullptr);
  tb.exitScope();
  ASSERT_EQ(tb.lookup("age"), nullptr);
  ASSERT_EQ(*tb.lookup("name"), "gamejoye");
  ASSERT_EQ(*tb.lookupFromCurrentScope("name"), "gamejoye");
}
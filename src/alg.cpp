// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"

void collect(const PMNode* node, std::vector<char>& cur, std::vector<std::vector<char>>& res) {
  if (node->value != '\0') cur.push_back(node->value);
  if (node->children.empty()) {
    if (!cur.empty()) res.push_back(cur);
  } else {
    for (auto& c : node->children) collect(c.get(), cur, res);
  }
  if (node->value != '\0') cur.pop_back();
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> res;
  std::vector<char> cur;
  collect(tree.getRoot(), cur, res);
  return res;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  auto all = getAllPerms(tree);
  if (num < 1 || num > (int)all.size()) return {};
  return all[num - 1];
}

bool find(const PMNode* node, int& num, std::vector<char>& cur, std::vector<char>& res) {
  if (node->value != '\0') cur.push_back(node->value);
  if (node->children.empty()) {
    if (--num == 0) { res = cur; cur.pop_back(); return true; }
  } else {
    for (auto& c : node->children)
      if (find(c.get(), num, cur, res)) { cur.pop_back(); return true; }
  }
  if (node->value != '\0') cur.pop_back();
  return false;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  if (num < 1) return {};
  std::vector<char> cur, res;
  int n = num;
  find(tree.getRoot(), n, cur, res);
  return res;
}

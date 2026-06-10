// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

struct PMNode {
  char value;
  std::vector<std::unique_ptr<PMNode>> children;
  PMNode(char val) : value(val) {}
};

class PMTree {
  std::unique_ptr<PMNode> root;

  void build(PMNode* node, const std::vector<char>& rem) {
    if (rem.empty()) return;
    for (char c : rem) {
      auto child = std::make_unique<PMNode>(c);
      std::vector<char> next;
      for (char r : rem)
        if (r != c) next.push_back(r);
      build(child.get(), next);
      node->children.push_back(std::move(child));
    }
  }

public:
  PMTree(const std::vector<char>& in) {
    root = std::make_unique<PMNode>('\0');
    build(root.get(), in);
  }
  const PMNode* getRoot() const { return root.get(); }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_

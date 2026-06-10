// Copyright 2022 NNTU-CS
#include <vector>
#include <fstream>
#include <chrono>
#include "tree.h"

int main() {
  std::ofstream out("result/times.csv");
  out << "n,getAllPerms,getPerm1,getPerm2\n";

  for (int n = 3; n <= 9; ++n) {
    std::vector<char> in;
    for (int i = 0; i < n; ++i) in.push_back('a' + i);
    PMTree tree(in);

    auto t0 = std::chrono::high_resolution_clock::now();
    auto p = getAllPerms(tree);
    auto t1 = std::chrono::high_resolution_clock::now();
    getPerm1(tree, static_cast<int>(p.size()) / 2);
    auto t2 = std::chrono::high_resolution_clock::now();
    getPerm2(tree, static_cast<int>(p.size()) / 2);
    auto t3 = std::chrono::high_resolution_clock::now();

    using ms = std::chrono::duration<double, std::milli>;
    out << n << ","
        << ms(t1 - t0).count() << ","
        << ms(t2 - t1).count() << ","
        << ms(t3 - t2).count() << "\n";
  }

  out.close();
  return 0;
}

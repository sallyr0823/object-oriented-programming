#include <iostream>

#include "dna_strand.hpp"
using std::cout;
using std::endl;

void printList(DNAstrand& list) {
  Node<char>* curr = list.head_;
  while (curr != nullptr) {
    cout << curr->data << "->";
    curr = curr->next;
  }
  cout << endl;
}

int main(int agrc, char** args) {
  const char* str1 = "tgatc";
  DNAstrand to_splice(str1);
  // to_splice.printList();
  const char* str2 = "atq";
  DNAstrand target(args[1]);
  // target.printList();
  const char* pattern = args[2];
  DNAstrand t2(args[3]);
  target.SpliceIn(pattern, t2);
  printList(target);
  // to_splice.printList();
  return 0;
}
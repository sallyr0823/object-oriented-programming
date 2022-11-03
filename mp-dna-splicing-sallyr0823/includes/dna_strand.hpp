#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand();
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();
  DNAstrand(const char* input);
  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  // Node<char>* helper(Node<char>* curr, int idx, const char* pattern, int
  // len);

  // private:
  Node<char>* head_;
  Node<char>* tail_;
};

#endif
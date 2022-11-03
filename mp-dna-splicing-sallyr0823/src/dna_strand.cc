#include "dna_strand.hpp"

#include <stdexcept>

DNAstrand::DNAstrand() {
  head_ = nullptr;
  tail_ = nullptr;
}
DNAstrand::~DNAstrand() {
  if (head_ == nullptr) return;
  Node* curr = head_;
  while (curr != tail_) {
    Node* next = curr->next;
    delete curr;
    curr = next;
  }
  delete tail_;
  head_ = nullptr;
  tail_ = nullptr;
}


void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (pattern[0] == '\0' || to_splice_in.head_ == nullptr)
      return;
    
  size_t length = 0,index = 0;
  while (pattern[length] != '\0') length++;
  Node* current = head_, *tmp = nullptr, *target_head = nullptr;
  while (current != nullptr) {
    if (current->data == pattern[index]) {
      tmp = current;
      while (index < length && current != nullptr) {
        if (pattern[index] == current->data) {
          current = current->next;
          index++;
        } else {
          break;
        }
      }
      if (index == length) {
        target_head = tmp;
      }
      current = tmp->next;
      index = 0;
    } else {
      current = current->next;
    }
  }

  if (target_head == nullptr) throw std::invalid_argument("Pattern not found");
  // find the prev of target
  Node*curr = head_, *prev = nullptr;
  if (target_head != head_) {
    while (curr != target_head) {
      prev = curr;
      curr = curr->next;
    }
  }

  // find the tail of the pattern
  size_t count = 0;
  curr = target_head;
  Node* temp = nullptr;
  while (count != length) {
    temp = curr->next;
    delete curr;
    curr = temp;
    count++;
  }

  if (to_splice_in.head_ != nullptr) {
    if (prev == nullptr)
      head_ = to_splice_in.head_;
    else
      prev->next = to_splice_in.head_;
    to_splice_in.tail_->next = curr;
    if (curr == nullptr) tail_ = to_splice_in.tail_;
  } else {
    if (prev != nullptr)
      prev->next = curr;
    else
      head_ = curr;
    if (curr == nullptr) tail_ = prev;
  }

  to_splice_in.head_ = nullptr;
  to_splice_in.tail_ = nullptr;
}


#include "circular-linked-list.hpp"

#include <cassert>
#include <iostream>
#include <vector>

using std::endl;

std::ostream& operator<<(std::ostream& os, const CircularLinkedList& cll) {
  // do something
  os << "a circular linked list:" << endl;
  Node* curr = cll.head_;
  while (curr != cll.tail_) {
    os << curr->data << " -> ";
    curr = curr->next;
  }
  if (cll.tail_ == nullptr)
    os << "empty list" << endl;
  else
    os << cll.tail_->data << endl;
  return os;
}

void CircularLinkedList::clear() {
  Node *curr = head_, *next = curr == nullptr ? nullptr : curr->next;
  if (head_ == nullptr) return;
  if (head_ == tail_) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
    return;
  }
  while (curr != tail_) {
    delete curr;
    curr = next;
    next = next == nullptr ? nullptr : next->next;
  }
  delete tail_;
  head_ = nullptr;
  tail_ = nullptr;
}

void CircularLinkedList::copy(const CircularLinkedList& source) {
  node_order_ = source.node_order_;
  Node *prev = nullptr, *curr = source.head_;
  if (curr == nullptr) {
    // empty list
    head_ = nullptr;
    tail_ = nullptr;
    return;
  }
  while (curr != source.tail_) {
    Node* newNode = new Node(curr->data);
    if (prev != nullptr)
      prev->next = newNode;
    else
      head_ = newNode;
    prev = newNode;
    curr = curr->next;
  }
  Node* newNode = new Node(curr->data);
  if (prev != nullptr) {
    prev->next = newNode;
    newNode->next = head_;
    tail_ = newNode;
  } else {
    head_ = newNode;
    tail_ = newNode;
    tail_->next = head_;
  }
}

void CircularLinkedList::Reverse() {
  if (head_ == nullptr || head_ == tail_) {
    node_order_ = (node_order_ == Order::kASC ? Order::kDESC : Order::kASC);
    return;
  }
  Node *curr = head_, *next = curr->next, *prev = nullptr;
  while (curr != tail_) {
    if (prev == nullptr) {
      curr->next = tail_;
    } else {
      curr->next = prev;
    }
    prev = curr;
    curr = next;
    next = next->next;
  }
  curr->next = prev;
  Node* tmp = head_;
  head_ = tail_;
  tail_ = tmp;
  node_order_ = (node_order_ == Order::kASC ? Order::kDESC : Order::kASC);
}

void CircularLinkedList::InsertInOrder(int data) {
  // std::cout << "inserting: " << data << endl;
  Node *prev = nullptr, *curr = head_;
  Node* newNode = new Node(data, nullptr);
  if (head_ == nullptr) {
    head_ = newNode;
    tail_ = newNode;
    newNode->next = head_;
    return;
  }
  // find where to insert
  if (node_order_ == Order::kASC) {
    while (prev != tail_ && data >= curr->data) {
      prev = curr;
      curr = curr->next;
    }
  } else {
    while (prev != tail_ && data <= curr->data) {
      prev = curr;
      curr = curr->next;
    }
  }
  // insert after prev
  if (prev == nullptr) {
    head_ = newNode;
    newNode->next = curr;
    tail_->next = newNode;
  } else {
    newNode->next = prev->next;
    prev->next = newNode;
    if (prev == tail_) tail_ = newNode;
  }
}

CircularLinkedList::CircularLinkedList() {
  head_ = nullptr;
  tail_ = nullptr;
  node_order_ = Order::kASC;
}
CircularLinkedList::CircularLinkedList(const CircularLinkedList& source) {
  copy(source);
}

CircularLinkedList& CircularLinkedList::operator=(
    const CircularLinkedList& source) {
  if (this == &source) return *this;
  clear();
  copy(source);
  return *this;
}

CircularLinkedList::~CircularLinkedList() { clear(); }
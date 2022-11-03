#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct Node {
  T data;         // NOLINT
  Node<T>* next;  // NOLINT
  Node(T data): data(data), next(nullptr) {}
  Node(T data, Node<T>* next): data(data), next(next) {}
};

#endif
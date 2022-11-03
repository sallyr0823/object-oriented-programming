#include "branched-linked-list.hpp"

#include <iostream>
using std::cout;
using std::endl;

// your implementation here

Node* BLL::PushBack(char dat) {
  // cout << "pushing back: " << dat << endl;
  Node* new_node = new Node(dat);
  Node* curr = head_;
  if (curr == nullptr) {
    // cout << "inserting head: " << dat << endl;
    head_ = new_node;
    return new_node;
  }
  while (curr->next_node_ != nullptr) {
    curr = curr->next_node_;
  }
  curr->next_node_ = new_node;
  // cout << "prev: " << curr->data_ << " now we insert: " << new_node->data_
  //<< endl;
  return new_node;
}

char BLL::GetAt(size_t idx) const {
  size_t count = 0;
  if (idx >= Size()) throw std::invalid_argument("Invalid Index!");
  Node* curr = head_;
  while (count != idx) {
    count++;
    if (curr->next_bll_ != nullptr) {
      size_t remaining = idx - count, next_bll_len = curr->next_bll_->Size();
      if (next_bll_len <= remaining) {
        count += next_bll_len;
      } else {
        return curr->next_bll_->GetAt(remaining);
      }
    }
    curr = curr->next_node_;
  }
  return curr->data_;
}
void BLL::SetAt(size_t idx, char dat) {
  size_t count = 0;
  if (idx >= Size()) throw std::invalid_argument("Invalid Index!");
  Node* curr = head_;
  while (count != idx) {
    count++;
    if (curr->next_bll_ != nullptr) {
      size_t remaining = idx - count, next_bll_len = curr->next_bll_->Size();
      if (next_bll_len <= remaining) {
        count += next_bll_len;
      } else {
        curr->next_bll_->SetAt(remaining, dat);
        return;
      }
    }
    curr = curr->next_node_;
  }
  curr->data_ = dat;
}
void BLL::Join(size_t idx, BLL* list) {
  // TODO: check if cyclic
  size_t count = 0;
  if (idx >= Size()) throw std::invalid_argument("Invalid Index!");
  Node* curr = head_;
  while (count != idx) {
    count++;
    if (curr->next_bll_ != nullptr) {
      size_t remaining = idx - count, next_bll_len = curr->next_bll_->Size();
      if (next_bll_len <= remaining) {
        count += next_bll_len;
      } else {
        curr->next_bll_->Join(remaining, list);
        return;
      }
    }
    curr = curr->next_node_;
  }
  curr->next_bll_ = list;
}
cs128::string BLL::ToString() const {
  cs128::string res;
  Node* curr = head_;
  while (curr != nullptr) {
    res += curr->data_;
    if (curr->next_bll_ != nullptr) res += curr->next_bll_->ToString();
    curr = curr->next_node_;
  }
  return res;
}
size_t BLL::Size() const {
  size_t res = 0;
  if (head_ == nullptr) return 0;
  Node* curr = head_;
  while (curr != nullptr) {
    res++;
    if (curr->next_bll_ != nullptr) res += curr->next_bll_->Size();
    curr = curr->next_node_;
  }
  return res;
}
bool BLL::IsBLLAcyclic() const {
  if(head_==nullptr) return true;
  size_t t_count=0,h_count=1;
  Node* tortoise=CycleHelper(t_count),*hare=CycleHelper(h_count);
  while (tortoise!=nullptr && hare!=nullptr){
    if(tortoise==hare) return false;
    t_count++;
    h_count+=2;
    tortoise=CycleHelper(t_count);
    hare=CycleHelper(h_count);
  }
  return true;
}

Node*& BLL::CycleHelper(size_t idx) const {
  size_t count = 0;
  Node* curr = head_;
  while (count != idx) {
    count++;
    if (curr->next_bll_ != nullptr) {
      size_t remaining = idx - count, next_bll_len = curr->next_bll_->Size();
      if (next_bll_len <= remaining) {
        count += next_bll_len;
      } else {
        return curr->next_bll_->CycleHelper(remaining);
      }
    }
    curr = curr->next_node_;
  }
  return curr;
}

// helper function
// dest=deepCopy(to_copy)
void BLL::CopyHelper(BLL& dest, const BLL& to_copy) {
  // cout << "yes, am here" << endl;
  Node *prev = nullptr, *curr = to_copy.head_;
  if (curr == nullptr)
    dest.head_ = nullptr;
  else {
    // dest.head_=nullptr

    while (curr != nullptr) {
      Node* new_node = new Node(curr->data_);

      if (curr->next_bll_ != nullptr) {
        BLL* new_bll = new BLL();
        CopyHelper(*new_bll, *curr->next_bll_);
        new_node->next_bll_ = new_bll;
      }
      if (dest.head_ == nullptr)
        dest.head_ = new_node;
      else
        prev->next_node_ = new_node;
      prev = new_node;
      curr = curr->next_node_;
    }
  }
}

void BLL::Copy(const BLL& to_copy) {
  if (to_copy.head_ == nullptr) {
    head_ = nullptr;
    // cout << "yes, am here" << endl;
    return;
  }
  CopyHelper(*this, to_copy);
}

void BLL::Clear() {  // ClearHelper(*this);
  Node* curr = head_;
  // cout << "deleting: " << endl;
  while (curr != nullptr) {
    // cout << "now delete: " << curr->data_ << endl;
    if (curr->next_bll_ != nullptr) delete (curr->next_bll_);
    Node* next = curr->next_node_;
    delete curr;
    curr = nullptr;
    curr = next;
  }
}

BLL::BLL() { head_ = nullptr; }

BLL::BLL(const BLL& to_copy) { Copy(to_copy); }
BLL::~BLL() { Clear(); }

BLL& BLL::operator=(const BLL& rhs) {
  if (&rhs == this) return *this;

  Clear();
  Copy(rhs);
  return *this;
}
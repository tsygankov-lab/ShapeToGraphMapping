#pragma once
#pragma once

#ifndef STACKVEC
#define STACKVEC
#include <array>
#include <vector>
// This may be better served by implementing something like short_alloc, but
// this will in part be a programming exercise.  The goal is to create a vector
// container which stores N elements 'on the stack,' meaning it will only
// allocate more memory on the heap when this overflows.

// To be implemented...
// insert (range)
// assign
// pop_back
// clear
// emplace (back)
// sweap
namespace vorContainer {
enum CONTAINER_STATE { _STACK, _HEAP };

template <typename T, std::size_t numElem>
struct buffered_vec {
  std::array<T, numElem> conStack;
  std::vector<T> conHeap;
  CONTAINER_STATE _STATE;

  class iterator : public std::iterator<std::random_access_iterator_tag, T> {
   public:
    T* p_;

    iterator() : p_(nullptr){};
    iterator(T* Tptr) : p_(Tptr){};
    iterator(const iterator& other) : p_(other.p_){};
    const iterator& operator=(const iterator& other_it) {
      p_ = other_it.p_;
      return *this;
    }

    T& operator*() { return *p_; }
    T* operator->() { return p_; }
    bool operator==(const iterator& oth) const { return p_ == oth.p_; }
    bool operator!=(const iterator& oth) const { return p_ != oth.p_; }
    bool operator<(const iterator& oth) const { return p_ < oth.p_; }
    bool operator>(const iterator& oth) const { return p_ > oth.p_; }
    bool operator<=(const iterator& oth) const { return p_ <= oth.p_; }
    bool operator>=(const iterator& oth) const { return p_ >= oth.p_; }

    iterator& operator++() {
      ++p_;
      return *this;
    }
    iterator& operator--() {
      --p_;
      return *this;
    }

    iterator operator-(const iterator& oth) const {
      return iterator(p_ - oth.p_);
    }
    iterator operator+(const iterator& oth) const {
      return iterator(p_ + oth.p_);
    }
    iterator operator-(T* off) const { return iterator(p_ - off); }
    iterator operator+(T* off) const { return iterator(p_ + off); }

    iterator operator+(std::size_t off) const { return iterator(p_ + off); }

    iterator operator-(std::size_t off) const { return iterator(p_ - off); }
  };

  buffered_vec() : _STATE(_STACK), stackSize(0){};

  bool onStack() { return _STATE == _STACK; }

  // If we are still in the buffer region, reset the head to the start of the
  // buffer.  Else clear the vector.  Memory has already been allocated to the
  // vector, so there is no need to return to the buffer.
  void clear() {
    if (onStack()) {
      stackSize = 0;
    } else {
      conHeap.clear();
    }
  }

  // This is the same as clear but also sets the vector to it's stack state.
  void reset() {
    stackSize = 0;
    conHeap.clear();
    _STATE = _STACK;
  }

  iterator erase(iterator pos) {
    auto testIterErase = conHeap.begin();
    if (onStack()) {
      iterator p_;
      for (p_ = pos; p_ < this->end() - 1; ++p_) {
        *p_ = *(p_ + 1);
      }
      *p_ = T();
      stackSize--;
      return pos;
    } else {
      auto offset = pos.p_ - &conHeap[0];
      conHeap.erase(conHeap.begin() + 1);
      return iterator(&conHeap[offset]);
    }
  }

  T& operator[](std::size_t n) {
    if (onStack()) {
      return conStack[n];
    } else {
      return conHeap[n];
    }
  }

  // Performs bound checks
  T& at(std::size_t n) {
    if (onStack()) {
      return conStack.at(n);
    } else {
      return conHeap.at(n);
    }
  }

  T& front() { return this[0]; }

  std::size_t size() {
    if (onStack()) {
      return stackSize;
    } else {
      return conHeap.size();
    }
  }

  // As with vector, this is undefined on an empty container.
  T& back() { return this[this->size() - 1]; }

  T* data() {
    if (onStack()) {
      return conStack->data();
    } else {
      return conHeap->data();
    }
  }

  void pushStack(const T& obj) {
    if (onStack()) {
      if (stackSize < numElem) {
        conStack[stackSize++] = obj;
      } else {
        // conHeap.reserve(numElem + 1);
        auto testIter = conHeap.begin();

        std::move(conStack.begin(), conStack.end(),
                  std::back_inserter(conHeap));
        testIter = conHeap.begin();
        conHeap.push_back(obj);
        _STATE = _HEAP;
      }
    }
  }

  void push_back(const T& obj) {
    if (_STATE == _HEAP) {
      conHeap.push_back(obj);
    } else {
      pushStack(obj);
    }
  }

  iterator insert(const iterator& pos, const T& val) {
    if (onStack()) {
      if (stackSize == numElem) {
        auto offset = pos.p_ - &conStack[0];
        conHeap.reserve(numElem + 1);
        std::move(conStack.begin(), conStack.begin() + offset,
                  std::back_inserter(conHeap));
        conHeap.push_back(val);
        std::move(conStack.begin() + offset, conStack.end(),
                  std::back_inserter(conHeap));
        _STATE = _HEAP;
        return iterator(&conHeap[offset]);
      } else {
        auto offset = pos.p_ - &conStack[0];
        for (int i = stackSize; i > offset; --i) {
          conStack[i] = conStack[i - 1];
        }
        conStack[offset] = val;
        stackSize++;
        return iterator(&conStack[offset]);
      }
    } else {
      auto offset = pos.p_ - &conHeap[0];
      conHeap.insert(conHeap.begin() + offset, val);
      return iterator(&conHeap[offset]);
    }
  }

  bool empty() {
    if (onStack()) {
      return stackSize == 0;
    } else {
      return conHeap.empty();
    }
  }

  iterator begin() {
    if (onStack())
      return iterator(&conStack[0]);
    else
      return iterator(&conHeap[0]);
  }

  iterator end() {
    if (onStack()) {
      return iterator((&conStack[0] + stackSize));
    } else {
      return iterator(&conHeap[0] + conHeap.size());
    }
  }

 private:
  std::size_t stackSize;
};
}  // namespace vorContainer

#endif

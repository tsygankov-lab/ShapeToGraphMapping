// May want to reconsider the name
// Objects are directly constructed into vectors of block size
#pragma once
#ifndef VCONTAINER
#define VCONTAINER

#include <memory>
#include <stack>
#include <vector>

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

#ifdef _GCC_49_COMP
namespace std {
template <class T>
struct _Unique_if {
  typedef unique_ptr<T> _Single_object;
};

template <class T>
struct _Unique_if<T[]> {
  typedef unique_ptr<T[]> _Unknown_bound;
};

template <class T, size_t N>
struct _Unique_if<T[N]> {
  typedef void _Known_bound;
};

template <class T, class... Args>
typename _Unique_if<T>::_Single_object make_unique(Args &&... args) {
  return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
typename _Unique_if<T>::_Unknown_bound make_unique(size_t n) {
  typedef typename remove_extent<T>::type U;
  return unique_ptr<T>(new U[n]());
}

template <class T, class... Args>
typename _Unique_if<T>::_Known_bound make_unique(Args &&...) = delete;
}  // namespace std
#endif

namespace vorContainer {
template <class T, class A = std::allocator<T>>
class vectorPageAllocator {
 public:
  int blockSize;
  int lastSpot;
  int numElements;
  int numVec;
  std::vector<std::unique_ptr<std::vector<T>>> collector;
  std::stack<typename std::vector<T>::size_type> recycleInd;

  // typedef A allocator_type;
  // typedef typename std::allocator_traits<A>::value_type value_type;
  // typedef typename std::allocator_traits<A>::reference reference;
  // typedef typename std::allocator_traits<A>::const_reference const_reference;
  // typedef typename std::allocator_traits<A>::difference_type difference_type;
  // typedef typename std::allocator_traits<A>::size_type size_type;

  vectorPageAllocator()
      : blockSize(128), lastSpot(-1), numElements(0), numVec(0){};
  // vectorPageAllocator(const vectorPageAllocator& oth) = delete;
  vectorPageAllocator(const vectorPageAllocator &other) {
    this->blockSize = other.blockSize;
    this->lastSpot = other.lastSpot;
    this->numElements = other.numElements;
    this->numVec = other.numVec;
    this->recycleInd = other.recycleInd;

    if (numElements > 0) {
      for (auto &up : other.collector) {
        collector.emplace_back(std::make_unique<std::vector<T>>());
        collector.back()->reserve(blockSize);
        std::copy(up->begin(), up->end(), collector.back()->begin());
      }

      this->setAllPtrIDs();
    }
  };  // cannot be
      // copied

  // Copy constructor only makes since if the collectors are held with
  // make_shared, or
  // if we can copy the individual vectors
  // {
  // Does not check for object pointers...
  //	blockSize = oth.blockSize;
  //	numVec = oth.numVec;
  //	numElements = oth.numElements;
  //	lastSpot = oth.lastSpot;
  //	for (int i = 0; i < numVec; i++) {
  //		collector.emplace_back(std::make_unique<std::vector<T>>());
  //	}
  //	for (int i = 0; i < lastSpot + 1; i++) {
  //		this->get(i) = *oth->get(i);
  //	}
  //}

  vectorPageAllocator(int blockSize)
      : blockSize(blockSize), lastSpot(-1), numElements(0), numVec(1) {
    collector.emplace_back(std::make_unique<std::vector<T>>());
    collector.at(0)->reserve(blockSize);
  }

  template <typename... Ts>
  T *add(Ts &&... args) {
    ++numElements;
    if (recycleInd.empty()) {
      ++lastSpot;
      if (numVec * blockSize <= lastSpot) {
        collector.emplace_back(std::make_unique<std::vector<T>>());
        collector.at(numVec)->reserve(blockSize);
        ++numVec;
        collector.at(numVec - 1)
            ->emplace_back(
                std::forward<Ts>(args)...);  // what the hell am I typing
        collector.at(numVec - 1)->back().setID(lastSpot);
        return &collector.at(numVec - 1)->back();
      } else {
        collector.at(numVec - 1)->emplace_back(std::forward<Ts>(args)...);
        collector.at(numVec - 1)->back().setID(lastSpot);
        return &collector.at(numVec - 1)->back();
      }
    } else {
      auto index = recycleInd.top();
      recycleInd.pop();
      auto vecIndex = index % blockSize;
      auto vecNum = index / blockSize;
      collector.at(vecNum)->at(vecIndex).setNew(std::forward<Ts>(args)...);
      return &collector.at(vecNum)->at(vecIndex);
    }
  }

  T *get(typename std::vector<T>::size_type index) {
    auto vecIndex = index % blockSize;
    auto vecNum = index / blockSize;
    return &collector.at(vecNum)->at(vecIndex);
  }

  T &getRef(typename std::vector<T>::size_type index) {
    auto vecIndex = index % blockSize;
    auto vecNum = index / blockSize;
    return collector.at(vecNum)->at(vecIndex);
  }

  T getCopy(typename std::vector<T>::size_type index) {
    auto vecIndex = index % blockSize;
    auto vecNum = index / blockSize;
    return collector.at(vecNum)->at(vecIndex);
  }

  void remove(typename std::vector<T>::size_type ind) {
    auto obj = get(ind);
    recycleInd.push(obj->getID());
    obj->disable();
    --numElements;
  }

  void remove(T *obj) {
    recycleInd.push(obj->getID());
    obj->disable();
    --numElements;
  }

  std::size_t getCapacity() { return blockSize * numVec; }

  // WARNING - Removing from the container will no longer work
  // after this.  Only use when preparing to move to a new container
  // of fixed size.  If n elements have been removed from the
  // allocator, this sets the last n elements of the list to have the
  // missing IDs of the containers.  ASSUMES THERE ARE MORE ACTIVE OBJECTS
  // THEN REMOVED INDICES (though it may actually still work if that is
  // the case)
  void setIDsToFinalLocation() {
    auto curID = lastSpot;
    while (!recycleInd.empty() && curID > 0) {
      auto nuID = recycleInd.top();
      auto nodeSel = this->get(curID);
      while (!nodeSel->getState() && curID > 0)
        nodeSel = this->get(--curID);  // Iterate until you find an active node
      if (curID > nuID) {
        nodeSel->setID(nuID);
        //	getRef(nuID) = getRef(curID);
      }  // If this will move the node forward in the list,
      recycleInd.pop();
    }
  }

  // Creates a vector and fills it with references to the active elements
  std::vector<T> extractObjVector() {
    std::vector<T> out;
    out.reserve(numElements);
    for (auto &e : *this) {
      out.push_back(e);
    }
    return out;
  }

  std::vector<T *> extractPtrVector() {
    std::vector<T *> out;
    out.reserve(numElements);
    for (auto &e : *this) {
      out.push_back(&e);
    }
    return out;
  }
  // Creates a vector and fills it with references to the active elements
  std::vector<T> extractObjVector_SetIDs() {
    std::vector<T> out;
    out.reserve(numElements);
    auto iter = -1;
    for (auto &e : *this) {
      out.push_back(e);
      e.setID(++iter);
    }
    return out;
  }

  void setAllPtrIDs() {
    for (auto &obj : *this) {
      obj.setPTRIDs();
    }
  }

  void clear() {
    // collector.clear();
    // collector.shrink_to_fit();
    // std::stack<typename std::vector<T>::size_type>().swap(recycleInd);
    // recycleInd.clear(); cleared by assigning indices
  }
  /*Warning, STL below*/
  class iterator {
   public:
    // typedef typename std::allocator_traits<A>::difference_type
    // difference_type;
    // typedef typename std::allocator_traits<A>::value_type value_type;
    // typedef typename std::allocator_traits<A>::reference reference;
    // typedef typename std::allocator_traits<A>::pointer pointer;
    typedef std::random_access_iterator_tag iterator_category;

    vectorPageAllocator &cont_;
    int pos;

    iterator(vectorPageAllocator<T, A> &other) : cont_(other), pos(0){};
    iterator(vectorPageAllocator<T, A> &other, long position)
        : cont_(other), pos(position){};

    // iterator(const iterator&);
    //~iterator();

    iterator &operator=(const iterator &oth){};
    bool operator==(const iterator &oth) const { return pos == oth.pos; };
    bool operator!=(const iterator &oth) const { return !(*this == oth); }
    bool operator<(const iterator &oth) const {
      return pos < oth.pos;
    };  // optional
    bool operator>(const iterator &oth) const {
      return pos > oth.pos;
    };  // optional
    bool operator<=(const iterator &oth) const {
      return pos <= oth.pos;
    };  // optional
    bool operator>=(const iterator &oth) const {
      return pos >= oth.pos;
    };  // optional

    iterator &operator++() {
      while (++pos < cont_.lastSpot + 1 && !cont_.getRef(pos).getState())
        ;
      return *this;
    }
    // iterator operator++(int); //optional
    iterator &operator--() {
      while (--pos > -1 && !cont_.getRef(pos).getState())
        ;
      return *this;
    };  // optional
    // iterator operator--(int); //optional
    // iterator& operator+=(size_type); //optional
    // iterator operator+(size_type) const; //optional
    // friend iterator operator+(size_type, const iterator&); //optional
    // iterator& operator-=(size_type); //optional
    // iterator operator-(size_type) const; //optional
    // difference_type operator-(iterator) const; //optional

    T &operator*() const { return cont_.getRef(pos); };
    T *operator->() const { return cont_.get(pos); }
    T &operator[](std::size_t posAt) const {
      return cont_.getRef(posAt);
    };  // optional
  };
  /*class const_iterator {
  public:
          typedef typename std::allocator_traits<A>::difference_type
  difference_type;
          typedef typename std::allocator_traits<A>::value_type value_type;
          typedef typename const std::allocator_traits<A>::reference reference;
          typedef typename const std::allocator_traits<A>::pointer pointer;
          typedef std::random_access_iterator_tag iterator_category; //or
  another tag

          const_iterator();
          const_iterator(const const_iterator&);
          const_iterator(const iterator&);
          ~const_iterator();

          const_iterator& operator=(const const_iterator&);
          bool operator==(const const_iterator&) const;
          bool operator!=(const const_iterator&) const;
          bool operator<(const const_iterator&) const; //optional
          bool operator>(const const_iterator&) const; //optional
          bool operator<=(const const_iterator&) const; //optional
          bool operator>=(const const_iterator&) const; //optional

          const_iterator& operator++();
          const_iterator operator++(int); //optional
          const_iterator& operator--(); //optional
          const_iterator operator--(int); //optional
          const_iterator& operator+=(size_type); //optional
          const_iterator operator+(size_type) const; //optional
          friend const_iterator operator+(size_type, const const_iterator&);
  //optional
          const_iterator& operator-=(size_type); //optional
          const_iterator operator-(size_type) const; //optional
          difference_type operator-(const_iterator) const; //optional

          reference operator*() const;
          pointer operator->() const;
          reference operator[](size_type) const; //optional
  };*/
  // typedef std::reverse_iterator<iterator> reverse_iterator; //optional
  // typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  // //optional

  iterator begin() {
    auto pos = 0;
    while (pos < lastSpot + 1 && !get(pos)->getState()) pos++;
    return iterator(*this, pos);
  }
  // const_iterator begin() const;
  // const_iterator cbegin() const;
  iterator end() { return iterator(*this, lastSpot + 1); }
  // const_iterator end() const;
  // const_iterator cend() const;

  // reverse_iterator rbegin(); //optional
  // const_reverse_iterator rbegin() const; //optional
  // const_reverse_iterator crbegin() const; //optional
  // reverse_iterator rend(); //optional
  // const_reverse_iterator rend() const; //optional
  // const_reverse_iterator crend() const; //optional
};  // namespace vorContainer
}  // namespace vorContainer
#endif  // !VCONTAINER

#ifndef _CONTAINERS_ARRAY_S21_ARRAY_H
#define _CONTAINERS_ARRAY_S21_ARRAY_H

#include <iterator>

namespace s21 {

namespace __iterator {
template <typename T, std::size_t Size>
class ArrayIterator {
 public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;

  ArrayIterator() : ptr(nullptr) {}
  ArrayIterator(pointer p) : ptr(p) {}

  reference operator*() const { return *ptr; }
  pointer operator->() const { return ptr; }

  ArrayIterator &operator++() {
    ++ptr;
    return *this;
  }
  ArrayIterator operator++(int) {
    ArrayIterator tmp = *this;
    ++ptr;
    return tmp;
  }

  ArrayIterator &operator--() {
    --ptr;
    return *this;
  }
  ArrayIterator operator--(int) {
    ArrayIterator tmp = *this;
    --ptr;
    return tmp;
  }

  ArrayIterator &operator+=(difference_type n) {
    ptr += n;
    return *this;
  }
  ArrayIterator &operator-=(difference_type n) {
    ptr -= n;
    return *this;
  }

  ArrayIterator operator+(difference_type n) const {
    return ArrayIterator(ptr + n);
  }
  ArrayIterator operator-(difference_type n) const {
    return ArrayIterator(ptr - n);
  }

  difference_type operator-(const ArrayIterator &other) const {
    return ptr - other.ptr;
  }

  bool operator==(const ArrayIterator &other) const { return ptr == other.ptr; }
  bool operator!=(const ArrayIterator &other) const { return ptr != other.ptr; }
  bool operator<(const ArrayIterator &other) const { return ptr < other.ptr; }
  bool operator>(const ArrayIterator &other) const { return ptr > other.ptr; }
  bool operator<=(const ArrayIterator &other) const { return ptr <= other.ptr; }
  bool operator>=(const ArrayIterator &other) const { return ptr >= other.ptr; }

 private:
  pointer ptr;
};

template <typename T, std::size_t Size>
class ArrayConstIterator {
 public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = const T &;

  ArrayConstIterator() : ptr(nullptr) {}
  ArrayConstIterator(pointer p) : ptr(p) {}

  reference operator*() const { return *ptr; }
  pointer operator->() const { return ptr; }

  ArrayConstIterator &operator++() {
    ++ptr;
    return *this;
  }
  ArrayConstIterator operator++(int) {
    ArrayConstIterator tmp = *this;
    ++ptr;
    return tmp;
  }

  ArrayConstIterator &operator--() {
    --ptr;
    return *this;
  }
  ArrayConstIterator operator--(int) {
    ArrayConstIterator tmp = *this;
    --ptr;
    return tmp;
  }

  ArrayConstIterator &operator+=(difference_type n) {
    ptr += n;
    return *this;
  }
  ArrayConstIterator &operator-=(difference_type n) {
    ptr -= n;
    return *this;
  }

  ArrayConstIterator operator+(difference_type n) const {
    return ArrayConstIterator(ptr + n);
  }
  ArrayConstIterator operator-(difference_type n) const {
    return ArrayConstIterator(ptr - n);
  }

  difference_type operator-(const ArrayConstIterator &other) const {
    return ptr - other.ptr;
  }

  bool operator==(const ArrayConstIterator &other) const {
    return ptr == other.ptr;
  }
  bool operator!=(const ArrayConstIterator &other) const {
    return ptr != other.ptr;
  }
  bool operator<(const ArrayConstIterator &other) const {
    return ptr < other.ptr;
  }
  bool operator>(const ArrayConstIterator &other) const {
    return ptr > other.ptr;
  }
  bool operator<=(const ArrayConstIterator &other) const {
    return ptr <= other.ptr;
  }
  bool operator>=(const ArrayConstIterator &other) const {
    return ptr >= other.ptr;
  }

 private:
  pointer ptr;
};
}  // namespace __iterator

template <typename T, std::size_t Size>
class array {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = __iterator::ArrayIterator<T, Size>;
  using const_iterator = const __iterator::ArrayConstIterator<T, Size>;
  using size_type = size_t;
  using pointer = T *;
  using const_pointer = const T *;

  array() : _array(nullptr), _size(Size) {}

  array(std::initializer_list<value_type> const &items)
      : _array(new value_type[items.size()]), _size(items.size()) {
    size_type i = 0;
    for (auto begin = items.begin(), end = items.end(); begin != end;
         ++begin, ++i) {
      _array[i] = *begin;
    }
  }

  array(const array &a) : _array(new value_type[a._size]), _size(a._size) {
    for (size_t i = 0; i < _size; ++i) {
      _array[i] = a._array[i];
    }
  };

  array(array &&a) : _array(a._array), _size(a._size) {
    a._array = nullptr;
    a._size = 0;
  }

  ~array() {
    if (_array != nullptr) {
      delete[] _array;
      _array = nullptr;
      _size = 0;
    }
  }

  iterator begin() { return iterator(_array); }
  const_iterator cbegin() const { return const_iterator(_array); }
  iterator end() { return iterator(_array + _size); }
  const_iterator cend() const { return const_iterator(_array + _size); }

  reference at(size_type pos) {
    if (_size <= pos) {
      throw ::std::out_of_range("");
    }
    return *(begin() + pos);
  }

  const_reference at(size_type pos) const {
    if (_size <= pos) {
      throw ::std::out_of_range("");
    }
    return *(cbegin() + pos);
  }

  reference front() { return *begin(); }
  const_reference front() const { return *cbegin(); }
  reference back() { return *(end() - 1); }
  const_reference back() const { return *(cend() - 1); }

  iterator data() { return _array; }

  const iterator data() const { return _array; }

  bool empty() const noexcept { return _size == 0; }

  size_type size() { return _size; }

  size_type max_size() const { return _size; }

  void swap(array &other) {
    std::swap(_size, other._size);
    std::swap(_array, other._array);
  }

  void fill(const_reference value) {
    if (_array == nullptr) {
      _array = new value_type[_size];
    }
    for (size_type i = 0; i < _size; i++) {
      _array[i] = value;
    }
  }

  /* OPERATORS */
  array &operator=(array &&a) {
    if (this != &a) {
      if (_array != nullptr) {
        delete[] _array;
        _array = nullptr;
        _size = 0;
      }
      _size = a._size;
      _array = a._array;
      a._array = nullptr;
      a._size = 0;
    }
    return *this;
  }

  reference operator[](size_type pos) { return *(begin() + pos); }

 private:
  pointer _array;
  size_type _size;
};

}  // namespace s21

#endif  // _CONTAINERS_ARRAY_S21_ARRAY_H

#ifndef _CONTAINERS_QUEUE_S21_QUEUE_H
#define _CONTAINERS_QUEUE_S21_QUEUE_H

#include <initializer_list>
#include <utility>

#include "../../sequence_containers/list/s21_list.h"

namespace s21 {

template <typename T, typename Container = list<T>>
class queue {
 public:
  using container_type = Container;
  using value_type = typename Container::value_type;
  using size_type = typename Container::size_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  queue() : _container() {}

  queue(std::initializer_list<value_type> const& items) : _container(items) {}

  queue(const queue& q) : _container(q._container) {}

  queue(queue&& q) : _container(std::move(q._container)) {}

  queue& operator=(const queue& other) {
    if (this != &other) {
      _container = other._container;
    }
    return *this;
  }

  queue& operator=(queue&& other) noexcept {
    if (this != &other) {
      _container = std::move(other._container);
    }
    return *this;
  }

  ~queue() {}

  reference front() { return _container.front(); }

  const_reference front() const { return _container.front(); }

  reference back() { return _container.back(); }

  const_reference back() const { return _container.back(); }

  bool empty() const { return _container.empty(); }

  size_type size() const { return _container.size(); }

  template <class... Args>
  decltype(auto) emplace(Args&&... args) {
    return _container.emplace_back(std::forward<Args>(args)...);
  }

  void push(const value_type& value) { _container.push_back(value); }

  void push(value_type&& value) { _container.push_back(std::move(value)); }

  void pop() { _container.pop_back(); }

  void swap(queue& other) noexcept(std::is_nothrow_swappable_v<Container>) {
    using std::swap;
    swap(_container, other._container);
  }

  template <class... Args>
  void insert_many_back(Args&&... args) {
    _container.insert_many_back(args...);
  }

 private:
  Container _container;
};

template <class T, class Container>
void swap(queue<T, Container>& lhs,
          queue<T, Container>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
  lhs.swap(rhs);
}

template <class T, class Container>
bool operator==(const queue<T, Container>& lhs,
                const queue<T, Container>& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  auto lhs_copy = lhs;
  auto rhs_copy = rhs;

  while (!lhs_copy.empty() && !rhs_copy.empty()) {
    if (lhs_copy.front() != rhs_copy.front()) {
      return false;
    }
    lhs_copy.pop();
    rhs_copy.pop();
  }

  return true;
}

}  // namespace s21
#endif  // _CONTAINERS_QUEUE_S21_QUEUE_H

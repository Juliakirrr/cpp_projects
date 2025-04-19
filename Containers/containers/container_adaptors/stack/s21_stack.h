#ifndef _CONTAINERS_STACK_S21_STACK_H
#define _CONTAINERS_STACK_S21_STACK_H

#include "../../sequence_containers/list/s21_list.h"

namespace s21 {

template <typename T, typename Container = list<T>>
class stack {
 public:
  using container_type = Container;
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  stack() : _container() {}
  stack(std::initializer_list<value_type> const& items) : _container(items) {}
  stack(const stack& s) : _container(s._container) {}
  stack(stack&& s) : _container(std::move(s._container)) {}

  stack& operator=(const stack& other) {
    if (this != &other) {
      _container = other._container;
    }
    return *this;
  }

  stack& operator=(stack&& other) noexcept {
    if (this != &other) {
      _container = std::move(other._container);
    }
    return *this;
  }

  ~stack() {}

  const_reference top() { return _container.back(); }

  bool empty() const { return _container.empty(); }
  size_type size() const { return _container.size(); }

  void push(const_reference value) { _container.push_back(value); }

  void push(value_type&& value) { _container.push_back(std::move(value)); }

  void pop() { _container.pop_back(); }

  void swap(stack& other) noexcept(std::is_nothrow_swappable_v<Container>) {
    using std::swap;
    swap(_container, other._container);
  }

  template <class... Args>
  void insert_many_back(Args&&... args) {
    _container.insert_many_back(args...);
  }

  template <class... Args>
  decltype(auto) emplace(Args&&... args) {
    return _container.emplace_back(std::forward<Args>(args)...);
  }

 private:
  Container _container;
};

template <class T, class Container>

void swap(stack<T, Container>& lhs,
          stack<T, Container>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
  lhs.swap(rhs);
}

template <class T, class Container>

bool operator==(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  auto lhs_copy = lhs;
  auto rhs_copy = rhs;

  while (!lhs_copy.empty() && !rhs_copy.empty()) {
    if (lhs_copy.top() != rhs_copy.top()) {
      return false;
    }
    lhs_copy.pop();
    rhs_copy.pop();
  }

  return true;
}

}  // namespace s21

#endif  // _CONTAINERS_STACK_S21_STACK_H

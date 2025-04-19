#ifndef _CONTAINERS_MAP_S21_MAP_HPP
#define _CONTAINERS_MAP_S21_MAP_HPP

#include <iostream>
#include <limits>
#include <list>
#include <optional>

#include "../../sequence_containers/list/s21_list.h"
#include "../../sequence_containers/vector/s21_vector.h"

namespace s21 {
namespace detail_map {

enum Color { RED, BLACK };
enum side { left, right, no };

template <typename T>
T createDefault() {
  static_assert(std::is_default_constructible<T>::value,
                "Type must be default constructible");
  return T();
}

struct Node_Base {
  Node_Base* parent;
  Node_Base* left;
  Node_Base* right;
  Color color;

  Node_Base() : parent(this), left(this), right(this), color(BLACK) {}
  Node_Base(Node_Base* a, Node_Base* b, Node_Base* c)
      : parent(a), left(b), right(c), color(BLACK) {}

  virtual ~Node_Base() = default;
};

template <typename Key, typename T>
struct Node : public Node_Base {
  std::pair<Key, T> kv;
  Node(Key key_, T data_) : kv(key_, data_) {}
  Node(std::pair<Key, T> value) : kv(value) {}
};
}  // namespace detail_map

namespace iteratorr {

template <typename Key, typename T>
class MapIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using pointer = std::pair<Key, T>*;
  using reference = std::pair<Key, T>&;
  using Node_ = detail_map::Node<Key, T>;
  using Node_Base = detail_map::Node_Base;

 private:
  Node_Base* ptr_;
  Node_Base* fakenode_;
  Node_Base* Root_;

 public:
  MapIterator() : ptr_(nullptr) {}
  MapIterator(Node_Base* _ptr, Node_Base* FN, Node_Base* Rt)
      : ptr_(_ptr), fakenode_(FN), Root_(Rt) {}

  reference operator*() const noexcept { return static_cast<Node_*>(ptr_)->kv; }

  MapIterator<Key, T>& operator++() {
    ptr_ = next(ptr_);
    return *this;
  }

  MapIterator<Key, T>& operator--() noexcept {
    ptr_ = previous(ptr_);
    return *this;
  }

  friend bool operator==(const MapIterator<Key, T>& __x,
                         const MapIterator<Key, T>& __y) {
    return __x.ptr_ == __y.ptr_;
  }

  friend bool operator!=(const MapIterator<Key, T>& __x,
                         const MapIterator<Key, T>& __y) {
    return __x.ptr_ != __y.ptr_;
  }

  Node_Base* getNode() { return ptr_; };

 private:
  Node_Base* previous(Node_Base* now) {
    if (now->left != fakenode_) {
      if (now->left->right == fakenode_) {
        now = now->left;
      } else if (now->left->right != fakenode_) {
        now = now->left;
        while (now->right != fakenode_) {
          now = now->right;
        }
      }
    } else if (now->left == fakenode_) {
      Node_Base* pre = now;
      now = now->parent;
      while (now->left == pre) {
        pre = now;
        now = now->parent;
      }
    }
    return now;
  }

  Node_Base* next(Node_Base* now) {
    if (now->right != fakenode_) {
      if (now->right->left == fakenode_) {
        now = now->right;
      } else if (now->right->left != fakenode_) {
        now = now->right;
        while (now->left != fakenode_) {
          now = now->left;
        }
      }
    } else if (now != Root_ && now->right == fakenode_) {
      Node_Base* pre = now;
      now = now->parent;

      while (now->right == pre) {
        pre = now;
        now = now->parent;
      }
    }
    return now;
  }
};

template <typename Key, typename T>
class MapConstIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using pointer = const std::pair<Key, T>*;
  using reference = const std::pair<Key, T>&;
  using Node_ = detail_map::Node<Key, T>;
  using Node_Base = detail_map::Node_Base;

 private:
  const Node_Base* ptr_;
  const Node_Base* fakenode_;
  const Node_Base* Root_;

 public:
  MapConstIterator() : ptr_(nullptr) {}

  MapConstIterator(const Node_Base* _ptr, const Node_Base* FN,
                   const Node_Base* Rt)
      : ptr_(_ptr), fakenode_(FN), Root_(Rt) {}

  reference operator*() const noexcept {
    return static_cast<const Node_*>(ptr_)->kv;
  }

  MapConstIterator<Key, T>& operator++() {
    ptr_ = next(ptr_);
    return *this;
  }

  MapConstIterator<Key, T>& operator--() noexcept {
    ptr_ = previous(ptr_);
    return *this;
  }

  friend bool operator==(const MapConstIterator<Key, T>& __x,
                         const MapConstIterator<Key, T>& __y) {
    return __x.ptr_ == __y.ptr_;
  }

  friend bool operator!=(const MapConstIterator<Key, T>& __x,
                         const MapConstIterator<Key, T>& __y) {
    return __x.ptr_ != __y.ptr_;
  }

  const Node_Base* getNode() { return ptr_; };

 private:
  const Node_Base* previous(const Node_Base* now) const {
    if (now->left != fakenode_) {
      if (now->left->right == fakenode_) {
        now = now->left;
      } else if (now->left->right != fakenode_) {
        now = now->left;
        while (now->right != fakenode_) {
          now = now->right;
        }
      }
    } else if (now->left == fakenode_) {
      const Node_Base* pre = now;
      now = now->parent;
      while (now->left == pre) {
        pre = now;
        now = now->parent;
      }
    }
    return now;
  }

  const Node_Base* next(const Node_Base* now) const {
    if (now->right != fakenode_) {
      if (now->right->left == fakenode_) {
        now = now->right;
      } else if (now->right->left != fakenode_) {
        now = now->right;
        while (now->left != fakenode_) {
          now = now->left;
        }
      }
    } else if (now != Root_ && now->right == fakenode_) {
      const Node_Base* pre = now;
      now = now->parent;

      while (now->right == pre) {
        pre = now;
        now = now->parent;
      }
    }
    return now;
  }
};
}  // namespace iteratorr

template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<std::pair<const Key, T>>>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const Key, T>;
  using size_type = size_t;
  using iterator = iteratorr::MapIterator<Key, T>;
  using const_iterator = iteratorr::MapConstIterator<Key, T>;
  using Node_ = detail_map::Node<Key, T>;
  using Node_Base = detail_map::Node_Base;

  using allocator_type = Allocator;
  using Allocator_Traits = std::allocator_traits<Allocator>;
  using node_allocator =
      typename std::allocator_traits<Allocator>::template rebind_alloc<Node_>;
  using NodeAllocatorTraits = std::allocator_traits<node_allocator>;
  using pointer = typename std::allocator_traits<Allocator>::pointer;
  using const_pointer =
      typename std::allocator_traits<Allocator>::const_pointer;
  using reference = value_type&;
  using const_reference =
      const value_type&;  // defines the type of the constant reference

 private:
  size_type size_;
  Node_Base Root_;
  Node_Base fakenode;
  node_allocator _alloc;

 public:
  //-----------------------counstract--------------------//
  map()
      : size_(0),
        Root_(nullptr, &fakenode, &fakenode),
        fakenode(&fakenode, &fakenode, &fakenode) {}

  map(std::initializer_list<value_type> const& items)
      : size_(0),
        Root_(nullptr, &fakenode, &fakenode),
        fakenode(&fakenode, &fakenode, &fakenode) {
    for (auto begin = items.begin(), end = items.end(); begin != end; ++begin) {
      insert(*begin);
    }
  }

  map(const map& m)
      : size_(0),
        Root_(nullptr, &fakenode, &fakenode),
        fakenode(&fakenode, &fakenode, &fakenode) {  // вернуть конст

    for (const_iterator begin = m.begin(); begin != m.end(); ++begin) {
      insert((*begin).first, (*begin).second);
    }
  }

  map(map&& m)
      : size_(0),
        Root_(nullptr, &fakenode, &fakenode),
        fakenode(&fakenode, &fakenode, &fakenode) {  // move
    swap(m);
  }

  ~map() { removeTree(Root_.left); }

  map& operator=(map&& other) {
    if (this != &other) {
      clear();
      swap(other);
    }
    return *this;
  }

  //------------------------methods-----------------------//

  bool empty() { return (size_ == 0) ? true : false; }
  size_type size() { return size_; }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(Node_) / 2;
  }

  std::pair<iterator, bool> insert(const value_type& value) {  // вставка
    std::pair<Node_*, bool> add = paste(Root_.left, value);
    if (add.second == true) {
      size_++;
      if (size_ > 1 && add.first->parent->color == detail_map::RED) {
        action(add.first);
      }
    }
    return std::pair<iterator, bool>(iterator(add.first, &fakenode, &Root_),
                                     add.second);
  }

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    return insert(std::make_pair(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    std::pair<iterator, bool> add =
        insert(std::make_pair(key, obj));  // если там 0 тогда ток меняем
    if (add.second == 0) {
      (*add.first).second = obj;
    }
    return add;
  }

  void swap(map& other) {
    change_list(Root_.left, &fakenode, &other.fakenode);
    change_list(other.Root_.left, &other.fakenode, &fakenode);

    if (Root_.left == &fakenode) {
      Root_.left = &other.fakenode;
    }
    if (other.Root_.left == &other.fakenode) {
      other.Root_.left = &fakenode;
    }

    Node_Base* tmpRr = Root_.left;
    Root_.left = other.Root_.left;
    other.Root_.left = tmpRr;

    size_type ppp = size_;
    size_ = other.size_;
    other.size_ = ppp;

    if (size_ != 0) {
      Root_.left->parent = &Root_;
    }
    if (other.size_ != 0) {
      other.Root_.left->parent = &other.Root_;
    }

    _alloc = std::move(other._alloc);
  }

  void merge(map& other) {
    for (auto i = other.begin(); i != other.end(); ++i) {
      insert_or_assign((*i).first, (*i).second);
    }
  }

  void erase(iterator pos) {
    Node_Base* deleted =
        search(Root_.left, (*pos).first, 1);  // поиск удаляемой вершины

    if (deleted != nullptr) {
      deletion(deleted);
      size_--;
    }
  }

  iterator find(const Key& key) {
    Node_Base* deleted = search(Root_.left, key, 0);  // поиск удаляемой вершины
    return deleted == nullptr ? iterator(&Root_, &fakenode, &Root_)
                              : iterator(deleted, &fakenode, &Root_);
  }

  bool contains(const Key& key) {
    Node_Base* deleted =
        search(sc(Root_.left), key, 0);  // поиск удаляемой вершины
    return deleted == nullptr ? false : true;
  }

  void clear() {
    removeTree(Root_.left);
    size_ = 0;
    Root_.left = Root_.right = fakenode.left = fakenode.right =
        fakenode.parent = &fakenode;
    Root_.parent = nullptr;
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    vector<std::pair<iterator, bool>> result;
    for (const auto& arg : {args...}) {
      result.push_back(insert(arg));
    }
    return result;
  }

  // --------------------------Element access----------------------//

  T& at(const Key& key) {
    Node_Base* aaa = inquiry(Root_.left, key);
    if (aaa == nullptr) {
      throw std::out_of_range("Index out of range!");
    }
    return sc(aaa)->kv.second;
  }

  T& operator[](const Key& key) {
    Node_Base* aaa = inquiry(Root_.left, key);
    if (aaa == nullptr) {
      T defaultValue = detail_map::createDefault<T>();  // Работает
      aaa = sc(((insert(key, defaultValue)).first).getNode());
    }
    return sc(aaa)->kv.second;
  }

  //--------------------------iterators----------------------//
  iterator begin() {
    return iterator(for_begin(Root_.left), &fakenode, &Root_);
  }
  iterator end() { return iterator(&Root_, &fakenode, &Root_); }

  const_iterator begin() const {
    return const_iterator(for_begin(Root_.left), &fakenode, &Root_);
  }
  const_iterator end() const {
    return const_iterator(&Root_, &fakenode, &Root_);
  }
  //---------------------------------------------------------//
 private:
  Node_Base* inquiry(Node_Base* Tree, Key key) {
    Node_Base* result = nullptr;
    if (Tree != &fakenode) {
      if (sc(Tree)->kv.first == key) {
        result = Tree;
      } else if (sc(Tree)->kv.first > key) {
        result = inquiry(Tree->left, key);
      } else if (sc(Tree)->kv.first < key) {
        result = inquiry(Tree->right, key);
      }
    }
    return result;
  }

  void change_list(Node_Base* firstnode, Node_Base* lastnode,
                   Node_Base* newnode) {
    if (firstnode != lastnode) {
      list<Node_Base*> queue;
      queue.push_front(firstnode);
      while (queue.size() != 0) {
        if (queue.front()->left != lastnode) {
          queue.push_back(queue.front()->left);
        }
        if (queue.front()->right != lastnode) {
          queue.push_back(queue.front()->right);
        }
        if (queue.front()->right == lastnode) {
          queue.front()->right = newnode;
        }
        if (queue.front()->left == lastnode) {
          queue.front()->left = newnode;
        }
        queue.pop_front();
      }
    }
  }

  void deletion(Node_Base* deleted) {
    if (deleted->left == &fakenode &&
        deleted->right == &fakenode) {  // детей нет
      if (deleted == Root_.left) {
        cleaning(sc(deleted));
        Root_.left = &fakenode;
      } else if (deleted->color == detail_map::BLACK) {
        Node_Base* Parent = deleted->parent;
        cleaning(sc(deleted));
        fakenode.parent = Parent;
        black_top_case(Parent->left == &fakenode ? Parent->left
                                                 : Parent->right);

      } else if (deleted->color == detail_map::RED) {
        cleaning(sc(deleted));
      }
    } else if (deleted->left->color == detail_map::RED) {
      sc(deleted)->kv = sc(deleted->left)->kv;
      deletion(deleted->left);
    }
  }

  void black_top_case(Node_Base* deleted) {  // должен вернуть корень
    Node_Base* Parent = deleted->parent;
    Node_Base* brother = Parent->left == deleted ? Parent->right : Parent->left;
    detail_map::side son =
        Parent->left == deleted ? detail_map::left : detail_map::right;
    Node_Base* niece = son == detail_map::left ? brother->right : brother->left;
    Node_Base* niece2 =
        son == detail_map::left ? brother->left : brother->right;

    if (brother->color == detail_map::BLACK) {  // брат черный

      if ((brother->left->color == detail_map::RED &&
           brother->right->color == detail_map::RED) ||
          (son == detail_map::left &&
           brother->right->color == detail_map::RED) ||
          (son == detail_map::right &&
           brother->left->color == detail_map::RED)) {
        // 1 случай
        brother->color = Parent->color;
        Parent->color = niece->color = detail_map::BLACK;
        if (Parent == Root_.left) {
          Root_.left = big_turn(brother, son);
        } else {
          Parent = big_turn(brother, son);
        }

      } else if (brother->left->color == detail_map::BLACK &&
                 brother->right->color == detail_map::BLACK) {  // 2 случай

        if (Parent == Root_.left) {  // родитель корень
          brother->color = detail_map::RED;

        } else if (Parent->color == detail_map::RED) {  /// родитель краснсый
          brother->color = detail_map::RED;
          Parent->color = detail_map::BLACK;

        } else {  // родитель черный не корень
          brother->color = detail_map::RED;
          black_top_case(Parent);
        }

      } else {  // 3 случай
        brother->color = detail_map::RED;
        niece2->color = detail_map::BLACK;
        niece = brother;
        brother = dynamic_cast<Node_Base*>(small_turn(sc(brother)));
        brother->color = Parent->color;
        Parent->color = niece->color = detail_map::BLACK;
        if (Parent == Root_.left) {
          Root_.left = big_turn(brother, son);
        } else {
          Parent = big_turn(brother, son);
        }
      }

    } else if (brother->color == detail_map::RED) {
      brother->color = detail_map::BLACK;
      Parent->color = detail_map::RED;

      if (Parent == Root_.left) {
        Root_.left = big_turn(brother, son);
      } else {
        Parent = big_turn(brother, son);
      }
      black_top_case(deleted);
    }
  }

  void cleaning(
      Node_* deleted) {  // но если это буде ткорень надо еще прооверить
    if (deleted) {
      if (deleted != sc(Root_.left)) {
        if (deleted == deleted->parent->right) {
          deleted->parent->right = &fakenode;
        } else {
          deleted->parent->left = &fakenode;
        }
      }
      NodeAllocatorTraits::destroy(_alloc, deleted);
      _alloc.deallocate(deleted, 1);
    }
  }

  Node_Base* search(Node_Base* Root, Key num,
                    int changenum) {  // перенести в мап// перенесла
    Node_Base* result = nullptr;

    if (num == sc(Root)->kv.first && changenum == 1) {
      result = change(sc(Root));  // изменяем если детей не 0
    } else if (num == sc(Root)->kv.first && changenum == 0) {
      result = Root;
    } else if (num >= sc(Root)->kv.first && Root->right != &fakenode) {
      result = search(Root->right, num, changenum);

    } else if (num < sc(Root)->kv.first && Root->left != &fakenode) {
      result = search(Root->left, num, changenum);
    }
    return result;
  }

  Node_Base* change(Node_Base* Tree) {
    Node_Base* deleted = Tree;

    if (Tree->left != &fakenode && Tree->right != &fakenode) {
      deleted = get_max(Tree->left);
      sc(Tree)->kv = sc(deleted)->kv;
    } else if (Tree->left == &fakenode && Tree->right != &fakenode) {
      sc(Tree)->kv = sc(Tree->right)->kv;
      deleted = Tree->right;
    } else if (Tree->left != &fakenode && Tree->right == &fakenode) {
      sc(Tree)->kv = sc(Tree->left)->kv;
      deleted = Tree->left;
    }
    return deleted;
  }

  Node_Base* get_max(Node_Base* Tree) {
    Node_Base* max = Tree;
    while (max->right != &fakenode) {
      max = max->right;
    }
    return max;
  }

  Node_Base* get_min(Node_Base* Tree) {
    Node_Base* min = Tree;
    while (min->left != &fakenode) {
      min = sc(min->left);
    }
    return min;
  }

  Node_Base* previous(Node_Base* now) {
    if (now->left != &fakenode) {
      if (now->left->right == &fakenode) {
        now = sc(now->left);
      } else if (now->left->right != &fakenode) {
        now = sc(now->left);
        while (now->right != &fakenode) {
          now = sc(now->right);
        }
      }
    } else if (now->left == &fakenode) {
      Node_Base* pre = now;
      now = now->parent;
      while (now->left == pre) {
        pre = now;
        now = now->parent;
      }
    }
    return now;
  }

  Node_Base* next(Node_Base* now) {
    if (now->right != &fakenode) {
      if (now->right->left == &fakenode) {
        now = now->right;
      } else if (now->right->left != &fakenode) {
        now = now->right;
        while (now->left != &fakenode) {
          now = now->left;
        }
      }
    } else if (now != &Root_ && now->right == &fakenode) {
      Node_Base* pre = now;
      now = now->parent;

      while (now->right == pre) {
        pre = now;
        now = now->parent;
      }
    }
    return now;
  }

  void action(Node_Base* newLeaf) {
    Node_Base* Parent = sc(newLeaf->parent);
    Node_Base* grandpa = sc(Parent->parent);

    if (grandpa->left == Parent) {  // left parent
      if (grandpa->right->color ==
          detail_map::RED) {  // uncle red   == перекрашиваем. сюда
        // рекурсию и случай если корень
        repainting(Parent);
        if (grandpa->parent != Root_.left &&
            grandpa->parent->color ==
                detail_map::RED) {  // проверяем если не корень ли и крссный то
                                    // рекурсия
          action(grandpa);
        }
      } else {                           // uncle black
        if (Parent->right == newLeaf) {  // right son делаем левым
          Parent = small_turn(Parent);
        }
        if (grandpa == Root_.left) {
          Root_.left = big_turn(Parent, detail_map::no);
        } else {
          grandpa = sc(big_turn(Parent, detail_map::no));
        }
      }
    } else {  // right parent
      if (grandpa->left->color ==
          detail_map::RED) {  // uncle red   == перекрашиваем. сюда
        // рекурсию и случай если корень
        repainting(Parent);
        if (grandpa->parent != Root_.left &&
            grandpa->parent->color ==
                detail_map::RED) {  // проверяем если не корень ли и крссный то
                                    // рекурсия
          action(grandpa);
        }
      } else {                          // uncle black
        if (Parent->left == newLeaf) {  // left son делаем левым
          Parent = small_turn(Parent);
        }
        if (grandpa == &Root_) {
          Root_.left = big_turn(Parent, detail_map::no);
        } else {
          grandpa = sc(big_turn(Parent, detail_map::no));
        }
      }
    }
  }

  Node_Base* big_turn(Node_Base* Parent, detail_map::side son) {
    Node_* grandpa = sc(Parent->parent);

    if (grandpa != Root_.left) {  // если это не корень
      if (grandpa->kv.first < sc(grandpa->parent)->kv.first) {
        grandpa->parent->left = Parent;
      } else {
        grandpa->parent->right = Parent;
      }
      Parent->parent = grandpa->parent;
    } else {
      Parent->parent = &Root_;
      Root_.left = Parent;
    }

    if (grandpa->left->color == detail_map::RED ||
        son == detail_map::right) {  // отец слева дядя справа
      grandpa->left = Parent->right;
      Parent->right->parent = grandpa;
      Parent->right = grandpa;
      Parent->right->parent = Parent;
      if (son == detail_map::no) {
        Parent->color = detail_map::BLACK;
        grandpa->color = detail_map::RED;
      }
    } else {  // отец справа дядя слева
      grandpa->right = Parent->left;
      Parent->left->parent = grandpa;
      Parent->left = grandpa;
      Parent->left->parent = Parent;
      if (son == detail_map::no) {
        Parent->color = detail_map::BLACK;
        grandpa->color = detail_map::RED;
      }
    }
    return Parent;
  }

  Node_Base* small_turn(Node_Base* Parent) {
    Node_Base* grandpa = sc(Parent->parent);
    Node_Base* temp = Parent;

    if (Parent == grandpa->left) {  // родитель левый
      Parent = Parent->right;
      temp->right = Parent->left;  // связи для правого нижнего
      temp->parent = Parent;
      temp->right->parent = temp;  // связи для бывшего левого звена нижнего
      Parent->left = temp;  // связи для нового родителя
      Parent->parent = grandpa;
      grandpa->left = Parent;
    } else {  // родитель правый
      Parent = Parent->left;
      temp->left = Parent->right;  // связи для правого нижнего
      temp->parent = Parent;
      temp->left->parent = temp;  // связи для бывшего левого звена нижнего
      Parent->right = temp;  // связи для нового родителя
      Parent->parent = grandpa;
      grandpa->right = Parent;
    }
    return Parent;
  }

  Node_* sc(Node_Base* node_base) const {
    Node_* node = dynamic_cast<Node_*>(node_base);
    return node;
  }

  std::pair<Node_*, bool> paste(Node_Base* Tree, const value_type& value) {
    std::pair<Node_*, bool> error = {nullptr, 1};

    if (Tree == &fakenode) {  // если корень
      Tree = createTree(value, &Root_);
      error.first = sc(Tree);
      Root_.left = Tree;
      Tree->color = detail_map::BLACK;
    } else {
      if (value.first > sc(Tree)->kv.first) {
        if (Tree->right == &fakenode) {
          Tree->right = createTree(value, Tree);
          error.first = sc(Tree->right);
        } else {
          error = paste(Tree->right, value);
        }
      } else if (value.first < sc(Tree)->kv.first) {
        if (Tree->left == &fakenode) {
          Tree->left = createTree(value, Tree);
          error.first = sc(Tree->left);
        } else {
          error = paste(Tree->left, value);
        }
      } else if (value.first == sc(Tree)->kv.first) {
        error.first = sc(Tree);
        error.second = 0;
      }
    }
    return error;
  }

  void repainting(Node_Base* Parent) {
    if (Parent->parent->left == Parent) {
      Parent->color = detail_map::BLACK;
      Parent->parent->right->color = detail_map::BLACK;
      Parent->parent->color = detail_map::RED;
    } else {
      Parent->color = detail_map::BLACK;
      Parent->parent->left->color = detail_map::BLACK;
      Parent->parent->color = detail_map::RED;
    }
    if (Parent->parent == Root_.left) {
      Parent->parent->color = detail_map::BLACK;
    }
  }

  Node_* createTree(const value_type& value, Node_Base* parent) {
    Node_* newTree = NodeAllocatorTraits::allocate(_alloc, 1);
    NodeAllocatorTraits::construct(_alloc, newTree, value);

    if (!newTree) {
      printf("Memory allocation failed\n");
      return nullptr;
    }

    newTree->kv.first = value.first;
    newTree->kv.second = value.second;
    newTree->color = detail_map::RED;
    newTree->left = newTree->right = &fakenode;
    newTree->parent = parent;
    return newTree;
  }

  void removeTree(
      Node_Base* Tree) {  // деструктор и как то проверку на налл надо сделать

    if (size_ > 0) {
      if (Tree->left != &fakenode) {
        removeTree(Tree->left);
        Tree->left = &fakenode;
      }
      if (Tree->left == &fakenode && Tree->right != &fakenode) {
        removeTree(Tree->right);
        Tree->right = &fakenode;
      }
      if (Tree->left == &fakenode && Tree->right == &fakenode) {
        Node_* TreeR = sc(Tree);
        NodeAllocatorTraits::destroy(_alloc, TreeR);
        _alloc.deallocate(TreeR, 1);
      }
    }
  }

  Node_Base* for_begin(Node_Base* start) const {
    if (start != &fakenode) {
      if (start->left != &fakenode) {
        start = for_begin(sc(start->left));
      }
    }
    return start;
  }
};
}  // namespace s21
#endif  // _CONTAINERS_MAP_S21_MAP_HPP

#ifndef _CONTAINERS_SET_S21_SET_HPP
#define _CONTAINERS_SET_S21_SET_HPP

#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <optional>

#include "../../sequence_containers/list/s21_list.h"
#include "../../sequence_containers/vector/s21_vector.h"

namespace s21 {

namespace detail_set {

enum Color { RED, BLACK };
enum side { left, right, no };

struct Node_Base {
  Node_Base* parent;
  Node_Base* left;
  Node_Base* right;
  Color color;

  Node_Base()
      : parent(this), left(this), right(this), color(detail_set::BLACK) {}
  Node_Base(Node_Base* a, Node_Base* b, Node_Base* c)
      : parent(a), left(b), right(c), color(detail_set::BLACK) {}

  virtual ~Node_Base() = default;
};

template <typename Key>
struct Node : public Node_Base {
  Key key_;
  Node(Key _key) : key_(_key) {}
};
}  // namespace detail_set

namespace iteratorr {

template <typename Key>
class SetIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using pointer = Key*;
  using reference = Key&;
  using Node_ = detail_set::Node<Key>;
  using Node_Base = detail_set::Node_Base;

 private:
  Node_Base* ptr_;
  Node_Base* fakenode_;
  Node_Base* Root_;

 public:
  SetIterator() : ptr_(nullptr) {}
  SetIterator(Node_Base* _ptr, Node_Base* FN, Node_Base* Rt)
      : ptr_(_ptr), fakenode_(FN), Root_(Rt) {}

  reference operator*() const noexcept {
    return static_cast<Node_*>(ptr_)->key_;
  }

  SetIterator<Key>& operator++() {
    ptr_ = next(ptr_);
    return *this;
  }

  SetIterator<Key>& operator--() noexcept {
    ptr_ = previous(ptr_);
    return *this;
  }

  friend bool operator==(const SetIterator<Key>& __x,
                         const SetIterator<Key>& __y) {
    return __x.ptr_ == __y.ptr_;
  }

  friend bool operator!=(const SetIterator<Key>& __x,
                         const SetIterator<Key>& __y) {
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

template <typename Key>
class SetConstIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using pointer = const Key*;
  using reference = const Key&;
  using Node_ = detail_set::Node<Key>;
  using Node_Base = detail_set::Node_Base;

 private:
  const Node_Base* ptr_;
  const Node_Base* fakenode_;
  const Node_Base* Root_;

 public:
  SetConstIterator() : ptr_(nullptr) {}

  SetConstIterator(const Node_Base* _ptr, const Node_Base* FN,
                   const Node_Base* Rt)
      : ptr_(_ptr), fakenode_(FN), Root_(Rt) {}

  reference operator*() const noexcept {
    return static_cast<const Node_*>(ptr_)->key_;
  }

  SetConstIterator<Key>& operator++() {
    ptr_ = next(ptr_);
    return *this;
  }

  SetConstIterator<Key>& operator--() noexcept {
    ptr_ = previous(ptr_);
    return *this;
  }

  friend bool operator==(const SetConstIterator<Key>& __x,
                         const SetConstIterator<Key>& __y) {
    return __x.ptr_ == __y.ptr_;
  }

  friend bool operator!=(const SetConstIterator<Key>& __x,
                         const SetConstIterator<Key>& __y) {
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

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key>>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using size_type = size_t;

  using iterator =
      iteratorr::SetIterator<Key>;  // or BinaryTree::iterator as internal
                                    // iterator of tree subclass; defines the
                                    // type for iterating through the container
  using const_iterator = iteratorr::SetConstIterator<Key>;
  using Node_ = detail_set::Node<Key>;
  using Node_Base = detail_set::Node_Base;

  using allocator_type = Allocator;
  using Allocator_Traits = std::allocator_traits<Allocator>;
  using node_allocator =
      typename std::allocator_traits<Allocator>::template rebind_alloc<Node_>;
  using NodeAllocatorTraits = std::allocator_traits<node_allocator>;
  using pointer = typename std::allocator_traits<Allocator>::pointer;
  using const_pointer =
      typename std::allocator_traits<Allocator>::const_pointer;
  using reference = value_type&;
  using const_reference = const value_type&;

 private:
  size_type size_;
  Node_Base Root_;
  Node_Base fakenode;
  node_allocator _alloc;

 public:
  //-----------------------counstract--------------------//
  set()
      : size_(0),
        Root_(nullptr, &fakenode, &fakenode),
        fakenode(&fakenode, &fakenode, &fakenode) {}

  set(std::initializer_list<value_type> const& items)
      : size_(0),
        Root_(nullptr, &fakenode, &fakenode),
        fakenode(&fakenode, &fakenode, &fakenode) {
    for (auto begin = items.begin(), end = items.end(); begin != end; ++begin) {
      insert(*begin);
    }
  }

  set(const set& m)
      : size_(0),
        Root_(nullptr, &fakenode, &fakenode),
        fakenode(&fakenode, &fakenode, &fakenode) {  // вернуть конст
    for (const_iterator begin = m.begin(); begin != m.end(); ++begin) {
      insert((*begin));
    }
  }

  set(set&& m)
      : size_(0),
        Root_(nullptr, &fakenode, &fakenode),
        fakenode(&fakenode, &fakenode, &fakenode) {  // move
    swap(m);
  }

  ~set() { removeTree(Root_.left); }

  set& operator=(set&& other) {
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
    return std::numeric_limits<size_type>::max() / sizeof(Node_);
  }

  void clear() {
    removeTree(Root_.left);
    size_ = 0;
    Root_.left = Root_.right = fakenode.left = fakenode.right =
        fakenode.parent = &fakenode;
    Root_.parent = nullptr;
  }

  std::pair<iterator, bool> insert(const value_type& value) {  // вставка
    std::pair<Node_Base*, bool> add = paste(Root_.left, value);
    if (add.second == true) {
      size_++;
      if (size_ > 1 && add.first->parent->color == detail_set::RED) {
        action(add.first);
      }
    }
    return std::pair<iterator, bool>(iterator(add.first, &fakenode, &Root_),
                                     add.second);
  }

  void erase(iterator pos) {
    Node_Base* deleted =
        search(Root_.left, (*pos), 1);  // поиск удаляемой вершины

    if (deleted != nullptr) {
      deletion(sc(deleted));
      size_--;
    }
  }

  void swap(set& other) {
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

  void merge(set& other) {
    for (auto i = other.begin(); i != other.end(); ++i) {
      insert((*i));
    }
  }

  bool contains(const Key& key) {
    Node_Base* deleted = search(Root_.left, key, 0);
    return deleted == nullptr ? false : true;
  }

  iterator find(const Key& key) {
    Node_Base* deleted = search(Root_.left, key, 0);  // поиск удаляемой вершины
    return deleted == nullptr ? iterator(&Root_, &fakenode, &Root_)
                              : iterator(deleted, &fakenode, &Root_);
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    vector<std::pair<iterator, bool>> result;
    for (const auto& arg : {args...}) {
      result.push_back(insert(arg));
    }
    return result;
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

  void deletion(Node_* deleted) {
    if (deleted->left == &fakenode &&
        deleted->right == &fakenode) {  // детей нет
      if (deleted == sc(Root_.left)) {
        cleaning(deleted);
        Root_.left = &fakenode;
      } else if (deleted->color == detail_set::BLACK) {
        Node_* Parent = sc(deleted->parent);
        cleaning(deleted);
        fakenode.parent = Parent;
        black_top_case(Parent->left == &fakenode ? Parent->left
                                                 : Parent->right);

      } else if (deleted->color == detail_set::RED) {
        cleaning(deleted);
      }
    } else if (deleted->left->color == detail_set::RED) {
      deleted->key_ = sc(deleted->left)->key_;
      deletion(sc(deleted->left));
    }
  }

  void black_top_case(Node_Base* deleted) {  // должен вернуть корень
    Node_Base* Parent = deleted->parent;
    Node_Base* brother = Parent->left == deleted ? Parent->right : Parent->left;
    detail_set::side son =
        Parent->left == deleted ? detail_set::left : detail_set::right;
    Node_Base* niece = son == detail_set::left ? brother->right : brother->left;
    Node_Base* niece2 =
        son == detail_set::left ? brother->left : brother->right;

    if (brother->color == detail_set::BLACK) {  // брат черный

      if ((brother->left->color == detail_set::RED &&
           brother->right->color == detail_set::RED) ||
          (son == detail_set::left &&
           brother->right->color == detail_set::RED) ||
          (son == detail_set::right &&
           brother->left->color == detail_set::RED)) {
        // 1 случай
        brother->color = Parent->color;
        Parent->color = niece->color = detail_set::BLACK;
        if (Parent == Root_.left) {
          Root_.left = big_turn(brother, son);
        } else {
          Parent = big_turn(brother, son);
        }

      } else if (brother->left->color == detail_set::BLACK &&
                 brother->right->color == detail_set::BLACK) {  // 2 случай

        if (Parent == Root_.left) {  // родитель корень
          brother->color = detail_set::RED;

        } else if (Parent->color == detail_set::RED) {  /// родитель краснсый
          brother->color = detail_set::RED;
          Parent->color = detail_set::BLACK;

        } else {  // родитель черный не корень
          brother->color = detail_set::RED;
          black_top_case(Parent);
        }

      } else {  // 3 случай
        brother->color = detail_set::RED;
        niece2->color = detail_set::BLACK;
        niece = brother;
        brother = dynamic_cast<Node_Base*>(small_turn(sc(brother)));
        brother->color = Parent->color;
        Parent->color = niece->color = detail_set::BLACK;
        if (Parent == Root_.left) {
          Root_.left = big_turn(brother, son);
        } else {
          Parent = big_turn(brother, son);
        }
      }

    } else if (brother->color == detail_set::RED) {
      brother->color = detail_set::BLACK;
      Parent->color = detail_set::RED;

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

    if (num == sc(Root)->key_ && changenum == 1) {
      result = change(sc(Root));  // изменяем если детей не 0
    } else if (num == sc(Root)->key_ && changenum == 0) {
      result = Root;
    } else if (num >= sc(Root)->key_ && Root->right != &fakenode) {
      result = search(Root->right, num, changenum);

    } else if (num < sc(Root)->key_ && Root->left != &fakenode) {
      result = search(Root->left, num, changenum);
    }
    return result;
  }

  Node_Base* change(Node_Base* Tree) {
    Node_Base* deleted = Tree;

    if (Tree->left != &fakenode && Tree->right != &fakenode) {
      deleted = get_max(Tree->left);
      sc(Tree)->key_ = sc(deleted)->key_;
    } else if (Tree->left == &fakenode && Tree->right != &fakenode) {
      sc(Tree)->key_ = sc(Tree->right)->key_;
      deleted = Tree->right;
    } else if (Tree->left != &fakenode && Tree->right == &fakenode) {
      sc(Tree)->key_ = sc(Tree->left)->key_;
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
        now = now->left;
      } else if (now->left->right != &fakenode) {
        now = now->left;
        while (now->right != &fakenode) {
          now = now->right;
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

 private:
  std::pair<Node_Base*, bool> paste(Node_Base* Tree, const value_type& value) {
    std::pair<Node_Base*, bool> error = {nullptr, 1};

    if (Tree == &fakenode) {  // если корень
      Tree = createTree(value, &Root_);
      error.first = Tree;
      Root_.left = Tree;
      Tree->color = detail_set::BLACK;
    } else {
      if (value > sc(Tree)->key_) {  // сделать просто больше для сета
        if (Tree->right == &fakenode) {
          Tree->right = createTree(value, Tree);
          error.first = sc(Tree->right);
        } else {
          error = paste(Tree->right, value);
        }
      } else if (value < sc(Tree)->key_) {
        if (Tree->left == &fakenode) {
          Tree->left = createTree(value, Tree);
          error.first = sc(Tree->left);
        } else {
          error = paste(Tree->left, value);
        }
      } else if (value == sc(Tree)->key_) {  // вернуть для сета
        error.first = sc(Tree);
        error.second = 0;
      }
    }
    return error;
  }

  void action(Node_Base* newLeaf) {
    Node_Base* Parent = sc(newLeaf->parent);
    Node_Base* grandpa = sc(Parent->parent);

    if (grandpa->left == Parent) {  // left parent
      if (grandpa->right->color ==
          detail_set::RED) {  // uncle red   == перекрашиваем. сюда
        // рекурсию и случай если корень
        repainting(Parent);
        if (grandpa->parent != Root_.left &&
            grandpa->parent->color ==
                detail_set::RED) {  // проверяем если не корень ли и крссный то
                                    // рекурсия
          action(grandpa);
        }
      } else {                           // uncle black
        if (Parent->right == newLeaf) {  // right son делаем левым
          Parent = small_turn(Parent);
        }
        if (grandpa == Root_.left) {
          Root_.left = big_turn(Parent, detail_set::no);
        } else {
          grandpa = sc(big_turn(Parent, detail_set::no));
        }
      }
    } else {  // right parent
      if (grandpa->left->color ==
          detail_set::RED) {  // uncle red   == перекрашиваем. сюда
        // рекурсию и случай если корень
        repainting(Parent);
        if (grandpa->parent != Root_.left &&
            grandpa->parent->color ==
                detail_set::RED) {  // проверяем если не корень ли и крссный то
                                    // рекурсия
          action(grandpa);
        }
      } else {                          // uncle black
        if (Parent->left == newLeaf) {  // left son делаем левым
          Parent = small_turn(Parent);
        }
        if (grandpa == &Root_) {
          Root_.left = big_turn(Parent, detail_set::no);
        } else {
          grandpa = sc(big_turn(Parent, detail_set::no));
        }
      }
    }
  }

  Node_Base* big_turn(Node_Base* Parent, detail_set::side son) {
    Node_* grandpa = sc(Parent->parent);

    if (grandpa != Root_.left) {  // если это не корень
      if (grandpa == grandpa->parent->left) {
        grandpa->parent->left = Parent;
      } else {
        grandpa->parent->right = Parent;
      }
      Parent->parent = grandpa->parent;
    } else {
      Parent->parent = &Root_;
      Root_.left = Parent;
    }

    if (grandpa->left->color == detail_set::RED ||
        son == detail_set::right) {  // отец слева дядя справа
      grandpa->left = Parent->right;
      Parent->right->parent = grandpa;
      Parent->right = grandpa;
      Parent->right->parent = Parent;
      if (son == detail_set::no) {
        Parent->color = detail_set::BLACK;
        grandpa->color = detail_set::RED;
      }
    } else {  // отец справа дядя слева
      grandpa->right = Parent->left;
      Parent->left->parent = grandpa;
      Parent->left = grandpa;
      Parent->left->parent = Parent;
      if (son == detail_set::no) {
        Parent->color = detail_set::BLACK;
        grandpa->color = detail_set::RED;
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

  void repainting(Node_Base* Parent) {
    if (Parent->parent->left == Parent) {
      Parent->color = detail_set::BLACK;
      Parent->parent->right->color = detail_set::BLACK;
      Parent->parent->color = detail_set::RED;
    } else {
      Parent->color = detail_set::BLACK;
      Parent->parent->left->color = detail_set::BLACK;
      Parent->parent->color = detail_set::RED;
    }
    if (Parent->parent == Root_.left) {
      Parent->parent->color = detail_set::BLACK;
    }
  }

  Node_* createTree(const value_type& value, Node_Base* parent) {
    Node_* newTree = NodeAllocatorTraits::allocate(_alloc, 1);
    NodeAllocatorTraits::construct(_alloc, newTree, value);

    if (!newTree) {
      printf("Memory allocation failed\n");
      return nullptr;
    }

    newTree->key_ = value;
    newTree->color = detail_set::RED;
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
        start = for_begin(start->left);
      }
    }
    return start;
  }
};
}  // namespace s21
#endif  // _CONTAINERS_SET_S21_SET_HPP

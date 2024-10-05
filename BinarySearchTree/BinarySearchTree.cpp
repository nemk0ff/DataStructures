#include "BinarySearchTree.h"
#include <iostream>
using namespace std;

BinarySearchTree::Node::Node(Key key, Value value, Node *parent, Node *left,
                             Node *right, bool flag) {
  keyValuePair.first = key;
  keyValuePair.second = value;
  this->parent = parent;
  this->left = left;
  this->right = right;
  this->flag = flag;
}

BinarySearchTree::Node::Node(const Node &other) {
  keyValuePair.first = other.keyValuePair.first;
  keyValuePair.second = other.keyValuePair.second;
  flag = other.flag;
  if (other.left) {
    left = new Node(*other.left);
    left->parent = this;
  }
  if (other.right) {
    right = new Node(*other.right);
    right->parent = this;
  }
}

bool BinarySearchTree::Node::operator==(const Node &other) const {
  return (parent == other.parent && left == other.left && right == other.right);
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &other) {
  if (other._root) {
    _root = new Node(*other._root);
  }
  _size = other._size;
}

BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &other) {
  if (this != &other) {
    if (other._root) {
      clear_tree(_root);
      _root = new Node(*other._root);
      }
    _size = other._size;
  }
  return *this;
}

BinarySearchTree::BinarySearchTree(BinarySearchTree &&other) noexcept {
  _root = other._root;
  _size = other._size;

  other._root = nullptr;
  other._size = 0;
}

BinarySearchTree &
BinarySearchTree::operator=(BinarySearchTree &&other) noexcept {
  if (this != &other) {
    _root = other._root;
    _size = other._size;

    other._root = nullptr;
    other._size = 0;
  }
  return *this;
}

BinarySearchTree::~BinarySearchTree() {
  if (_root) {
    clear_tree(_root);
  }
}

void BinarySearchTree::clear_tree(Node *node) {
  if (node) {
    if (node->left)
      clear_tree(node->left);
    if (node->right)
      clear_tree(node->right);
    delete node;
  }
}

BinarySearchTree::Iterator::Iterator(Node *node) { 
  _node = node; 
}

std::pair<Key, Value> &BinarySearchTree::Iterator::operator*() {
  return _node->keyValuePair;
}

const std::pair<Key, Value> &BinarySearchTree::Iterator::operator*() const {
  return _node->keyValuePair;
}

std::pair<Key, Value> *BinarySearchTree::Iterator::operator->() {
  return &(_node->keyValuePair);
}

const std::pair<Key, Value> *BinarySearchTree::Iterator::operator->() const {
  return &(_node->keyValuePair);
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++() {
  //Если у узла есть правый
  if (_node->right != nullptr) 
  {
    _node = _node->right; // то переходим к нему
    // и идем от него влево до конца
    while (_node->left != nullptr) 
    {
      _node = _node->left;
    }
  } else // если у узла нет правого
    // Ищем предка, для которого мы являемся левым потомком
  {
    Node *parent = _node->parent; 
    while (parent != nullptr &&
           _node == parent->right) 
    {
      _node = parent;
      parent = parent->parent;
    }
    _node = parent;
  }
  return *this;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++(int) {
  Iterator temp = *this;
  ++(*this);
  return temp;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--() {
  if (_node->left != nullptr) //если у узла есть левый
  {
    _node = _node->left; //то переходим к нему
    //и идем от него вправо до конца
    while (_node->right != nullptr) 
    {
      _node = _node->right;
    }
  } else //если у узла нет левого
    // Ищем предка, для которого мы являемся правым потом
  {
    Node *parent = _node->parent; 
    while (parent != nullptr &&
           _node == parent->left) 
    {
      _node = parent;
      parent = parent->parent;
    }
    _node = parent;
  }
  return *this;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--(int) {
  Iterator temp = *this;
  --(*this);
  return temp;
}

bool BinarySearchTree::Iterator::operator==(const Iterator &other) const {
  return (_node == other._node);
}

bool BinarySearchTree::Iterator::operator!=(const Iterator &other) const {
  return (_node != other._node);
}

BinarySearchTree::ConstIterator::ConstIterator(const Node *node) {
  _node = node;
}

const std::pair<Key, Value> &
BinarySearchTree::ConstIterator::operator*() const {
  return _node->keyValuePair;
}

const std::pair<Key, Value> *
BinarySearchTree::ConstIterator::operator->() const {
  return &(_node->keyValuePair);
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++() {
  if (_node->right != nullptr && !_node->right->flag) //если у узла есть правый
  {
    _node = _node->right; //то переходим к нему
    //и идем от него влево до конца
    while (_node->left != nullptr) 
    {
      _node = _node->left;
    }
  } else //если у узла нет правого
  {
    Node *parent = _node->parent; //идем к родителю
     // Ищем предка, для которого мы правый потомок
    while (parent != nullptr &&
           _node == parent->right)
    {
      _node = parent;
      parent = parent->parent;
    }
    _node = parent;
  }
  return *this;
}

BinarySearchTree::ConstIterator
BinarySearchTree::ConstIterator::operator++(int) {
  ConstIterator temp = *this;
  ++(*this);
  return temp;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--() {
  if (_node->left != nullptr) //если у узла есть левый
  {
    _node = _node->left; //то переходим к нему
    while (_node->right != nullptr) //и идем от него по правой ветке до конца
    {
      _node = _node->right;
    }
  } else //если у узла нет левого
  {
    // Ищем предка, для которого мы левый потомок
    Node *parent = _node->parent; 
    while (parent != nullptr &&
           _node == parent->left) 
    {
      _node = parent;
      parent = parent->parent;
    }
    _node = parent;
  }
  return *this;
}

BinarySearchTree::ConstIterator
BinarySearchTree::ConstIterator::operator--(int) {
  ConstIterator temp = *this;
  --(*this);
  return temp;
}

bool BinarySearchTree::ConstIterator::operator==(
    const ConstIterator &other) const {
  return (_node == other._node);
}

bool BinarySearchTree::ConstIterator::operator!=(
    const ConstIterator &other) const {
  return (_node != other._node);
}

BinarySearchTree::ConstIterator BinarySearchTree::find(const Key &key) const {
  Node *current = _root; 
  while (current != nullptr)
  {
    if (key > current->keyValuePair.first &&
        !current->right->flag) 
    {
      current = current->right;
    } else if (key <
               current->keyValuePair.first)
    {
      current = current->left;
    } else if (key == current->keyValuePair.first) //если ключи равны
    {
      return ConstIterator(current);
    } else
      return cend(); 
  }
  return ConstIterator(nullptr);
}

BinarySearchTree::Iterator BinarySearchTree::find(const Key &key) {
  Node *current = _root; 
  while (current != nullptr)
  {
    if (current->right && key > current->keyValuePair.first &&
        !current->right->flag) 
    {
      current = current->right;
    } else if (current->left &&
               key <
                   current->keyValuePair.first) 
    {
      current = current->left;
    } else if (key == current->keyValuePair.first) 
    {
      return Iterator(current);
    } else
      return end(); 
  }
  return end();
}

std::pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator>
BinarySearchTree::equalRange(const Key &key) {
  Iterator begin(nullptr);
  Iterator end(nullptr);
  Iterator helper = this->begin();
  int flag = 1;

  while (helper != this->end()) {
    if ((*helper).first == key) {
      if (flag) {
        begin = helper;
        flag = 0;
      }
      Iterator tmp = helper;
      ++tmp;
      if ((*tmp).first > key || tmp == this->end()) {
        end = tmp;
        break;
      }
    }
      helper++;
  }
  return std::pair<Iterator, Iterator>(begin, end);
}

std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator>
BinarySearchTree::equalRange(const Key &key) const {
  ConstIterator begin(nullptr);
  ConstIterator end(nullptr);
  ConstIterator helper = cbegin();
  int flag = 1;


  while (helper != cend()) {
    if ((*helper).first == key) {
      if (flag) {
        begin = helper;
        flag = 0;
      }
      ConstIterator temp = helper;
      ++temp;
      if ((*temp).first > key || temp == cend()) {
        end = temp;
        break;
      }
    }
      helper++;
  }
  return std::pair<ConstIterator, ConstIterator>(begin, end);
}

BinarySearchTree::ConstIterator BinarySearchTree::min(const Key &key) const {
  Node *current = _root;
  Node *res = nullptr;
  Value min;
  int f = 1; 
  while (current != nullptr) 
  {
    if (key > current->keyValuePair.first &&
        !current->right->flag) 
    {
      current = current->right;
    } else if (key < current->keyValuePair.first)
    {
      current = current->left;
    } else 
    {
      if (current->keyValuePair.second < min || f) 
      {
        if(min > current->keyValuePair.second) min = current->keyValuePair.second; 
        res = current; 
        f = 0;        
      }
      current = current->right; 
    }
  }
  return ConstIterator(res);
}

BinarySearchTree::ConstIterator BinarySearchTree::min() const {
  Node *current = _root;
  while (current->left) {
    current = current->left;
  }
  return ConstIterator(current);
}

BinarySearchTree::ConstIterator BinarySearchTree::max(const Key &key) const {
  Node *current = _root; 
  Node *res = nullptr;
  Value max;
  int f = 1; 
  while (current != nullptr) 
  {
    if (key > current->keyValuePair.first &&
        !current->right->flag) 
    {
      current = current->right;
    } else if (key <
               current->keyValuePair.first) 
    {
      current = current->left;
    } else 
    {
      if (current->keyValuePair.second > max || f) 
      {
        max = current->keyValuePair.second; 
        res = current; 
        f = 0;         
      }
      current = current->right;
    }
  }
  return ConstIterator(res);
}

BinarySearchTree::ConstIterator BinarySearchTree::max() const {
  Node *current = _root; 
  while (current && current->right && !current->right->flag) {
    current = current->right;
  }
  return ConstIterator(current);
}

BinarySearchTree::Iterator BinarySearchTree::begin() {
  Node *current = _root;
  while (current && current->left) {
    current = current->left;
  }
  return Iterator(current);
}

BinarySearchTree::ConstIterator BinarySearchTree::cbegin() const {
  return min();
}

BinarySearchTree::Iterator BinarySearchTree::end() {
  Node *current = _root;
  while (current && current->right) {
    current = current->right;
  }
  return Iterator(current);
}

BinarySearchTree::ConstIterator BinarySearchTree::cend() const {
  Node *current = _root;
  while (current && current->right) {
    current = current->right;
  }
  return ConstIterator(current);
}

size_t BinarySearchTree::size() const { return _size; }

void BinarySearchTree::Node::output_node_tree() const {
  if (flag) {
    std::cout << "Key: " << keyValuePair.first
              << ", Value: " << keyValuePair.second << std::endl;
  } else {
    std::cout << "(nill node)" << std::endl;
  }

  if (left) {
    left->output_node_tree();
  }
  if (right) {
    right->output_node_tree();
  }
}

void BinarySearchTree::output_tree() {
  if (_root != nullptr) {
    _root->output_node_tree();
  } else {
    std::cout << "(Empty tree)" << std::endl;
  }
}

void BinarySearchTree::Node::insert(const Key &key, const Value &value) {
  if (key < keyValuePair.first)
  {
    if (left) 
    {
      left->insert(key, value);
    } else
    {
      Node *node = new Node(key, value, this, nullptr, nullptr);
      this->left = node;
    }
  }
  if (key >= keyValuePair.first)
  {
    if (right) 
    {
      right->insert(key, value);
    } else 
    {
      Node *node = new Node(key, value, this, nullptr, nullptr);
      this->right = node;
    }
  }
}

void BinarySearchTree::insert(const Key &key, const Value &value) {
  if (_root) {
    delete_nill();
    _root->insert(key, value);
  } else {
    _root = new Node(key, value);
  }
  insert_nill();
  _size++;
}

BinarySearchTree::Node *BinarySearchTree::Node::erase_node(Node *node, const Key &key) {
  if (node == nullptr)
    return node;
  if (key < node->keyValuePair.first) 
  {
    node->left = erase_node(node->left, key); 
    return node;
  } else if (key > node->keyValuePair.first) 
  {
    node->right = erase_node(node->right, key); 
    return node;
  }
  // 1 ребенок или без детей
  if (node->left == nullptr) {
    Node *temp = node->right;
    delete node;
    return temp;
  } else if (node->right == nullptr) {
    Node *temp = node->left;
    delete node;
    return temp;
  }

  // 2 ребенка
  Node *temp = node->right; 
  Node *parent = node;    
  while (temp->left != nullptr) {
    parent = temp;
    temp = temp->left; 
  }

  node->keyValuePair = temp->keyValuePair;
  if (parent->left == temp) {
    parent->left = temp->right;
  } else {
    parent->right = temp->right;
  }
  delete temp;
  return node;
}

void BinarySearchTree::erase(const Key &key) {
  if (_root) {
    delete_nill();
    _root = _root->erase_node(_root, key);
    _size--;
    insert_nill();
  }
  // Пока в дереве есть ключи key, удаляем их
  Iterator f = find(key);
  if (f != end()) {
    erase(key);
  }
}
void BinarySearchTree::delete_nill() {
  Node *current = _root;
  if (!current)
    return;
  while (current->right) {
    current = current->right;
  }
  if (current != nullptr && current->flag) {
    current->parent->right = nullptr;
    delete current;
  }
}

void BinarySearchTree::insert_nill() {
  if (_root) {
    Node *nil = new Node(0, 0);
    nil->flag = true;
    Node *current = _root;
    while (current->right) {
      current = current->right;
    }
    if (!current->flag) {
      current->right = nil;
      nil->parent = current;
    }
  }
}

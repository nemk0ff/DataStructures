#pragma once
#include "StackImplementation.h"
#include <list>
class ListStack : public IStackImplementation {
public:
  // добавление в хвост
  void push(const ValueType &value) override;
  // удаление с хвоста
  void pop() override;
  // посмотреть элемент в хвосте
  const ValueType &top() const override;
  // проверка на пустоту
  bool isEmpty() const override;
  // размер
  size_t size() const override;
  // виртуальный деструктор
  virtual ~ListStack() = default;

private:
  std::list<ValueType> container;
};

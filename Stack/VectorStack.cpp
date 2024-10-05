#include "VectorStack.h"
using namespace std;

// добавление в хвост
void VectorStack::push(const ValueType &value) { container.push_back(value); }
// удаление с хвоста
void VectorStack::pop() { container.pop_back(); }
// посмотреть элемент в хвосте
const ValueType &VectorStack::top() const { return container.back(); }
// проверка на пустоту
bool VectorStack::isEmpty() const { return container.empty(); }
// размер
size_t VectorStack::size() const { return container.size(); }

#include "ListStack.h"

// добавление в хвост
void ListStack:: push(const ValueType& value){
    container.push_back(value);
}
// удаление с хвоста
void ListStack:: pop(){
    container.pop_back();
}
// посмотреть элемент в хвосте
const ValueType& ListStack:: top() const{
    return container.back();
}

// проверка на пустоту
bool ListStack:: isEmpty() const{
    return container.empty();
}
// размер
size_t ListStack:: size() const{
    return container.size();
}

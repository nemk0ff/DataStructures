#include "Vector.h"
#include <iostream>
using namespace std;

//! Конструктор с параметрами
Vector::Vector(const ValueType* rawArray, const size_t size, float coef) 
{
  if (coef <= 1)
  {
    throw invalid_argument("Coef must be >1");
  }
  _size = size;
  _capacity = size;
  _multiplicativeCoef = coef;
  _data = new ValueType[_capacity];
  for (size_t i = 0; i < _size; i++)
  {
    _data[i] = rawArray[i];
  }
}
//!Конструктор копирования
//!\param other - копируемый объект
// Создаем новый вектор путем копирования переданного другого вектора
Vector::Vector(const Vector& other) 
{
  _size = other._size;
  _capacity = other._size;
  _multiplicativeCoef = other._multiplicativeCoef;
  _data = new ValueType[_capacity];
  for (size_t i = 0; i < _size; i++)
  {
    _data[i] = other._data[i];
  }
}
//! Оператор присваивания копированием
//! \param other - копируемый объект
Vector& Vector::operator= (const Vector &other) 
{
  if (this == &other)
  {
    return *this;
  }
  delete[] _data;
  _size = other._size;
  _capacity = other._capacity;
  _multiplicativeCoef = other._multiplicativeCoef;
  _data = new ValueType[_capacity];
  for (size_t i = 0; i < _size; i++)
  {
    _data[i] = other._data[i];
  }
  return *this;
}
//! Конструктор перемещения
//! \param other - перемещаемый объект
// Создаем новый вектор путем копирования переданного другого вектора, а исходный удаляем
Vector::Vector(Vector&& other) noexcept 
{
  _size = other._size;
  _capacity = other._capacity;
  _data = other._data;
  _multiplicativeCoef = other._multiplicativeCoef;
  other._multiplicativeCoef = 0;
  other._size = 0;
  other._capacity = 0;
  other._data = NULL;
}
//! Оператор присваивания перемещением
//! \param other - перемещаемый объект
Vector& Vector::operator=(Vector &&other) noexcept 
{
  if (this == &other)
  {
    return *this;
  }
  delete[] _data;
  _size = other._size;
  _capacity = other._capacity;
  _data = other._data;
  _multiplicativeCoef = other._multiplicativeCoef;

  other._multiplicativeCoef = 0;
  other._size = 0;
  other._capacity = 0;
  other._data = NULL;
  return *this;
}
//! Деструктор
// Удаления динамического массива и освобождения его памяти
Vector::~Vector() 
{
  delete[] _data;
}

//! Вставка в конец
void Vector::pushBack(const ValueType& value) 
{
  if (_size + 1 >= _capacity)
  {
    if (_capacity == 0)
    {
      _capacity++;
    }
    while (_size + 1 >= _capacity)
    {
      _capacity *= _multiplicativeCoef;
    }
    ValueType* _helper = new ValueType[(int)_capacity];
    for(int i = 0; i < _size; i++)
    {
      _helper[i] = _data[i];
    }
    delete[] _data;
    _data = _helper;
  }
  _data[_size] = value;
  _size++;
}

//! Вставка в начало
void Vector::pushFront(const ValueType &value)
{
  if (_size + 1 >= _capacity)
  {
    if (_capacity == 0)
    {
      _capacity++;
    }
    while (_size + 1 >= _capacity)
    {
      _capacity *= _multiplicativeCoef;
    }
    ValueType* _helper = new ValueType[(int)_capacity];
    for(int i = 1; i < _size + 1; i++)
    {
      _helper[i] = _data[i - 1];
    }
    delete[] _data;
    _data = _helper;
  }
  else
  {
    for(int i = _size; i > 0; i--)
    {
      _data[i] = _data[i - 1];
    }
  }
  _data[0] = value;
  _size++;
}

//! Вставка элемента value в позицию pos
void Vector::insert(const ValueType& value, size_t pos) 
{
  if (_size + 1 >= _capacity)
  {
    if (_capacity == 0)
    {
      _capacity++;
    }
    while (_size + 1 >= _capacity)
    {
      _capacity *= _multiplicativeCoef;
    }
    ValueType* _helper = new ValueType[(int)_capacity];
    for(int i = 1; i < _size + 1; i++)
    {
      _helper[i] = _data[i - 1];
    }
    delete[] _data;
    _data = _helper;
  }
  for(int i = _size; i > pos; i--)
  {
    _data[i] = _data[i - 1];
  }
  _data[pos] = value;
}

//! Вставка массива элементов типа ValueType в позицию pos
void Vector::insert(const ValueType* values, size_t size, size_t pos) 
{
    if ((_size + size) > _capacity) 
    {
      // Места не хватит. Надо выполнить расширение с учетом коэффициента расширения + кусок размера size
      int newCapacity = _capacity == 0 ? size : ((_capacity * _multiplicativeCoef) + size);
      ValueType *helper = new ValueType[newCapacity];
      // заливаем старые данные
      if (pos > _size) 
      {
        //Позиция за пределами массива. просто всавим в конец
        for (int i = 0; i < _size; i++) 
        {
          helper[i] = _data[i];
        }
        for (int i = 0; i < size; i++) 
        {
          helper[_size + i] = values[i];
        }
      } 
      else 
      {
        for (int i = 0; i < pos; i++) 
        {
          helper[i] = _data[i];
        }
        for (int i = 0; i < size; i++) 
        {
          helper[pos + i] = values[i];
        }
        for (int i = pos; i < _size; i++) 
        {
          helper[size + i] = _data[i];
        }
      }
      _size = _size + size; // новый размер
      delete[] _data; // удаляем старые данные
      _data = helper; // новые данные
      _capacity = newCapacity; // новая граница
    } 
    else 
    {
      if (pos > _size) 
      {
        // Позиция за пределами массива. просто вставим в конец
        for (int i = 0; i < size; i++) 
        {
            _data[_size + i] = values[i];
        }
        _size = _size + size; // новый размер
      } 
      else 
      {
        // просто сдвиг данных на длину вставляемого массива вправо
        for (int i = _size; i > pos; i--) 
        {
          _data[i + size - 1] = _data[i - 1];
        }
        for (int i = 0; i < size; i++) 
        {
          _data[pos + i] = values[i];
        }  
        _size = _size + size; // новый размер
      }
    }
}


//! Вставка содержимого вектора в позицию pos
void Vector::insert(const Vector& vector, size_t pos) 
{
  if (_size + vector._size >= _capacity)
  {
    if (_capacity == 0)
    {
      _capacity++;
    }
    while (_size + vector._size >= _capacity)
    {
      _capacity *= _multiplicativeCoef;
    }
    ValueType* _helper = NULL;
    _helper = new ValueType[(int)_capacity];
    for(int i = 1; i < _size + 1; i++)
    {
      _helper[i] = _data[i - 1];
    }
    delete[] _data;
    _data = _helper;
  }
  for(int i = _size + vector._size; i > pos; i--)
  {
    _data[i] = _data[i - vector._size];
  }
  for(int i = pos; i < pos + vector._size; i++)
  {
    _data[i] = vector._data[i - pos];
  }
}

//! Удаление с конца
void Vector::popBack() 
{
  // Проверка, что вектор не пустой
  if (_size == 0)
  {
    throw "Error";
  } 
  _size--;
}
//! Удаление из начала
void Vector::popFront() 
{
  if (_size == 0)
  {
    throw "Error";
  }
  // Проверка, что вектор не пустой
  // просто сдвиг данных на один элемент влево
  for (int i = 0; i < _size; i++) 
  {
    _data[i] = _data[i + 1];
  }
  _size--; // новый размер
}

/*!
    \brief Удалить элемент(ы) из вектора
    \param pos: позиция начала удаляемого участка
    \param count: количество удаляемых элементов
    если (pos + count) > size, то элементы интервала [pos, size) должны быть удалены
*/
void Vector::erase(size_t pos, size_t count) 
{
    if (pos + count >= _size) 
    {
      // от позиции до конца. следовательно просто сдвигаем границу
      _size = pos;
    } 
    else 
    {
      // это интервал. переносим элементы
      for (int i = pos; i < _size; i++) 
      {
        _data[i] = _data[i + count];
      }
      _size = _size - count;
    }
}
/*!
    \brief Удалить элемент(ы) из вектора
    \param beginPos: позиция начала удаляемого участка
    \param endPos: позиция окончания удаляемого участка
    Все элементы интервала [beginPos, endPos) должны быть удалены:
    [1, 2, 3, 4] -> erase(1, 3) -> [1, 4]
    если endPos > size, то элементы интервала [beginPos, size) должны быть удалены
*/
void Vector::eraseBetween(size_t beginPos, size_t endPos) 
{
  if (beginPos > endPos || beginPos >= _size) 
  {
    // контроль, чтобы начальная позиция была меньше финальной
    return;
  }
  if (endPos >= _size) 
  {
    // от позиции до конца. следовательно просто сдвигаем границу
    _size = beginPos;
  } 
  else 
  {
    // это интервал. переносим элементы
    int count = _size - endPos - 1;
    for (int i = 0; i < count; i++) 
    {
      _data[beginPos + i] = _data[endPos + i];
    }
    _size = _size - count;
  }
}

//! Количество элементов
size_t Vector::size() const 
{
  return _size;
}
//! Максимальное количество элементов
size_t Vector::capacity() const 
{
  return _capacity;
}

//! Фактор загруженности
// Расчитаем как отношение текущего размера к общедоступному
// При этом проверим, что не делим на ноль
double Vector::loadFactor() const 
{
  return _capacity == 0 ? 0 : (double)(_size)/_capacity;
}
//! Доступ к элементу по индексу
// Доступ по индексу к динамическому массиву
// Проверим, что запрос из доступного диапазона. Иначе формируем исключение
ValueType& Vector::operator[](size_t idx) 
{
  if (idx >= _size) 
  {
    throw out_of_range("Vector::operator[] ERROR: Index out of range");
  }
  return _data[idx];
}

//! Доступ к элементу по индексу (const version)
const ValueType& Vector::operator[](size_t idx) const 
{
  if (idx >= _size) 
  {
    throw out_of_range("Vector::operator[] ERROR: Index out of range");
  }
  return _data[idx];
}

//! Поиск первого вхождения значения
//! \return - индекс элемента
long long Vector::find(const ValueType& value) const 
{
  for (int i = 0; i < _size; i++) 
  {
    if (_data[i] == value) 
    {
      return i;
    }
  }
  return -1;
}

//! Если capacity > _capacity, то выделить новый участок памяти размером capacity и перенести вектор туда, иначе - ничего
void Vector::reserve(size_t capacity) 
{
  if (capacity > _capacity) 
  {
    ValueType *newData = new ValueType[capacity];
    for (int i = 0; i < _size; i++) 
    {
      newData[i] = _data[i];
    }
    delete[] _data; // удаляем старые данные
    _data = newData; // новые данные
    _capacity = capacity; // новая граница
  }
}

//! Уменьшить capacity до size
void Vector::shrinkToFit() 
{
  _capacity = _size;
  ValueType *helper = new ValueType[_size];
  for (int i = 0; i < _size; i++)
  {
    helper[i] = _data[i];
  }
  delete [] _data;
  _data = helper;
}

//=========================================
Vector::Iterator::Iterator(ValueType* ptr) 
{
  _ptr = ptr;
}

ValueType& Vector::Iterator::operator*() 
{
  return *_ptr;
}

const ValueType& Vector::Iterator::operator*() const 
{
  return *_ptr;
}

ValueType* Vector::Iterator::operator->() 
{
  return _ptr;
}

const ValueType* Vector::Iterator::operator->() const 
{
  return _ptr;
}

// Prefix increment
Vector::Iterator Vector::Iterator::operator++() 
{
  _ptr++;
  return *this;
}

// Postfix increment
Vector::Iterator Vector::Iterator::operator++(int) 
{
  Iterator tmp = *this;
  ++(*this);
  return tmp;
}

bool Vector::Iterator::operator==(const Iterator& other) const 
{
  return _ptr == other._ptr; 
}

bool Vector::Iterator:: operator!=(const Iterator& other) const 
{
  return _ptr != other._ptr;
}

//! Получить итератор на начало вектора
Vector::Iterator Vector::begin() 
{
  return Iterator(_data);
}
//! Получить итератор на элемент вектора, следующий за последним
Vector::Iterator Vector::end() 
{
  return Iterator(_data + _size);
}
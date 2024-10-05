#include "HashTable.h"
#include <iostream>

HashTable::HashTable(size_t size) noexcept {
  this->_capacity = size;
  this->_filled = 0;
  this->table.resize(_capacity);
}

HashTable::~HashTable() { this->table.clear(); }

void HashTable::insert(const KeyType &key, const ValueType &value) 
{
  //! Проверяем, есть ли уже такая пара в таблице
  ValueType temp;
  if(this->find(key, temp))
  {
    std::cout << "Такой ключ уже есть в таблице" << std::endl;
    for (auto i: table[hash_function(key)]) {
      if (key == i.first) {
          std::cout << "Before " << i.second << std::endl;
          i.second = value;
        std::cout << "after " << i.second << std::endl;

      }
    }
  }
  else
  {
    // Вставляем пару в хеш-таблицу
    this->table[hash_function(key)].push_back(std::make_pair(key, value));
    // Если мы вставили элемент в пустой лист, то нужно увеличить количество заполненных ячеек
    this->_filled++;
    // Увеличиваем вместимость, если нужно
    if (this->getLoadFactor() > 0.75) {
      this->_capacity *= 2;
      std::vector<std::list<std::pair<KeyType, ValueType>>> temp_table(this->_capacity);
      for (auto &list : this->table)
        {
          for (auto &pair : list)
            {
              temp_table[this->hash_function(pair.first)].push_back(pair);
            }
        }
      this->table = temp_table;
    }
  }
}

bool HashTable::find(const KeyType &key, ValueType &value) const
{
  for (const auto &i: table[hash_function(key)]) {
    if (key == i.first) {
        value = i.second;
        return true;
    }
  }
  return false;
}

void HashTable::remove(const KeyType &key) 
{
  for(auto i = table[hash_function(key)].begin(); i != table[hash_function(key)].end(); i++)
    {
      if(key == i->first)
      {
        table[hash_function(key)].erase(i);
        this->_filled --;
        return;
      }
    }
}

ValueType &HashTable::operator[](const KeyType &key) {
    for (auto i = table[hash_function(key)].begin(); i != table[hash_function((key))].end(); i++) {
        if (i->first == key) {
            return i->second;
        }
    }
    // Если мы обращаемся по ключу, которого нет в таблице, то добавляем его
    insert(key, 0);
    // Вызываем перегрузку оператора ещё раз, она уже сработает, т.к. ключ мы вставили
    return table[hash_function(key)].back().second;
}

double HashTable::getLoadFactor()  {
    return static_cast<double>(_filled) / _capacity;
}

size_t HashTable::hash_function(const KeyType &key) const{
  // Берём сумму ASCII кодов символов в ключе
  size_t sum = 0;
  for (const auto &i : key)
  {
    sum += i;
  }
  // Возвращаем остаток от деления на вместимость хеш-таблицы
  return sum % _capacity;
}

void HashTable::print() const
{
  std::cout << "Capacity: " << _capacity << std::endl;
  std::cout << "Filled: " << _filled << std::endl;
  //std::cout << "LoadFactor: " << getLoadFactor() << std::endl;
  for (const auto &i : table)
    {
      std::cout << "[" << i.size() << "] ";
      for (const auto &j : i)
        {
          std::cout << j.first << " " << j.second << " | ";
        }
      std::cout << std::endl;
    }
}

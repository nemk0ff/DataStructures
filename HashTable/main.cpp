#include <iostream>
#include "HashTable.h"
using namespace std;
int main() 
{
  
  HashTable test(7);
  test.insert("a", 10);
  test.insert("b", 20);
  // Вставляем дубликат
  test.insert("a", 51);
  test.print();
  ValueType temp;
  test.find("a", temp);
  cout << temp << endl;

  /*
  cout << "Вставляем по существующему ключу" << endl;
  // Моя хеш-функция зависит от capacity хеш-таблицы
  // Поэтому возможно такое, что два одинаковых ключа 
  // будут лежать не в одной ячейке, так как они были 
  // вставлены в разное время и при разных размерах таблицы
  test.insert("a", 34);
  //test.insert("b", 23);
  test.print();

  cout << "Удаляем существующий уникальный ключ:" << endl;
  test.remove("d");
  test.print();

  cout << "Удаляем несуществующий ключ" << endl;
  test.remove("z");
  test.print();

  cout << "Поиск существующего ключа" << endl;
  ValueType value;
  cout << test.find("b", value) << endl;
  cout << value << endl;
  
  cout << "Поиск несуществующего ключа" << endl;
  cout << test.find("a", value) << endl;
  cout << value << endl;
  
  cout << "Обращение к существующему ключу" << endl;
  cout << test["x"] << endl;

  cout << "Обращение к несуществующему ключу" << endl;
  cout << test["j"] << endl;
  // тут создается новая пара (x,0)
  test.print(); 
*/
}
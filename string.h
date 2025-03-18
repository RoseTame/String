#ifndef STRING_H
#define STRING_H

#include <algorithm>  // 提供swap函数
#include <cassert>    // 提供assert函数，用于调试时检查条件
#include <cstddef>    // 提供size_t类型
#include <cstring>    // 提供memcpy, strlen等字符串操作函数
#include <iostream>   // 提供输入输出流

namespace rose {

// 自定义字符串类
class string {
 public:
  static const size_t npos = -1;  // 表示无效或未找到的位置

  typedef char *iterator;              // 迭代器类型，指向字符的指针
  typedef const char *const_iterator;  // 常量迭代器类型，指向常量的字符指针

  iterator begin();  // 返回指向字符串开头的迭代器
  iterator end();    // 返回指向字符串结尾的迭代器

  const_iterator begin() const;  // 返回指向字符串开头的常量迭代器
  const_iterator end() const;    // 返回指向字符串结尾的常量迭代器

  string(const char *str = "");  // 构造函数，接受C风格字符串
  string(size_t n, char ch);     // 构造函数：创建包含 n 个字符 ch 的字符串
  string(const string &s);       // 拷贝构造函数
  string &operator=(const string &s);  // 拷贝赋值运算符
  void swap(string &s);                // 交换两个字符串的内容
  ~string();                           // 析构函数

  const char *c_str() const;  // 返回C风格字符串
  size_t size() const;        // 返回字符串的长度
  size_t capacity() const;    // 返回字符串的容量

  char &operator[](size_t pos);              // 返回指定位置的字符，可修改
  const char &operator[](size_t pos) const;  // 返回指定位置的字符，不可修改

  void push_back(char ch);                // 在字符串末尾添加一个字符
  void append(const char *str);           // 在字符串末尾添加C风格字符串
  void reserve(size_t n);                 // 预留至少n个字符的容量
  void resize(size_t n, char ch = '\0');  // 调整字符串大小，新位置用ch填充

  string &operator+=(char ch);          // 在字符串末尾添加一个字符
  string &operator+=(const char *str);  // 在字符串末尾添加C风格字符串
  string &operator+=(const string &s);  // 在字符串末尾添加另一个字符串

  void insert(size_t pos, size_t n, char ch);  // 在指定位置插入n个字符ch
  void insert(size_t pos, const char *str);    // 在指定位置插入C风格字符串

  void erase(size_t pos, size_t len = npos);  // 删除从指定位置开始的len个字符

  size_t find(char ch, size_t pos = 0);  // 查找字符ch，返回第一个匹配的位置
  size_t find(const char *str,
              size_t pos = 0);  // 查找子串str，返回第一个匹配的位置

  string substr(size_t pos = 0,
                size_t len = npos);  // 返回从pos开始，长度为len的子串

  void clear();        // 清空字符串内容
  bool empty() const;  // 判断字符串是否为空

  bool operator<(const string &s);   // 小于运算符
  bool operator==(const string &s);  // 等于运算符
  bool operator<=(const string &s);  // 小于等于运算符
  bool operator>(const string &s);   // 大于运算符
  bool operator>=(const string &s);  // 大于等于运算符
  bool operator!=(const string &s);  // 不等于运算符

 private:
  size_t _size = 0;      // 字符串的当前长度
  size_t _capacity = 0;  // 字符串的当前容量
  char *_str = nullptr;  // 指向字符串内容的指针
};

// 输出运算符重载，用于输出字符串
std::ostream &operator<<(std::ostream &out, const string &s);
// 输入运算符重载，用于从输入流读取字符串
std::istream &operator>>(std::istream &in, string &s);
// 从输入流读取一行字符串
std::istream &getline(std::istream &in, string &s);

}  // namespace rose

#endif

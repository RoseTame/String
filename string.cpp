#include "string.h"

// 构造函数，接受C风格字符串
rose::string::string(const char *str)
    : _size(strlen(str)), _capacity(_size), _str(new char[_capacity + 1]) {
  memcpy(_str, str, _size + 1);  // 将字符串内容拷贝到内部缓冲区
}

// 构造函数：创建包含 n 个字符 ch 的字符串
rose::string::string(size_t n, char ch) {
  _size = n;
  _capacity = n;
  _str = new char[_capacity + 1];  // +1 是给 '\0' 留空间
  for (size_t i = 0; i < _size; ++i) {
    _str[i] = ch;
  }
  _str[_size] = '\0';
}

// 拷贝构造函数，使用现代写法
rose::string::string(const rose::string &s) {
  string tmp(s._str);  // 创建一个临时字符串
  swap(tmp);           // 交换内容
}

// 拷贝赋值运算符，使用现代写法
rose::string &rose::string::operator=(const string &s) {
  if (this != &s) {  // 避免自我赋值
    string tmp(s);   // 创建一个临时字符串
    swap(tmp);       // 交换内容
  }
  return *this;
}

// 交换两个字符串的内容
void rose::string::swap(rose::string &s) {
  std::swap(_str, s._str);            // 交换字符指针
  std::swap(_size, s._size);          // 交换长度
  std::swap(_capacity, s._capacity);  // 交换容量
}

// 析构函数
rose::string::~string() {
  delete[] _str;  // 释放内存
  _str = nullptr;
  _size = _capacity = 0;
}

// 返回C风格字符串
const char *rose::string::c_str() const { return _str; }

// 返回字符串的长度
size_t rose::string::size() const { return _size; }

// 返回字符串的容量
size_t rose::string::capacity() const { return _capacity; }

// 返回指定位置的字符，可修改
char &rose::string::operator[](size_t pos) {
  assert(pos < _size);  // 检查位置是否越界
  return _str[pos];
}

// 返回指定位置的字符，不可修改
const char &rose::string::operator[](size_t pos) const {
  assert(pos < _size);  // 检查位置是否越界
  return _str[pos];
}

// 返回指向字符串开头的迭代器
rose::string::iterator rose::string::begin() { return _str; }

// 返回指向字符串结尾的迭代器
rose::string::iterator rose::string::end() { return _str + _size; }

// 返回指向字符串开头的常量迭代器
rose::string::const_iterator rose::string::begin() const { return _str; }

// 返回指向字符串结尾的常量迭代器
rose::string::const_iterator rose::string::end() const { return _str + _size; }

// 在字符串末尾添加一个字符
void rose::string::push_back(char ch) {
  if (_size == _capacity) {  // 如果空间不足，扩容
    reserve(_capacity == 0 ? 4 : 2 * _capacity);
  }
  _str[_size] = ch;  // 添加字符
  ++_size;
  _str[_size] = '\0';  // 添加字符串结束符
}

// 在字符串末尾添加C风格字符串
void rose::string::append(const char *str) {
  int len = strlen(str);
  if (_size + len > _capacity) {  // 如果空间不足，扩容
    reserve(_size + len);
  }
  memcpy(_str + _size, str, len + 1);  // 复制字符串内容
  _size += len;
}

// 预留至少n个字符的容量
void rose::string::reserve(size_t n) {
  if (n > _capacity) {             // 如果需要扩容
    char *tmp = new char[n + 1];   // 申请新内存
    memcpy(tmp, _str, _size + 1);  // 拷贝原有内容
    delete[] _str;                 // 释放旧内存
    _str = tmp;
    _capacity = n;  // 更新容量
  }
}

// 调整字符串大小，新位置用ch填充
void rose::string::resize(size_t n, char ch) {
  if (n < _size) {  // 如果新大小小于当前大小，截断字符串
    _size = n;
    _str[_size] = '\0';
  } else {  // 如果新大小大于当前大小，填充字符
    reserve(n);
    for (size_t i = _size; i < n; i++) {
      _str[i] = ch;
    }
    _size = n;
    _str[_size] = '\0';
  }
}

// 在字符串末尾添加一个字符
rose::string &rose::string::operator+=(char ch) {
  push_back(ch);
  return *this;
}

// 在字符串末尾添加C风格字符串
rose::string &rose::string::operator+=(const char *str) {
  append(str);
  return *this;
}

// 在字符串末尾添加另一个字符串
rose::string &rose::string::operator+=(const string &s) {
  append(s._str);
  return *this;
}

// 在指定位置插入n个字符ch
void rose::string::insert(size_t pos, size_t n, char ch) {
  assert(pos <= _size);         // 检查位置是否越界
  if (_size + n > _capacity) {  // 如果空间不足，扩容
    reserve(_size + n);
  }

  size_t end = _size;
  while (end >= pos && end != npos) {  // 移动字符
    _str[end + n] = _str[end];
    end--;
  }

  for (size_t i = 0; i < n; i++) {  // 插入字符
    _str[pos + i] = ch;
  }
  _size += n;
}

// 在指定位置插入C风格字符串
void rose::string::insert(size_t pos, const char *str) {
  assert(pos <= _size);  // 检查位置是否越界
  int len = strlen(str);
  if (_size + len > _capacity) {  // 如果空间不足，扩容
    reserve(_size + len);
  }

  int end = _size;
  while (end >= pos && end != npos) {  // 移动字符
    _str[end + len] = _str[end];
    end--;
  }
  for (size_t i = 0; i < len; i++) {  // 插入字符串
    _str[pos + i] = str[i];
  }
  _size += len;
}

// 删除从指定位置开始的len个字符
void rose::string::erase(size_t pos, size_t len) {
  assert(pos <= _size);                    // 检查位置是否越界
  if (len == npos || pos + len > _size) {  // 如果需要删除到末尾
    _str[pos] = '\0';
    _size = pos;
  } else {  // 如果需要删除部分字符
    size_t end = pos + len;
    while (end <= _size) {  // 移动字符
      _str[pos++] = _str[end++];
    }
    _size -= len;
  }
}

// 查找字符ch，返回第一个匹配的位置
size_t rose::string::find(char ch, size_t pos) {
  assert(pos < _size);  // 检查位置是否越界
  for (int i = pos; i < _size; i++) {
    if (ch == _str[i]) {  // 找到匹配字符
      return i;
    }
  }
  return npos;  // 未找到
}

// 查找子串str，返回第一个匹配的位置
size_t rose::string::find(const char *str, size_t pos) {
  assert(pos < _size);                        // 检查位置是否越界
  const char *ptr = strstr(_str + pos, str);  // 使用strstr查找子串
  if (ptr) {
    return ptr - _str;  // 返回子串位置
  }
  return npos;  // 未找到
}

// 返回从pos开始，长度为len的子串
rose::string rose::string::substr(size_t pos, size_t len) {
  assert(pos < _size);  // 检查位置是否越界

  size_t n = len;
  if (len == npos || pos + len > _size) {  // 如果长度超出范围，调整长度
    n = _size - pos;
  }
  rose::string tmp;  // 创建临时字符串
  tmp.reserve(n);    // 预留足够的容量

  for (size_t i = pos; i < pos + n; i++) {  // 复制子串内容
    tmp += _str[i];
  }
  return tmp;
}

// 输出运算符重载，用于输出字符串
std::ostream &rose::operator<<(std::ostream &out, const string &s) {
  for (auto ch : s) {  // 遍历字符串中的每个字符
    out << ch;         // 输出字符
  }
  return out;
}

// 输入运算符重载，用于从输入流读取字符串
std::istream &rose::operator>>(std::istream &in, string &s) {
  s.clear();  // 清空当前字符串内容

  char ch = in.get();                // 读取第一个字符
  while (ch == ' ' || ch == '\n') {  // 跳过空白字符
    ch = in.get();
  }

  char buff[128] = {'\0'};  // 缓冲区，用于临时存储输入的字符
  size_t i = 0;

  while (ch != ' ' && ch != '\n') {  // 读取字符，直到遇到空白或换行
    buff[i++] = ch;
    if (i == 127) {  // 如果缓冲区满了，将其内容加入字符串
      buff[i] = '\0';
      s += buff;
      i = 0;
    }
    ch = in.get();
  }
  if (i != 0) {  // 如果缓冲区中还有未处理的内容，加入字符串
    buff[i] = '\0';
    s += buff;
  }
  return in;
}

// 从输入流读取一行字符串
std::istream &rose::getline(std::istream &in, string &s) {
  s.clear();  // 清空当前字符串内容
  char ch = in.get();
  while (ch != '\n') {  // 读取字符，直到遇到换行
    s += ch;
    ch = in.get();
  }
  return in;
}

// 清空字符串内容
void rose::string::clear() {
  _str[0] = '\0';  // 将第一个字符设为'\0'
  _size = 0;       // 设置为空字符串
}

// 判断字符串是否为空
bool rose::string::empty() const { return size() == 0; }

// 小于运算符
bool rose::string::operator<(const string &s) {
  int ret =
      memcmp(_str, s._str, _size < s._size ? _size : s._size);  // 比较字符串
  return ret == 0 ? _size < s._size : ret < 0;  // 如果相同，比较长度
}

// 等于运算符
bool rose::string::operator==(const string &s) {
  return _size == s._size &&
         memcmp(_str, s._str, _size) == 0;  // 比较字符串内容
}

// 小于等于运算符
bool rose::string::operator<=(const string &s) {
  return *this < s || *this == s;  // 小于或等于
}

// 大于运算符
bool rose::string::operator>(const string &s) {
  return !(*this <= s);  // 不小于等于
}

// 大于等于运算符
bool rose::string::operator>=(const string &s) {
  return !(*this < s);  // 不小于
}

// 不等于运算符
bool rose::string::operator!=(const string &s) {
  return !(*this == s);  // 不等于
}

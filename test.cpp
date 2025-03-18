#include <cassert>
#include <iostream>

#include "string.h"

int main() {
  // 测试构造函数和 c_str()
  std::cout << "Test 1: Constructor and c_str()" << std::endl;
  rose::string s1("Hello");
  std::cout << "s1: " << s1.c_str() << " (size: " << s1.size() << ")"
            << std::endl;

  rose::string s2(5, 'X');
  std::cout << "s2: " << s2.c_str() << " (size: " << s2.size() << ")"
            << std::endl;

  rose::string s3;
  std::cout << "s3: " << s3.c_str() << " (size: " << s3.size() << ")"
            << std::endl;
  std::cout << std::endl;

  // 测试拷贝构造函数和拷贝赋值运算符
  std::cout << "Test 2: Copy constructor and copy assignment operator"
            << std::endl;
  rose::string s4 = s1;
  std::cout << "s4 (copy of s1): " << s4.c_str() << " (size: " << s4.size()
            << ")" << std::endl;

  rose::string s5;
  s5 = s2;
  std::cout << "s5 (assigned from s2): " << s5.c_str()
            << " (size: " << s5.size() << ")" << std::endl;
  std::cout << std::endl;

  // 测试移动构造函数和移动赋值运算符
  std::cout << "Test 3: Move constructor and move assignment operator"
            << std::endl;
  rose::string s6 = std::move(s1);
  std::cout << "s6 (moved from s1): " << s6.c_str() << " (size: " << s6.size()
            << ")" << std::endl;

  rose::string s7;
  s7 = std::move(s2);
  std::cout << "s7 (moved from s2): " << s7.c_str() << " (size: " << s7.size()
            << ")" << std::endl;
  std::cout << std::endl;

  // 测试 push_back 和 append
  std::cout << "Test 4: push_back and append" << std::endl;
  s6.push_back(' ');
  s6.append("World");
  std::cout << "s6 (after push_back and append): " << s6.c_str()
            << " (size: " << s6.size() << ")" << std::endl;

  s7 += "!!!";
  std::cout << "s7 (after operator+=): " << s7.c_str()
            << " (size: " << s7.size() << ")" << std::endl;
  std::cout << std::endl;

  // 测试 insert
  std::cout << "Test 5: insert" << std::endl;
  s6.insert(5, 3, '#');
  std::cout << "s6 (after insert(5,3,'#')): " << s6.c_str()
            << " (size: " << s6.size() << ")" << std::endl;

  s6.insert(0, "Prefix ");
  std::cout << "s6 (after insert(0,\"Prefix \")): " << s6.c_str()
            << " (size: " << s6.size() << ")" << std::endl;
  std::cout << std::endl;

  // 测试 erase
  std::cout << "Test 6: erase" << std::endl;
  s6.erase(0, 7);
  std::cout << "s6 (after erase(0,7)): " << s6.c_str()
            << " (size: " << s6.size() << ")" << std::endl;

  s6.erase(5, 3);
  std::cout << "s6 (after erase(5,3)): " << s6.c_str()
            << " (size: " << s6.size() << ")" << std::endl;
  std::cout << std::endl;

  // 测试 find
  std::cout << "Test 7: find" << std::endl;
  size_t pos = s6.find("World");
  std::cout << "s6.find(\"World\"): " << pos << std::endl;

  pos = s6.find("Universe");
  std::cout << "s6.find(\"Universe\"): " << pos << " (not found)" << std::endl;
  std::cout << std::endl;

  // 测试 substr
  std::cout << "Test 8: substr" << std::endl;
  rose::string substr = s6.substr(6, 5);
  std::cout << "s6.substr(6,5): " << substr.c_str()
            << " (size: " << substr.size() << ")" << std::endl;
  std::cout << std::endl;

  // 测试比较运算符
  std::cout << "Test 9: comparison operators" << std::endl;
  std::cout << "s6 == s7: " << (s6 == s7) << std::endl;
  std::cout << "s6 != s7: " << (s6 != s7) << std::endl;
  std::cout << "s6 < s7: " << (s6 < s7) << std::endl;
  std::cout << "s6 > s7: " << (s6 > s7) << std::endl;
  std::cout << "s6 <= s7: " << (s6 <= s7) << std::endl;
  std::cout << "s6 >= s7: " << (s6 >= s7) << std::endl;
  std::cout << std::endl;

  // 测试输入输出流
  std::cout << "Test 10: input and output streams" << std::endl;
  rose::string s8;
  std::cout << "Enter a string: ";
  std::cin >> s8;
  std::cout << "You entered: " << s8 << " (size: " << s8.size() << ")"
            << std::endl;

  rose::string s9;
  std::cout << "Enter a line of text: ";
  rose::getline(std::cin, s9);
  std::cout << "You entered: " << s9 << " (size: " << s9.size() << ")"
            << std::endl;
  std::cout << std::endl;

  // 测试 clear 和 empty
  std::cout << "Test 11: clear and empty" << std::endl;
  s9.clear();
  std::cout << "s9 (after clear): " << s9.c_str() << " (size: " << s9.size()
            << ")" << std::endl;
  std::cout << "s9.empty(): " << s9.empty() << std::endl;
  std::cout << std::endl;

  // 测试析构函数（通过作用域退出验证）
  std::cout
      << "Test 12: Destructor (implicitly called when objects go out of scope)"
      << std::endl;
  {
    rose::string s10("Temporary string");
    std::cout << "s10: " << s10.c_str() << " (size: " << s10.size() << ")"
              << std::endl;
  }
  std::cout << "s10 has been destructed." << std::endl;

  return 0;
}

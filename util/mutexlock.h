// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef STORAGE_LEVELDB_UTIL_MUTEXLOCK_H_
#define STORAGE_LEVELDB_UTIL_MUTEXLOCK_H_

#include "port/port.h"
#include "port/thread_annotations.h"

namespace leveldb {

// Helper class that locks a mutex on construction and unlocks the mutex when
// the destructor of the MutexLock object is invoked.
//
// Typical usage:
//
//   void MyClass::MyMethod() {
//     MutexLock l(&mu_);       // mu_ is an instance variable
//     ... some complex code, possibly with multiple return paths ...
//   }

class SCOPED_LOCKABLE MutexLock {
 public:
  //构造函数
  explicit MutexLock(port::Mutex* mu) EXCLUSIVE_LOCK_FUNCTION(mu) : mu_(mu) {
    this->mu_->Lock();
  }
  //析构函数
  ~MutexLock() UNLOCK_FUNCTION() { this->mu_->Unlock(); }
  //拷贝构造函数
  MutexLock(const MutexLock&) = delete;
  //拷贝赋值运算符
  MutexLock& operator=(const MutexLock&) = delete;

 private:
  port::Mutex* const mu_;
};
/*
explicit 禁止编译器执行非预期 (往往也不被期望) 的类型转换
*/

/*
https://www.cnblogs.com/lsgxeva/p/7787438.html
C++ 的类有四类特殊成员函数，它们分别是：默认构造函数、析构函数、拷贝构造函数以及拷贝赋值运算符。
=default  
  C++11 标准引入了一个新特性："=default"函数。程序员只需在函数声明后加上“=default;”，
  就可将该函数声明为 "=default"函数，编译器将为显式声明的 "=default"函数自动生成函数体。
  该函数比用户自己定义的默认构造函数获得更高的代码效率
=delete 
  为了能够让程序员显式的禁用某个函数，C++11 标准引入了一个新特性："=delete"函数。
  程序员只需在函数声明后上“=delete;”，就可将该函数禁用。
*/


}  // namespace leveldb

#endif  // STORAGE_LEVELDB_UTIL_MUTEXLOCK_H_

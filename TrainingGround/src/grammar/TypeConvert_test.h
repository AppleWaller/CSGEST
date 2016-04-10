#if defined(_MSC_VER)
#pragma once
#else
_Pragma("once")
#endif

#include "inc.h"
#include <string>

NS_BEGIN(elloop);

class Convertable {
public:
  explicit Convertable(int i=0) : i_(i) {}

  // ע�������������

  // 1. ����()������
  int operator() () { return i_; }

  // 2. ����ת��������
  explicit operator double() {
    return i_;
  }

  int i_;
};

NS_END(elloop);

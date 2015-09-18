#include "ClassTest.h"
#include "gtest/gtest.h"

NS_BEGIN(elloop);
NS_BEGIN(class_test)

TEST(ClassTest, Const) {
    pcln("ClassTest ---> Const");

    // ����Ĵ���չʾ�ˣ����ض����ڲ�ָ���Ա��Σ���ԡ�

    A       a;
    int*    pa = a.a();
    EXPECT_EQ(*pa, 10);
    //delete a.a();     // crash�� because in ~A() will delete a_ again.

    // ��ʹ��ʹ��const���͵�ָ�룬Ҳ��ֹ���˶Է��ص�ָ�����delete����
    int* const pca = a.a();
    //delete pca;       // crash!


}

NS_END(class_test)
NS_END(elloop);
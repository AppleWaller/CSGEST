#include "gtest/gtest.h"
#include "struct_array.h"

NS_BEGIN(elloop);

BEGIN_TEST(StructArrayTest, SingleStructInit, @)
pcln("StructArrayTest -------------> SingleStructInit");

auto printSimple = [](const Simple& s)
{
    LOGD("simple: (%d, %d)\n", s.x, s.y);
};

// ����ṹ���������ַ�ʽ���Ƽ��ڶ��֣���ʽָ���ֶ�����
Simple s1 = { 1, 2 };
printSimple(s1);

Simple s2 = { s2.x = 1, s2.y = 2 };
printSimple(s2);

auto printCombo = [](const Combo& c)
{
    LOGD("combo: (%d, %d; %d)\n", c.sim.x, c.sim.y, c.z);
};

// ���нṹ���Ա�Ľṹ��ĳ�ʼ��

Combo   c1 = { {1, 2}, 3 };
printCombo(c1);

Combo   c2 = { { 1, 2 }, c2.z = 3 };
printCombo(c2);
END_TEST


BEGIN_TEST(StructArrayTest, StructArrayInit, @)
pcln("StructArrayTest -------------> StructArrayInit");

auto printSimple = [](const Simple& s)
{
    LOGD("simple: (%d, %d)\n", s.x, s.y);
};

auto printCombo = [](const Combo& c)
{
    LOGD("combo: (%d, %d; %d)\n", c.sim.x, c.sim.y, c.z);
};

// �ڽṹ��ֻ��Ĭ�ϵĹ��캯��ʱ���ڳ�ʼ���ṹ������ʱ��
// ÿ������Ԫ�صĳ�ʼ����Ҫֵ�ĸ������ڸýṹ��ĳ�Ա��������
// ��Simple�Ķ�����Կ�������������int��ɣ������Ҫ����ֵ����ʼ��һ������Ԫ��
Simple  s1[] = {
    1, 2,
    3, 4,
};
size_t  len = ARRAY_LEN(s1);
EXPECT_EQ(2, len);
for (size_t i = 0; i < len; ++i)
{
    printSimple(s1[i]);
}
// or use {}. s1 is the same with s2.
Simple  s2[] = {
    { 1, 2 },
    { 3, 4 }
};
len = ARRAY_LEN(s2);
EXPECT_EQ(2, len);

Simple  s3[] = {
    1, 2, 3
};
len = ARRAY_LEN(s3);
EXPECT_EQ(2, len);
EXPECT_TRUE(3 == s3[1].x);
EXPECT_TRUE(0 == s3[1].y);

pcln("combo struct");

// �����͵Ľṹ��Ҳ��һ���������û���Զ��幹�캯������ô�ڳ�ʼ���ṹ������ʱ
// ÿ������Ԫ����Ҫ��ֵ�ĸ������ڸýṹ��ÿ����Ա��ʼ������ĸ���֮�ͣ�
// simple��Ҫ������ Combo�ĵ�����������Ҫһ�������г�ʼ��һ��Combo����Ԫ����Ҫ
// ����ֵ��
Combo   c1[] = {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
};
len = ARRAY_LEN(c1);
EXPECT_EQ(3, len);
// ���ߣ�
Combo   c2[] = {
    { 1, 2, 3 },
    { 4, 5, 6 },
    { 7, 8, 9 }
};
len = ARRAY_LEN(c2);
EXPECT_EQ(3, len);
// ���ߣ�
Combo   c3[] = {
    { { 1, 2 }, 3 },
    { { 4, 5 }, 6 },
    { { 7, 8 }, 9 },
};
len = ARRAY_LEN(c2);
EXPECT_EQ(3, len);
for (size_t i = 0; i < len; ++i)
{
    printCombo(c3[i]);
}

// ע�⣺���Ķ���ʼ���ṹ������Ĵ���ʱ�����԰�һ��˳������ִ��룺
// ��c3����ĳ�ʼ��Ϊ����
//  Combo   c3[] = {
//      { { 1, 2 }, 3 },
//      { { 4, 5 }, 6 },
//      { { 7, 8 }, 9 },
//  };
// ���ȴӵȺ��ұ߿����ұ���������һ�Դ����ţ������������Ҫ��
// �����������Ĵ�����֮�󣬿�������Զ��ŷָ��ĵ�Ԫ��ʲô�����������������
// 1) ÿ����Ԫ��һ�Դ�����(c3�ĳ�ʼ������)��
//      ��ô�������������ĵ�Ԫ�ĸ����������������Ԫ�صĸ�����
//      ÿ����Ԫ��չ����ȥ�����˵Ĵ����ţ�������ĵ�Ԫȥ��ʼ��һ���ṹ��Ԫ�أ�
//      �������Ԫ�ؿ��ܻ����Զ��ŷָ��ĵ�Ԫ�����ݽṹ��Ľṹ�����ж�Ӧ��ƥ��
//      ���ɡ�ÿ���ӵ�ԪҲ���ܻ����ֵ����������������ʱȱ�ٵ�ֵ�������ΪĬ��ֵ
// 2) ÿ����Ԫֱ����ֵ��
//      ȡ����ÿ���ṹ����Ҫ��ֵ�ĸ���n������Ԫ�ظ���=ceil(��Ԫ��/n), ���Ľ�
//      ��������ò����㹻��ֵ����ʼ�����������ʼ��Ϊ0;

// ����������ӣ�c4 ������3��Ԫ�أ���Ϊ�Ⱥ��ұߵĻ��������棬������������ӵ�Ԫ��
// ��һ��Ԫ��Combo �� { { }�� 3} ����ʼ���� simple������ʼ��Ϊ��0��0����z������ʼ��Ϊ
// 3
// �ڶ���Ԫ��Combo: { {4, }, 6 } ����ʼ���� simple��4,0), z = 6
// ������Ԫ��Combo: { {7, 8}, 9} ����ʼ���� simple(7, 8), z = 9
Combo   c4[] = {
    { {}, 3 },
    { { 4, }, 6 },
    { { 7, 8 }, 9 },
};
len = ARRAY_LEN(c4);
EXPECT_EQ(3, len);
EXPECT_TRUE(0 == c4[0].sim.x);
EXPECT_TRUE(0 == c4[0].sim.y);
EXPECT_TRUE(3 == c4[0].z);

EXPECT_TRUE(4 == c4[1].sim.x);
EXPECT_TRUE(0 == c4[1].sim.y);
EXPECT_TRUE(6 == c4[1].z);

END_TEST;




NS_END(elloop);




NS_BEGIN(from_opengl_test);

#define LEN(x) sizeof x / sizeof x[0]

template <typename T>
struct vec2
{
    typedef T       value_type;

    value_type      x;
    value_type      y;

    template <typename U>
    vec2(const U & u) : x(u), y(u)
    {}

    template <typename U, typename V>
    vec2(const U& u, const V& v) :
        x(u), y(v)
    {}
};

template <typename T>
struct color
{
    typedef T       value_type;

    value_type      r;
    value_type      g;
    value_type      b;

    /*color(value_type r1, value_type g1, value_type b1) :
        r(r1), g(g1), b(b1)
        {
        }*/
};


struct RawColor
{
    int     r;
    int     g;
    int     b;
};

struct Compo
{
    vec2<float> pos;
    color<int>  color;
};




BEGIN_TEST(StructArrayTest, FromOpenGLTest, @)
typedef vec2<float> float2;

vec2<float> f = { 10 };

vec2<float> ary[2] = { { 10, 11 }, { 1, 0 } };
//vec2<float> ary2[] = { 10, 11 };

float2 fs1[] = {
    1, 2,
    3, 4,
    5, 6,
    7, 8
};
size_t len1 = LEN(fs1);
for (size_t i = 0; i < len1; ++i)
{
    float2 temp = fs1[i];
}

float2 fs2[] = {
    { 1, 2 },
    { 3, 4 },
    { 5, 6 },
    { 7, 8 }
};
len1 = LEN(fs2);
for (size_t i = 0; i < len1; ++i)
{
    float2 t = fs2[i];
}

typedef color<int> colori;
colori cs1[] = {
    { 1, 2, 3 },
    { 4, 5, 6 },
    { 7, 8, 9 }
};
len1 = LEN(cs1);
for (size_t i = 0; i < len1; ++i)
{
    colori temp = cs1[i];
}

colori cs2[] = {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
};
len1 = LEN(cs2);
for (size_t i = 0; i < len1; ++i)
{
    colori t = cs2[i];
}


RawColor rcs1[] = {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
};

len1 = LEN(rcs1);
for (size_t i = 0; i < len1; ++i)
{
    RawColor t = rcs1[i];
}


Compo compos[] = {
    { 1, 2 }, { 1, 1, 1 },
    { 11, 22 }, { 11, 12, 13 }
};

END_TEST



NS_END(from_opengl_test);

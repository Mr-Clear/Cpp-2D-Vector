/* Build with: gcc -std=c++17 -lstdc++ -lm -lgtest Test.cpp */

#include <gtest/gtest.h>

#include <iostream>

#include "Vector2.h"

using Vector2d = Vector2<double>;
using Vector2i = Vector2<int>;

template <typename T>
inline void PrintTo(const Vector2<T> &v, ::std::ostream *os)
{
    *os << '(' << v.x() << ", " << v.y() << ')';
}

TEST(Vector2, DefaultConstructors)
{
    const Vector2d vd{};
    EXPECT_EQ(0.0, vd.x());
    EXPECT_EQ(0.0, vd.y());
    const Vector2i vi{};
    EXPECT_EQ(0, vi.x());
    EXPECT_EQ(0, vi.y());
}

TEST(Vector2, ConstexprGetter)
{
    constexpr Vector2i a{1, 2};
    static_assert(1 == a.x());
    static_assert(2 == a.y());
}

TEST(Vector2, InitConstructors)
{
    const Vector2d vd{2.3, 5.7};
    EXPECT_EQ(2.3, vd.x());
    EXPECT_EQ(5.7, vd.y());
    const Vector2i vi{11, 13};
    EXPECT_EQ(11, vi.x());
    EXPECT_EQ(13, vi.y());
}

TEST(Vector2, CopyConstructors)
{
    constexpr Vector2d a{2.3, 5.7};
    constexpr Vector2d b{a};
    EXPECT_EQ(2.3, b.x());
    EXPECT_EQ(5.7, b.y());
    static_assert(2.3 == b.x());
    static_assert(5.7 == b.y());
}

TEST(Vector2, OperatorEquals)
{
    const Vector2i a{1, 2};
    const Vector2i b{2, 1};
    EXPECT_EQ(a, a);
    EXPECT_NE(a, b);

    constexpr Vector2i c{1, 2};
    static_assert(c == Vector2i(1, 2));
    static_assert(c != Vector2i(2, 1));
}

TEST(Vector2, Cast)
{
    EXPECT_EQ(Vector2d(4, 5), static_cast<Vector2d>(Vector2i(4, 5)));
    EXPECT_EQ(Vector2i(4, 5), static_cast<Vector2i>(Vector2d(4, 5)));
    EXPECT_EQ(Vector2i(4, 5), static_cast<Vector2i>(Vector2d(4.4, 4.6)));
    EXPECT_EQ(Vector2<float>(4.4, 4.6), static_cast<Vector2<float>>(Vector2d(4.4, 4.6)));
    static_assert(Vector2<float>(4.4, 4.6) == static_cast<Vector2<float>>(Vector2d(4.4, 4.6)));
}

TEST(Vector2, Setter)
{
    Vector2i a{1, 2};
    a.setX(2);
    a.setY(1);
    EXPECT_EQ(Vector2i(2, 1), a);
    a.set(3, 4);
    EXPECT_EQ(Vector2i(3, 4), a);
}

TEST(Vector2, SetterCascade)
{
    Vector2i a{1, 2};
    a.setX(2).setY(1);
    EXPECT_EQ(Vector2i(2, 1), a);
    Vector2i b = a.set(3, 4);
    EXPECT_EQ(Vector2i(3, 4), a);
    EXPECT_EQ(Vector2i(3, 4), b);

    const Vector2i c = Vector2i(5, 6).set(7, 8);
    EXPECT_EQ(Vector2i(7, 8), c);
}

TEST(Vector2, Assignment)
{
    Vector2i a{1, 2};
    a = Vector2i{3, 4};
    EXPECT_EQ(Vector2i(3, 4), a);
    Vector2i b = a = Vector2i{5, 6};
    EXPECT_EQ(a, b);
}

TEST(Vector2, Add)
{
    EXPECT_EQ(Vector2i(4, 6), Vector2i(1, 2) + Vector2i(3, 4));
    static_assert(Vector2i(4, 6) == Vector2i(1, 2) + Vector2i(3, 4));
}

TEST(Vector2, Substract)
{
    EXPECT_EQ(Vector2i(-2, -3), Vector2i(1, 2) - Vector2i(3, 5));
    static_assert(Vector2i(-2, -3) == Vector2i(1, 2) - Vector2i(3, 5));
}

TEST(Vector2, ScalarMultiplication)
{
    EXPECT_EQ(Vector2i(4, 8), Vector2i(1, 2) * 4);
    static_assert(Vector2i(4, 8) == Vector2i(1, 2) * 4);
}

TEST(Vector2, ScalarDivision)
{
    EXPECT_EQ(Vector2i(2, 3), Vector2i(6, 9) / 3);
    static_assert(Vector2i(2, 3) == Vector2i(6, 9) / 3);
}

TEST(Vector2, DotProduct)
{
    EXPECT_EQ(33, Vector2i(7, 2) * Vector2i(3, 6));
    static_assert(33 == Vector2i(7, 2) * Vector2i(3, 6));
}

TEST(Vector2, AddAssign)
{
    Vector2i a{8, 5};
    const Vector2i b = a += Vector2i{-3, 1};
    EXPECT_EQ(Vector2i(5, 6), a);
    EXPECT_EQ(a, b);
}

TEST(Vector2, SubstractAssign)
{
    Vector2i a{8, 5};
    const Vector2i b = a -= Vector2i{3, 1};
    EXPECT_EQ(Vector2i(5, 4), a);
    EXPECT_EQ(a, b);
}

TEST(Vector2, ScalarMultiplicationAssign)
{
    Vector2i a{1, 2};
    const Vector2i b = a *= 5;
    EXPECT_EQ(Vector2i(5, 10), a);
    EXPECT_EQ(a, b);
}

TEST(Vector2, ScalarDivisionAssign)
{
    Vector2i a{15, 20};
    const Vector2i b = a /= 5;
    EXPECT_EQ(Vector2i(3, 4), a);
    EXPECT_EQ(a, b);
}

TEST(Vector2, Negate)
{
    EXPECT_EQ(Vector2i(-3, -4), -Vector2i(3, 4));
    static_assert(Vector2i(-3, -4) == -Vector2i(3, 4));
}

TEST(Vector2, Flip)
{
    EXPECT_EQ(Vector2i(4, 3), ~Vector2i(3, 4));
    static_assert(Vector2i(4, 3) == ~Vector2i(3, 4));
}

TEST(Vector2, Length)
{
    EXPECT_EQ(5, Vector2i(3, 4).length());
    static_assert(5 == Vector2i(3, 4).length());
}

TEST(Vector2, Normalized)
{
    EXPECT_EQ(Vector2d(3. / 5, 4. / 5), Vector2d(3, 4).normalized());
    static_assert(Vector2d(3. / 5, 4. / 5) == Vector2d(3, 4).normalized());
}

TEST(Vector2, Normalize)
{
    Vector2d v{3, 4};
    v.normalize();
    EXPECT_EQ(Vector2d(3. / 5, 4. / 5), v);
}

TEST(Vector2, Direction)
{
    EXPECT_EQ(0, Vector2i(1, 0).direction());
    EXPECT_EQ(M_PI / 2, Vector2i(0, 1).direction());
    EXPECT_EQ(M_PI, Vector2i(-1, 0).direction());
    EXPECT_EQ(-M_PI * 3 / 4, Vector2d(-1, -1).direction());
    static_assert(-M_PI * 3 / 4 == Vector2d(-1, -1).direction());
}

TEST(Vector2, Rotated)
{
    EXPECT_EQ(Vector2i(-3, 10), Vector2i(10, 3).rotated(M_PI / 2));
    const auto r = Vector2d(3, 4).rotated(-M_PI / 2);
    EXPECT_DOUBLE_EQ(4, r.x());
    EXPECT_DOUBLE_EQ(-3, r.y());
    static_assert(Vector2i(-3, 10) == Vector2i(10, 3).rotated(M_PI / 2));
}

TEST(Vector2, Rotate)
{
    auto r = Vector2d(3, 4);
    r.rotate(-M_PI / 2);
    EXPECT_DOUBLE_EQ(4, r.x());
    EXPECT_DOUBLE_EQ(-3, r.y());
    static_assert(Vector2i(-3, 10) == Vector2i(10, 3).rotate(M_PI / 2));
}

TEST(Vector2, FromDirLen)
{
    EXPECT_EQ(Vector2i(0, 5), Vector2i::fromDirLen(M_PI / 2, 5));
    static_assert(Vector2i(0, 5) == Vector2i::fromDirLen(M_PI / 2, 5));
    EXPECT_EQ(Vector2i(3, 4), Vector2i::fromDirLen(1, 5));
}

TEST(Vector2, Defaults)
{
    static_assert(Vector2i::X() == Vector2i(1, 0));
    static_assert(Vector2i::Y() == Vector2i(0, 1));
    static_assert(Vector2i::ZERO() == Vector2i(0, 0));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

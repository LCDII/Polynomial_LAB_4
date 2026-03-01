#include <gtest.h>

#include"Polynomial.h"

TEST(Polynom, can_create_polynom)
{
	ASSERT_NO_THROW(Polynomial());
}
TEST(Polynom, can_solve)
{
	Polynomial p;
	ASSERT_NO_THROW(p.solve(1,1,1));
}
TEST(Polynom, solves_correctly)
{
	Monom m(1, 1, 2, 3);
	Monom m1(1, 1, 2, 3);
	Polynomial p;
	p = p + m;
	p = p + m1;
	EXPECT_EQ(128, p.solve(2, 2, 2));
}
TEST(Polynom, can_add_polynoms)
{
	Polynomial p;
	Polynomial p1;
	ASSERT_NO_THROW(p + p1);
}
TEST(Polynom, can_sub_polynoms)
{
	Polynomial p;
	Polynomial p1;
	ASSERT_NO_THROW(p - p1);
}
TEST(Polynom, can_multiply_polynoms)
{
	Polynomial p;
	Polynomial p1;
	ASSERT_NO_THROW(p * p1);
}
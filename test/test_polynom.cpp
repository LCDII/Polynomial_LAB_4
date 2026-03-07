#include <gtest/gtest.h>

#include"Polynomial.h"
#include<string>
using namespace std;

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
TEST(Polynom, can_interpretate_string)
{
	string s = "2.2x^2y^3 + x^-2y^3 - 4z^5 + 5";
	ASSERT_NO_THROW(Polynomial(s));
}
TEST(Polynom, can_interpretate_monom)
{
	string s = "x^2y^3";
	Polynomial p(s);
	EXPECT_EQ(p.solve(1, 2, 3), 8);
}
TEST(Polynom, can_interpretate_number)
{
	string s = "5";
	Polynomial p(s);
	EXPECT_EQ(p.solve(1, 2, 3), 5);
}
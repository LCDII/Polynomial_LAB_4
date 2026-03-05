#include <gtest/gtest.h>

#include"Monom.h"

TEST(Monom, can_create_monom_with_correct_power_gap)
{
	ASSERT_NO_THROW(Monom(1, -5, 10, 3));
}
TEST(Monom, cant_create_monom_with_incorrect_power_gap)
{
	ASSERT_ANY_THROW(Monom(1, -5, 15, 3));
}
TEST(Monom, can_create_monom_with_no_powers)
{
	ASSERT_NO_THROW(Monom(45));
}
TEST(Monom, can_solve)
{
	Monom m(1, -5, 10, 3);
	ASSERT_NO_THROW(m.solve(1, 1, 1));
}
TEST(Monom, solves_correctly)
{
	Monom m(1, 1, 2, 3);
	EXPECT_EQ(64, m.solve(2, 2, 2));
}
TEST(Monom, can_be_nullified)
{
	Monom m(0.00000000000000000000001, 1, 2, 3);
	EXPECT_EQ(true, m.isNull());
}
TEST(Monom, can_add_monoms_with_same_powers)
{
	Monom m(1, 1, 2, 3);
	Monom m1(1, 1, 2, 3);
	ASSERT_NO_THROW(m + m1);
}
TEST(Monom, can_sub_monoms_with_same_powers)
{
	Monom m(1, 1, 2, 3);
	Monom m1(1, 1, 2, 3);
	ASSERT_NO_THROW(m - m1);
}
TEST(Monom, can_multiply_monoms)
{
	Monom m(1, 1, 2, 3);
	Monom m1(1, 1, 2, 3);
	ASSERT_NO_THROW(m * m1);
}
TEST(Monom, compare_equal_monoms_return_true)
{
	Monom m(1, 1, 2, 3);
	Monom m1(1, 1, 2, 3);
	EXPECT_EQ(true ,m == m1);
}
TEST(Monom, compare_not_equal_monoms_return_false)
{
	Monom m(1, 1, 2, 3);
	Monom m1(1, 2, 2, 3);
	EXPECT_EQ(false, m == m1);
}

#include <gtest/gtest.h>
#include "../Common/Employee.h"
#include <cstring>

TEST(EmployeeTest, DefaultValues)
{
    Employee e{};
    EXPECT_EQ(e.num, 0);
    EXPECT_DOUBLE_EQ(e.hours, 0.0);
}

TEST(EmployeeTest, NameCopy)
{
    Employee e{};
    std::strncpy(e.name, "Ivan", sizeof(e.name));
    EXPECT_STREQ(e.name, "Ivan");
}

TEST(EmployeeTest, StructSizeStable)
{
    EXPECT_EQ(sizeof(Employee), sizeof(int) + 10 + sizeof(double));
}

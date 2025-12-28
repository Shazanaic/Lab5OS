#include <gtest/gtest.h>
#include "../Server/FileStorage.h"
#include <cstdio>

class FileStorageTest : public ::testing::Test
{
protected:
    const std::string file = "test.bin";

    void TearDown() override
    {
        std::remove(file.c_str());
    }
};

TEST_F(FileStorageTest, CreateAndReadAll)
{
    FileStorage fs(file);

    std::vector<Employee> employees = {
        {1, "A", 10.5},
        {2, "B", 20.0}
    };

    fs.create(employees);
    auto result = fs.readAll();

    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].num, 1);
    EXPECT_EQ(result[1].num, 2);
}

TEST_F(FileStorageTest, ReadById)
{
    FileStorage fs(file);

    Employee e{ 1, "Alex", 40 };
    fs.create({ e });

    Employee out{};
    EXPECT_TRUE(fs.readById(1, out));
    EXPECT_EQ(out.num, 1);
    EXPECT_DOUBLE_EQ(out.hours, 40);
}

TEST_F(FileStorageTest, WriteById)
{
    FileStorage fs(file);
    fs.create({ {1, "Old", 5} });

    Employee updated{ 1, "New", 100 };
    EXPECT_TRUE(fs.writeById(1, updated));

    Employee out{};
    fs.readById(1, out);
    EXPECT_STREQ(out.name, "New");
    EXPECT_DOUBLE_EQ(out.hours, 100);
}

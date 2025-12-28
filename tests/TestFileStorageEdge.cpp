#include <gtest/gtest.h>
#include "../Server/FileStorage.h"
#include <cstdio>

TEST(FileStorageEdgeTest, ReadFromEmptyFile)
{
    FileStorage fs("empty.bin");
    std::vector<Employee> result = fs.readAll();
    EXPECT_TRUE(result.empty());
    std::remove("empty.bin");
}

TEST(FileStorageEdgeTest, ReadNonExistingId)
{
    FileStorage fs("edge.bin");
    fs.create({ {1, "A", 1} });

    Employee out{};
    EXPECT_FALSE(fs.readById(999, out));
    std::remove("edge.bin");
}

TEST(FileStorageEdgeTest, WriteNonExistingId)
{
    FileStorage fs("edge2.bin");
    fs.create({ {1, "A", 1} });

    Employee e{ 5, "X", 10 };
    EXPECT_FALSE(fs.writeById(5, e));
    std::remove("edge2.bin");
}

#include <gtest/gtest.h>
#include "../Server/RecordLockManager.h"
#include <thread>
#include <vector>
#include <atomic>

TEST(RecordLockManagerConcurrency, MultipleReaders)
{
    RecordLockManager mgr;
    std::atomic<int> counter{ 0 };

    auto reader = [&]()
        {
            mgr.lockRead(1);
            counter++;
            mgr.unlockRead(1);
        };

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
        threads.emplace_back(reader);

    for (auto& t : threads)
        t.join();

    EXPECT_EQ(counter, 10);
}

TEST(RecordLockManagerConcurrency, WriterBlocksReaders)
{
    RecordLockManager mgr;
    std::atomic<bool> writerEntered{ false };

    std::thread writer([&]()
        {
            mgr.lockWrite(1);
            writerEntered = true;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            mgr.unlockWrite(1);
        });

    std::thread reader([&]()
        {
            while (!writerEntered) {}
            mgr.lockRead(1);
            mgr.unlockRead(1);
        });

    writer.join();
    reader.join();

    SUCCEED();
}

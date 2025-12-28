#include <gtest/gtest.h>
#include "../Server/RecordLockManager.h"
#include <thread>
#include <atomic>

TEST(RecordLockManagerTest, SingleThreadReadWrite)
{
    RecordLockManager mgr;

    mgr.lockRead(1);
    mgr.unlockRead(1);

    mgr.lockWrite(1);
    mgr.unlockWrite(1);

    SUCCEED();
}

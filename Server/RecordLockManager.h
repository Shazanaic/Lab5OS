#pragma once
#include <unordered_map>
#include <shared_mutex>

class RecordLockManager
{
public:
    void lockRead(int id);
    void unlockRead(int id);

    void lockWrite(int id);
    void unlockWrite(int id);

private:
    std::unordered_map<int, std::shared_mutex> m_locks;
};

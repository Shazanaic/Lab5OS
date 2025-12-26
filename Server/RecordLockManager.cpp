#include "RecordLockManager.h"

void RecordLockManager::lockRead(int id)
{
    m_locks[id].lock_shared();
}

void RecordLockManager::unlockRead(int id)
{
    m_locks[id].unlock_shared();
}

void RecordLockManager::lockWrite(int id)
{
    m_locks[id].lock();
}

void RecordLockManager::unlockWrite(int id)
{
    m_locks[id].unlock();
}

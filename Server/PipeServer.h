#pragma once
#include "../Common/PipeMessage.h"
#include "FileStorage.h"
#include "RecordLockManager.h"
#include <windows.h>

class PipeServer
{
public:
    PipeServer(FileStorage& storage, RecordLockManager& locks);
    void run();

private:
    void handleClient(HANDLE pipe);

    FileStorage& m_storage;
    RecordLockManager& m_locks;
};
#pragma once

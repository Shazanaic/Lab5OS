#pragma once
#include "../Common/PipeMessage.h"
#include <windows.h>

class PipeClient
{
public:
    PipeClient();
    ~PipeClient();

    PipeResponse send(const PipeRequest& req);

private:
    HANDLE m_pipe;
};

#include "PipeClient.h"

PipeClient::PipeClient()
{
    m_pipe = CreateFileA(
        "\\\\.\\pipe\\EmployeePipe",
        GENERIC_READ | GENERIC_WRITE,
        0, nullptr, OPEN_EXISTING, 0, nullptr);
}

PipeClient::~PipeClient()
{
    CloseHandle(m_pipe);
}

PipeResponse PipeClient::send(const PipeRequest& req)
{
    DWORD written, read;
    PipeResponse resp;

    WriteFile(m_pipe, &req, sizeof(req), &written, nullptr);
    ReadFile(m_pipe, &resp, sizeof(resp), &read, nullptr);

    return resp;
}

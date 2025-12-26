#include "PipeServer.h"
#include <thread>

PipeServer::PipeServer(FileStorage& storage, RecordLockManager& locks)
    : m_storage(storage), m_locks(locks) {
}

void PipeServer::run()
{
    while (true)
    {
        HANDLE pipe = CreateNamedPipeA(
            "\\\\.\\pipe\\EmployeePipe",
            PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            PIPE_UNLIMITED_INSTANCES,
            512, 512,
            0, nullptr);

        ConnectNamedPipe(pipe, nullptr);

        std::thread(&PipeServer::handleClient, this, pipe).detach();
    }
}

void PipeServer::handleClient(HANDLE pipe)
{
    PipeRequest req;
    DWORD readBytes;

    while (ReadFile(pipe, &req, sizeof(req), &readBytes, nullptr))
    {
        PipeResponse resp{};

        if (req.operation == OperationType::Read)
        {
            m_locks.lockRead(req.employeeId);
            if (m_storage.readById(req.employeeId, resp.data))
                resp.status = ResponseStatus::Ok;
            else
                resp.status = ResponseStatus::NotFound;
            m_locks.unlockRead(req.employeeId);
        }
        else if (req.operation == OperationType::Write)
        {
            m_locks.lockWrite(req.employeeId);
            m_storage.writeById(req.employeeId, req.data);
            resp.status = ResponseStatus::Ok;
            m_locks.unlockWrite(req.employeeId);
        }

        DWORD written;
        WriteFile(pipe, &resp, sizeof(resp), &written, nullptr);
    }

    CloseHandle(pipe);
}

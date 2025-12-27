#include "PipeClient.h"
#include <iostream>

int main()
{
    PipeClient client;

    while (true)
    {
        int cmd;
        std::cout << "1 - read, 2 - write, 0 - exit: ";
        std::cin >> cmd;

        if (cmd == 0) break;

        PipeRequest req{};
        std::cout << "ID: ";
        std::cin >> req.employeeId;

        if (cmd == 1)
        {
            req.operation = OperationType::Read;
            auto resp = client.send(req);
            if (resp.status == ResponseStatus::Ok)
                std::cout << resp.data.num << " " << resp.data.name << " " << resp.data.hours << "\n";
        }
        else if (cmd == 2)
        {
            req.operation = OperationType::Write;
            std::cin >> req.data.num >> req.data.name >> req.data.hours;
            client.send(req);
        }
    }
}

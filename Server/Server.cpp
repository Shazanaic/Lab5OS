#include "PipeServer.h"
#include <iostream>

int main()
{
    std::string fileName;
    std::cout << "Enter the filename: ";
    std::cin >> fileName;

    int n;
    std::cout << "Enter the number of employees: ";
    std::cin >> n;

    std::vector<Employee> employees(n);
    for (auto& e : employees)
        std::cin >> e.num >> e.name >> e.hours;

    FileStorage storage(fileName);
    storage.create(employees);

    RecordLockManager locks;
    PipeServer server(storage, locks);

    server.run();
}

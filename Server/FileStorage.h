#pragma once
#include "../Common/Employee.h"
#include <string>
#include <vector>

class FileStorage
{
public:
    explicit FileStorage(const std::string& fileName);

    void create(const std::vector<Employee>& employees);
    std::vector<Employee> readAll();

    bool readById(int id, Employee& out);
    bool writeById(int id, const Employee& emp);

private:
    std::string m_fileName;
};

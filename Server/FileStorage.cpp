#include "FileStorage.h"
#include <fstream>

FileStorage::FileStorage(const std::string& fileName)
    : m_fileName(fileName) {
}

void FileStorage::create(const std::vector<Employee>& employees)
{
    std::ofstream ofs(m_fileName, std::ios::binary | std::ios::trunc);
    for (const auto& e : employees)
        ofs.write(reinterpret_cast<const char*>(&e), sizeof(Employee));
}

std::vector<Employee> FileStorage::readAll()
{
    std::vector<Employee> result;
    std::ifstream ifs(m_fileName, std::ios::binary);

    Employee e;
    while (ifs.read(reinterpret_cast<char*>(&e), sizeof(Employee)))
        result.push_back(e);

    return result;
}

bool FileStorage::readById(int id, Employee& out)
{
    std::ifstream ifs(m_fileName, std::ios::binary);
    Employee e;

    while (ifs.read(reinterpret_cast<char*>(&e), sizeof(Employee)))
    {
        if (e.num == id)
        {
            out = e;
            return true;
        }
    }
    return false;
}

bool FileStorage::writeById(int id, const Employee& emp)
{
    std::fstream fs(m_fileName, std::ios::binary | std::ios::in | std::ios::out);
    Employee e;

    while (fs.read(reinterpret_cast<char*>(&e), sizeof(Employee)))
    {
        if (e.num == id)
        {
            fs.seekp(-static_cast<int>(sizeof(Employee)), std::ios::cur);
            fs.write(reinterpret_cast<const char*>(&emp), sizeof(Employee));
            return true;
        }
    }
    return false;
}

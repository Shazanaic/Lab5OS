#pragma once
#include <cstdint>

enum class OperationType : uint8_t
{
    Read = 1,
    Write = 2,
    Close = 3
};

enum class ResponseStatus : uint8_t
{
    Ok = 0,
    NotFound = 1,
    Locked = 2,
    Error = 3
};

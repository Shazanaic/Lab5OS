#pragma once
#include "Employee.h"
#include "Protocol.h"

struct PipeRequest
{
    OperationType operation;
    int employeeId;
    Employee data;
};

struct PipeResponse
{
    ResponseStatus status;
    Employee data;
};

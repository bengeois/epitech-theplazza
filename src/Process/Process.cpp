/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Process
*/

#include "Process/Process.hpp"
#include "Error/Error.hpp"

#include <signal.h>

using namespace Plazza;

Process::Process() : _pid(fork())
{
    if (_pid == -1)
        throw ProcessError("Fail to fork", "Process");
}

Process::~Process()
{
    if (!isAlive())
        return;
    if (kill(_pid, SIGKILL) == -1)
        ProcessError("Fail to kill process" + std::to_string(_pid), "Process");
}

Process::Process(const Process &process) : _pid(process._pid)
{
}

Process &Process::operator=(const Process &process)
{
    _pid = process._pid;
    return (*this);
}

pid_t Process::getPid() const
{
    return (_pid);
}

bool Process::isAlive() const
{
    if (kill(_pid, 0) == 0)
        return (true);
    return (false);
}

bool Process::isInChild() const
{
    return ((!_pid ? true : false));
}
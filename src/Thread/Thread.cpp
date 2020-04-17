/*
** EPITECH PROJECT, 2020
** Epitech_ThePlazza
** File description:
** TODO: add description
*/

#include "Thread/Thread.hpp"

using namespace Plazza;

Thread::Thread(const std::function<void()> &ft) : _thread(std::make_shared<std::thread>(ft))
{
}

Thread::~Thread()
{
    _thread->join();
}

void Thread::join()
{
    _thread->join();
}

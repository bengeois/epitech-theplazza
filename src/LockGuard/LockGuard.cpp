/*
** EPITECH PROJECT, 2020
** Epitech_ThePlazza
** File description:
** TODO: add description
*/

#include "LockGuard/LockGuard.hpp"

using namespace Plazza;

LockGuard::LockGuard(const std::shared_ptr<Mutex> &mutex) : _lock(mutex->getMutex())
{
}

LockGuard::~LockGuard() = default;

std::unique_lock<std::mutex> &LockGuard::getUniqueLock()
{
    return _lock;
}

/*
** EPITECH PROJECT, 2020
** Epitech_ThePlazza
** File description:
** TODO: add description
*/

#include "LockGuard/LockGuard.hpp"

Plazza::LockGuard::LockGuard(const std::shared_ptr<Mutex> &mutex) : _mutex(mutex)
{
    _mutex->lock();
}

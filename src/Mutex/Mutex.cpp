/*
** EPITECH PROJECT, 2020
** Epitech_ThePlazza
** File description:
** TODO: add description
*/

#include "Mutex/Mutex.hpp"

using namespace Plazza;

Mutex::Mutex() : _mutex(std::make_shared<std::mutex>())
{
}

Mutex::~Mutex()
{
    _mutex->unlock();
};

void Mutex::lock()
{
    _mutex->lock();
}

void Mutex::unlock()
{
    _mutex->unlock();
}

bool Mutex::trylock()
{
    return _mutex->try_lock();
}

std::mutex &Mutex::getMutex()
{
    return *_mutex;
}

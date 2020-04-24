/*
** EPITECH PROJECT, 2020
** Epitech_ThePlazza
** File description:
** TODO: add description
*/

#include "ConditionVariable/ConditionVariable.hpp"

using namespace Plazza;

ConditionVariable::ConditionVariable()
= default;

ConditionVariable::~ConditionVariable()
= default;

void ConditionVariable::notify_one()
{
    _cv.notify_one();
}

void ConditionVariable::notify_all()
{
    _cv.notify_all();
}

void ConditionVariable::wait(LockGuard &lock, std::function<bool()> ft)
{
    _cv.wait(lock.getUniqueLock(), ft);
}

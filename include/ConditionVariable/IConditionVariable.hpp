/*
** EPITECH PROJECT, 2020
** Epitech_ThePlazza
** File description:
** TODO: add description
*/

#ifndef EPITECH_THEPLAZZA_ICONDITIONVARIABLE_HPP
#define EPITECH_THEPLAZZA_ICONDITIONVARIABLE_HPP

#include <functional>
#include "LockGuard/LockGuard.hpp"

namespace Plazza
{
    class IConditionVariable
    {
        public:
            virtual ~IConditionVariable() = default;

            virtual void notify_one() = 0;
            virtual void notify_all() = 0;
            virtual void wait(LockGuard &lock, std::function<bool()> ft) = 0;
    };
}

#endif //EPITECH_THEPLAZZA_ICONDITIONVARIABLE_HPP

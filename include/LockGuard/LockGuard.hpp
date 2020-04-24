/*
** EPITECH PROJECT, 2020
** Epitech_ThePlazza
** File description:
** TODO: add description
*/

#ifndef EPITECH_THEPLAZZA_LOCKGUARD_HPP
#define EPITECH_THEPLAZZA_LOCKGUARD_HPP

#include <Mutex/Mutex.hpp>

namespace Plazza
{
    class LockGuard
    {
        public:
            explicit LockGuard(const std::shared_ptr<Mutex> &mutex);
            ~LockGuard();

        private:
            const std::shared_ptr<Mutex> &_mutex;
    };
}

#endif //EPITECH_THEPLAZZA_LOCKGUARD_HPP

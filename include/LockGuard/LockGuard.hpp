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
            LockGuard(const LockGuard &lock) = delete;
            LockGuard &operator=(const LockGuard &lock) = delete;

            std::unique_lock<std::mutex> &getUniqueLock();

        private:
            std::unique_lock<std::mutex> _lock;
    };
}

#endif //EPITECH_THEPLAZZA_LOCKGUARD_HPP

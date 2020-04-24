/*
** EPITECH PROJECT, 2020
** Epitech_ThePlazza
** File description:
** TODO: add description
*/

#include <memory>
#include <mutex>
#include "IMutex.hpp"

#ifndef EPITECH_THEPLAZZA_MUTEX_HPP
#define EPITECH_THEPLAZZA_MUTEX_HPP

namespace Plazza
{
    class Mutex : public IMutex
    {
        public:
            Mutex();
            ~Mutex() override;

            void lock() override;
            void unlock() override;
            bool trylock() override;
            std::mutex &getMutex() override;

        private:
            std::shared_ptr<std::mutex> _mutex;
    };
}

#endif //EPITECH_THEPLAZZA_MUTEX_HPP

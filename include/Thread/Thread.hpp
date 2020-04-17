/*
** EPITECH PROJECT, 2020
** Epitech_ThePlazza
** File description:
** TODO: add description
*/

#ifndef EPITECH_THEPLAZZA_THREAD_HPP
#define EPITECH_THEPLAZZA_THREAD_HPP

#include <thread>
#include <functional>
#include "IThread.hpp"

namespace Plazza
{
    class Thread : public IThread
    {
        public:
            explicit Thread(const std::function<void()> &ft);
            ~Thread() override;
            Thread(const Thread &other) = default;
            Thread &operator=(const Thread &rhs) = default;

            void join() override;

        private:
            std::shared_ptr<std::thread> _thread;
    };
}

#endif //EPITECH_THEPLAZZA_THREAD_HPP

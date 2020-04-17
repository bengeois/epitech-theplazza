/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IProcess
*/

#ifndef IPROCESS_HPP_
#define IPROCESS_HPP_

#include <unistd.h>
#include <sys/types.h>

namespace Plazza
{
    class IProcess {
        public:
            ~IProcess() = default;

            virtual pid_t getPid() const = 0;
            virtual bool isInChild() const = 0;
            virtual bool isAlive() const = 0;
    };
} // namespace Plazza

#endif /* !IPROCESS_HPP_ */

/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Process
*/

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include <unistd.h>
#include <sys/types.h>

namespace Plazza
{
    class Process {
        public:
            Process();
            ~Process();

            pid_t getPid() const;
            bool isInChild() const;
            bool isAlive() const;

        private:
            pid_t _pid;
    };
} // namespace Plazza

#endif /* !PROCESS_HPP_ */

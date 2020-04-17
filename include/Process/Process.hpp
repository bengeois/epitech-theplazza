/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Process
*/

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include "IProcess.hpp"

namespace Plazza
{
    class Process : public IProcess {
        public:
            Process();
            ~Process();
            Process(const Process &process);
            Process &operator=(const Process &process);

            pid_t getPid() const override;
            bool isInChild() const override;
            bool isAlive() const override;

        private:
            pid_t _pid;
    };
} // namespace Plazza

#endif /* !PROCESS_HPP_ */

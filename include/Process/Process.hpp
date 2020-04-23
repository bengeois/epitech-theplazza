/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Process
*/

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include "IProcess.hpp"
#include "IPC/Socket.hpp"
#include <memory>

namespace Plazza
{
    class Process : public IProcess {
        public:
            Process();
            ~Process() override;
            Process(const Process &process) = default;
            Process &operator=(const Process &process) = default;

            [[nodiscard]] pid_t getPid() const override;
            [[nodiscard]] bool isInChild() const override;
            [[nodiscard]] bool isAlive() const override;
            bool send();
            bool send(const std::string &data);
            bool read();
            [[nodiscard]] const std::string getData();
            void createIPC(int fd) override;

        private:
            pid_t _pid;
            std::shared_ptr<IIPC> _ipc;
    };
} // namespace Plazza

#endif /* !PROCESS_HPP_ */

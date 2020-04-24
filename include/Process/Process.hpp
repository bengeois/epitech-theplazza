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
            Process(std::shared_ptr<IIPC> &ipc);
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
            void createIPC(int arg1, int arg2, IIPC::IPCType type) override;

        private:
            std::shared_ptr<IIPC> _ipc;
            pid_t _pid;
    };
} // namespace Plazza

#endif /* !PROCESS_HPP_ */

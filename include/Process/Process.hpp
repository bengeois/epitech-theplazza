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
#include "IPC/Pipe.hpp"
#include <memory>
#include <functional>

namespace Plazza
{
    class Process : public IProcess {
        public:
            explicit Process(std::function<void()> ft);
            Process(std::function<void()> ft, std::shared_ptr<IIPC> &ipc);
            ~Process() override;
            Process(const Process &process) = delete;
            Process &operator=(const Process &process) = delete;

            [[nodiscard]] pid_t getPid() const override;
            [[nodiscard]] bool isInChild() const override;
            [[nodiscard]] bool hasData() const override;
            [[nodiscard]] bool isAlive() const override;
            bool send() override;
            bool send(const std::string &data) override;
            bool read() override;
            [[nodiscard]] const std::string getData() override;
            void createIPC(int arg1, int arg2, IIPC::IPCType type) override;
            [[nodiscard]] std::shared_ptr<IIPC> getIpc() const override;
            void runChild() override;

        private:
            std::function <void()> _ft;
            std::shared_ptr<IIPC> _ipc;
            pid_t _pid;
    };
} // namespace Plazza

#endif /* !PROCESS_HPP_ */

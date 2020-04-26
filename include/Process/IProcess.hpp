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
#include <string>
#include "IPC/IIPC.hpp"
#include <memory>

namespace Plazza
{
    class IProcess {
        public:
            virtual ~IProcess() = default;

            [[nodiscard]] virtual pid_t getPid() const = 0;
            [[nodiscard]] virtual bool isInChild() const = 0;
            [[nodiscard]] virtual bool hasData() const = 0;
            virtual bool send() = 0;
            virtual bool send(const std::string &data) = 0;
            virtual bool read() = 0;
            [[nodiscard]] virtual const std::string getData() = 0;
            virtual void createIPC(int arg1, int arg2, IIPC::IPCType type) = 0;
            virtual std::shared_ptr<IIPC> getIpc() const = 0;
            virtual bool isAlive() const = 0;
            virtual void runChild() = 0;
    };
} // namespace Plazza

#endif /* !IPROCESS_HPP_ */

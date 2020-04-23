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

namespace Plazza
{
    class IProcess {
        public:
            virtual ~IProcess() = default;

            [[nodiscard]] virtual pid_t getPid() const = 0;
            [[nodiscard]] virtual bool isInChild() const = 0;
            [[nodiscard]] virtual bool isAlive() const = 0;
            virtual bool send() = 0;
            virtual bool send(const std::string &data) = 0;
            virtual bool read() = 0;
            [[nodiscard]] virtual const std::string getData() = 0;
    };
} // namespace Plazza

#endif /* !IPROCESS_HPP_ */

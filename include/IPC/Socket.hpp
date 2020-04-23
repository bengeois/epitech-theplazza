/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Socket
*/

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <string>
#include "IPC/IIPC.hpp"

namespace Plazza
{
    class Socket : public IIPC {
        public:
            Socket();
            ~Socket();

            bool read() override;
            const std::string getData() override;

            bool send() override;
            void send(const std::string &msg) override;

        private:
    };
} // namespace Plazza

#endif /* !SOCKET_HPP_ */

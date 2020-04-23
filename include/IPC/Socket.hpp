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
#include "SmartBuffer/SmartBuffer.hpp"

namespace Plazza
{
    class Socket : public IIPC {
        public:
            Socket();
            ~Socket();
            Socket(const Socket &socket) = default;
            Socket &operator=(const Socket &socket) = default;

            bool read() override;
            [[nodiscard]] const std::string getData() override;

            bool send() override;
            void send(const std::string &msg) override;

        private:
            int _fd;
            sockaddr_in _addr;
            bool _exist = true;
            SmartBuffer _data;
            SmartBuffer _msg;
    };
} // namespace Plazza

#endif /* !SOCKET_HPP_ */

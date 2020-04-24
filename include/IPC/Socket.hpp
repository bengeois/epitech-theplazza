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
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace Plazza
{
    class Socket : public IIPC {
        public:
            Socket();
            Socket(int port, int fd);
            ~Socket() override;
            Socket(const Socket &socket) = default;
            Socket &operator=(const Socket &socket) = default;

            bool read() override;
            [[nodiscard]] const std::string getData() override;

            bool send() override;
            void send(const std::string &msg) override;
            [[nodiscard]] bool exist() const override;

            void setRelation(Relation relation) override;
            Relation getRelation() const override;
            const std::string &getBuffer() const override;

        private:
            int _fd;
            sockaddr_in _addr;
            bool _exist = true;
            SmartBuffer _data;
            SmartBuffer _msg;
            Relation _relation;
    };
} // namespace Plazza

#endif /* !SOCKET_HPP_ */

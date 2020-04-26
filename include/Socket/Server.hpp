/*
** EPITECH PROJECT, 2020
** Epitech-ThePlazza
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <netinet/in.h>
#include <vector>
#include <memory>

namespace Plazza
{
    class Server {
        public:
            explicit Server(int port = 0);
            ~Server() = default;
            Server(const Server &server) = default;
            Server &operator=(const Server &server) = default;

            [[nodiscard]] int getPort() const;
            [[nodiscard]] int getFd() const;
            [[nodiscard]] int newConnection();

        private:
            void bindPort(int port);

        private:
            int _port;
            int _fd;
            sockaddr_in _addr;
    };
} // namespace Plazza

#endif /* !SERVER_HPP_ */

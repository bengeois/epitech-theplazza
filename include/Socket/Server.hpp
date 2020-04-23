/*
** EPITECH PROJECT, 2020
** Epitech-ThePlazza
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <netinet/in.h>
#include "Client.hpp"
#include <vector>
#include <memory>

namespace Plazza
{
    class Server {
        public:
            explicit Server(int port = 1026);
            ~Server() = default;
            Server(const Server &server) = default;
            Server &operator=(const Server &server) = default;

            [[nodiscard]] int getPort() const;
            void translateSelect(const fd_set &readfs, const fd_set &writefs);
            void setFdSet(fd_set *readfs, fd_set *writefs);
            std::shared_ptr<Client> &getClientAt(int index);
            [[nodiscard]] int getNbClient() const;
            [[nodiscard]] int getFd() const;
            int newConnection();

        private:
            void bindPort(int port);

        private:
            int _port;
            int _fd;
            sockaddr_in _addr;
            std::vector<std::shared_ptr<Client>> _clients;
    };
} // namespace Plazza

#endif /* !SERVER_HPP_ */

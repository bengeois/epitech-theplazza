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
            Server(int port = 0);
            ~Server();

            int getPort() const;
            void translateSelect(const fd_set &readfs, const fd_set &writefs);
            void setFdSet(fd_set *readfs, fd_set *writefs);

        private:
            void bindPort(int port);

            void newConnection();

        private:
            int _port;
            int _fd;
            sockaddr_in _addr;
            std::vector<std::unique_ptr<Client>> _clients;
    };
} // namespace Plazza

#endif /* !SERVER_HPP_ */

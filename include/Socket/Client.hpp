/*
** EPITECH PROJECT, 2020
** Epitech-ThePlazza
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <string>
#include <netinet/in.h>
#include <queue>

namespace Plazza
{
    class Client {
        public:
            Client(int fd, sockaddr_in &addr);
            Client(const std::string &addr = "127.0.0.1", int port = 21);
            ~Client();

            void read() const;
            void translateSelect(const fd_set &readfs, const fd_set &writefs);
            void setFdSet(fd_set *readfs, fd_set *writefs);

        private:
            int _fd;
            sockaddr_in _addr;
            std::queue<char> _msg;
    };
} // namespace Plazza

#endif /* !CLIENT_HPP_ */

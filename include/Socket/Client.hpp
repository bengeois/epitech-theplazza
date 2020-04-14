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
            explicit Client(const std::string &addr = "127.0.0.1", int port = 21);
            explicit Client(int port = 21, const std::string &addr = "127.0.0.1");
            ~Client();

            void read();
            void write();
            void write(const std::string &msg);
            void translateSelect(const fd_set &readfs, const fd_set &writefs);
            void setFdSet(fd_set *readfs, fd_set *writefs);
            const std::string getData();
            [[nodiscard]] bool isWriting() const;

            bool makeBlocking();
            bool makeNonBlocking();
            [[nodiscard]] bool exist() const;

        private:
            void createClient(const std::string &addr, int port);

        private:
            int _fd;
            sockaddr_in _addr;
            std::queue<char> _msg;
            bool _write = false;
            bool _read = false;
            std::string _data;
            bool _exist = true;
    };
} // namespace Plazza

#endif /* !CLIENT_HPP_ */

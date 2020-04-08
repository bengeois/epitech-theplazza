/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#ifndef CPP_PLAZZA_2019_USERSHELL_HPP
#define CPP_PLAZZA_2019_USERSHELL_HPP

#include <zconf.h>
#include <string>
#include "Error/Error.hpp"

namespace Plazza
{
    class UserShell
    {
        public:
            UserShell();
            ~UserShell() = default;

            const std::string &getUserCommand();

            bool isShellActive();

        private:
            void checkInput();
            void resetCheck();

            void setReadFd(int fd);
            void setWriteFd(int fd);
            void setExceptFd(int fd);

            bool checkReadFdReady(int fd);
            bool checkWriteFdReady(int fd);
            bool checkExceptFd(int fd);

        private:
            fd_set _readFds;
            fd_set _writeFds;
            fd_set _exceptFds;
            struct timeval _timeout {};
            std::string _command;
    };
}

#endif //CPP_PLAZZA_2019_USERSHELL_HPP

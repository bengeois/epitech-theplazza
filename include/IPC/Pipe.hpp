/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pipe
*/

#ifndef PIPE_HPP_
#define PIPE_HPP_

#include "IIPC.hpp"

namespace Plazza
{
    class Pipe : public IIPC {
        public:
            Pipe();
            ~Pipe();

            bool read();
            const std::string getData();

            bool send();
            void send(const std::string &msg);
            bool exist() const;

        private:
            int _writePipe[2];
            int _readPipe[2];
    };
} // namespace Plazza

#endif /* !PIPE_HPP_ */

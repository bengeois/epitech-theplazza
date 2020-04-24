/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pipe
*/

#ifndef PIPE_HPP_
#define PIPE_HPP_

#include <SmartBuffer/SmartBuffer.hpp>
#include "IIPC.hpp"

namespace Plazza
{
    class Pipe : public IIPC {
        public:
            Pipe();
            ~Pipe() override;

            bool read() override;
            const std::string getData() override;

            bool send() override;
            void send(const std::string &msg) override;
            [[nodiscard]] bool exist() const override;

        private:
            bool _exist;
            int _writePipe[2] {};
            int _readPipe[2] {};
            SmartBuffer _received;
            SmartBuffer _sending;
    };
} // namespace Plazza

#endif /* !PIPE_HPP_ */

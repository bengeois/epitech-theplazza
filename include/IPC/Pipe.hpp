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
            Pipe(const Pipe &pipe) = default;
            Pipe &operator=(const Pipe &pipe) = default;

            bool read() override;
            const std::string getData() override;

            bool send() override;
            void send(const std::string &msg) override;
            [[nodiscard]] bool exist() const override;
            void setRelation(Relation relation) override;
            [[nodiscard]] Relation getRelation() const override;
            [[nodiscard]] const std::string &getBuffer() const override;
        
        private:
            [[nodiscard]] int getFd(bool read) const;

        private:
            bool _exist;
            int _parentPipe[2] {};
            int _childPipe[2] {};
            SmartBuffer _received;
            SmartBuffer _sending;
            Relation _relation;
    };
} // namespace Plazza

#endif /* !PIPE_HPP_ */

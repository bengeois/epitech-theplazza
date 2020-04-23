/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IIPC
*/

#ifndef IIPC_HPP_
#define IIPC_HPP_

namespace Plazza
{
    class IIPC {
        public:
            virtual ~IIPC() = default;

            virtual bool read() = 0;
            virtual const std::string getData() = 0;

            virtual bool send() = 0;
            virtual void send(const std::string &msg) = 0;

        private:
    };

} // namespace Plazza

#endif /* !IIPC_HPP_ */

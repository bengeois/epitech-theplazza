/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include "Reception/Reception.hpp"

namespace Plazza
{
    class Factory {
        public:
            // For socket
            Factory(int arg1, int arg2, IIPC::IPCType type);
            ~Factory();
            Factory(const Factory &factory) = default;
            Factory &operator=(const Factory &factory) = default;

            [[nodiscard]] std::shared_ptr<IIPC> createIPC() const;
        private:
            [[nodiscard]] std::shared_ptr<IIPC> createSocket() const;
            [[nodiscard]] std::shared_ptr<IIPC> createPipe() const;
        private:
            IIPC::IPCType _type;
            int _arg1;
            int _arg2;
    };
} // namespace Plazza

#endif /* !FACTORY_HPP_ */

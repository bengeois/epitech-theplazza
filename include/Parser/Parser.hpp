/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#ifndef CPP_PLAZZA_2019_PARSER_HPP
#define CPP_PLAZZA_2019_PARSER_HPP

#include <string>
#include <vector>
#include "Error/Error.hpp"
#include "IPC/IIPC.hpp"

namespace Plazza
{
    class Parser
    {
        public:
            Parser(int argc, char **argv);
            ~Parser() = default;
            Parser(const Parser &parser) = default;
            Parser &operator=(const Parser &parser) = default;

            void build();

            [[nodiscard]] long getCookingMultiplier() const;
            [[nodiscard]] int getCooksPerKitchen() const;
            [[nodiscard]] float getRegenerateTime() const;
            [[nodiscard]] IIPC::IPCType getIPCType() const;

        private:
            std::vector<std::string> _argv;
            long _cookingMultiplier;
            int _cooksPerKitchen;
            float _regenerateTime;
            IIPC::IPCType _type = IIPC::SOCKET;
    };
}

#endif //CPP_PLAZZA_2019_PARSER_HPP

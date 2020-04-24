/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** SmartBuffer
*/

#ifndef SMARTBUFFER_HPP_
#define SMARTBUFFER_HPP_

#include <string>
#include <queue>

namespace Plazza
{
    class SmartBuffer {
        public:
            SmartBuffer();
            ~SmartBuffer();
            SmartBuffer(const SmartBuffer &smartBuffer) = default;
            SmartBuffer &operator=(const SmartBuffer &smartBuffer) = default;

            SmartBuffer &operator+=(const std::string &str);
            SmartBuffer &operator+=(char c);
            [[nodiscard]] const std::string &getBuffer() const;
            const std::string getNextLine();
            void remove(int len);
            [[nodiscard]] size_t size() const;

        private:
            std::string _data;
    };
} // namespace Plazza

#endif /* !SMARTBUFFER_HPP_ */

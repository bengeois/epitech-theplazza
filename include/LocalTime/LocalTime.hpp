/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** LocalTime
*/

#ifndef LOCALTIME_HPP_
#define LOCALTIME_HPP_

#include <ctime>

namespace Plazza
{
    class LocalTime {
        public:
            LocalTime();
            ~LocalTime() = default;

            [[nodiscard]] int getYear() const;
            [[nodiscard]] int getMonth() const;
            [[nodiscard]] int getDay() const;
            [[nodiscard]] int getHour() const;
            [[nodiscard]] int getMin() const;
            [[nodiscard]] int getSec() const;

        private:
            tm *_info = nullptr;
    };
} // namespace Plazza

#endif /* !LOCALTIME_HPP_ */

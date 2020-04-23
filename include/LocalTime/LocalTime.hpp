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

            int getYear() const;
            int getMonth() const;
            int getDay() const;
            int getHour() const;
            int getMin() const;
            int getSec() const;

        private:
            tm *_info = nullptr;
    };
} // namespace Plazza

#endif /* !LOCALTIME_HPP_ */

/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** LocalTime
*/

#include "LocalTime/LocalTime.hpp"

using namespace Plazza;

LocalTime::LocalTime()
{
    time_t now = time(0);

    _info = localtime(&now);
}

int LocalTime::getYear() const
{
    return (1900 + _info->tm_year);
}

int LocalTime::getMonth() const
{
    return (_info->tm_mon);
}

int LocalTime::getDay() const
{
    return (_info->tm_mday);
}

int LocalTime::getHour() const
{
    return (_info->tm_hour);
}

int LocalTime::getMin() const
{
    return (_info->tm_min);
}

int LocalTime::getSec() const
{
    return (_info->tm_sec);
}
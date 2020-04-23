/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** SmartBuffer
*/

#include "SmartBuffer/SmartBuffer.hpp"

using namespace Plazza;

SmartBuffer::SmartBuffer()
{
}

SmartBuffer::~SmartBuffer()
{
}

SmartBuffer &SmartBuffer::operator+=(char c)
{
    _data += c;
    return (*this);
}

SmartBuffer &SmartBuffer::operator+=(const std::string &str)
{
    _data += str;
    return (*this);
}

const std::string &SmartBuffer::getBuffer() const
{
    return (_data);
}

const std::string SmartBuffer::getNextLine()
{
    std::string data = "";
    size_t i = 0;

    for (; _data[i] && _data[i] != '\n'; i++);
    if (_data[i] != '\n')
        return (data);
    data = _data.substr(0, i);
    _data.erase(0, i + 1);
    data += "\n";
    return (data);
}

void SmartBuffer::remove(int len)
{
    _data.erase(0, len);
}
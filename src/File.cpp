/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** File
*/

#include "File.hpp"
#include "Error/Error.hpp"
#include <iostream>

using namespace Plazza;

File::File(const std::string &path, std::ios_base::openmode mode) : _path(path)
{
    _fileStream.open(path, mode);
    if (!_fileStream.is_open()) {
        _fileStream.clear();
        throw FileError("Can't find the file", "File");
    }
}

File::~File()
{
    _fileStream.close();
    _fileStream.clear();
}

bool File::getNextLine(std::string &line)
{
    if (std::getline(_fileStream, line))
        return (true);
    return (false);
}

File &File::operator<<(const std::string &name)
{
    _fileStream << name;
    return (*this);
}

File &File::operator<<(std::ostream& (*os)(std::ostream&))
{
    _fileStream << os;
    return (*this);
}
/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pipe
*/

#include "IPC/Pipe.hpp"
#include "Error/Error.hpp"
#include <unistd.h>

using namespace Plazza;

Pipe::Pipe()
{
    if (pipe(_writePipe) < 0 || pipe(_readPipe) < 0)
        throw PipeError("Pipe failed", "Pipe");
}

Pipe::~Pipe()
{
}

bool Pipe::read()
{

}

const std::string Pipe::getData()
{

}

bool Pipe::send()
{

}

void Pipe::send(const std::string &msg)
{

}

bool Pipe::exist() const
{

}
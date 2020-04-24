/*
** EPITECH PROJECT, 2020
** Epitech_ThePlazza
** File description:
** TODO: add description
*/

#ifndef EPITECH_THEPLAZZA_IMUTEX_HPP
#define EPITECH_THEPLAZZA_IMUTEX_HPP

namespace Plazza
{
    class IMutex
    {
        public:
            virtual ~IMutex() = default;
            virtual void lock() = 0;
            virtual void unlock() = 0;
            virtual bool trylock() = 0;
            virtual std::mutex &getMutex() = 0;
    };
}

#endif //EPITECH_THEPLAZZA_IMUTEX_HPP

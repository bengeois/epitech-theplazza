/*
** EPITECH PROJECT, 2020
** Epitech_ThePlazza
** File description:
** TODO: add description
*/

#ifndef EPITECH_THEPLAZZA_ITHREAD_HPP
#define EPITECH_THEPLAZZA_ITHREAD_HPP

namespace Plazza
{
    class IThread
    {
        public:
            virtual ~IThread() = default;
            virtual void join() = 0;
    };
}

#endif //EPITECH_THEPLAZZA_ITHREAD_HPP

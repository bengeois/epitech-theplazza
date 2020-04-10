/*
** EPITECH PROJECT, 2020
** Epitech_ThePlazza
** File description:
** TODO: add description
*/

#ifndef EPITECH_THEPLAZZA_UTILS_HPP
#define EPITECH_THEPLAZZA_UTILS_HPP

#include <future>

namespace Plazza
{
    template<typename R>
    bool future_ready(std::future<R> const &f) {
        return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
    }
}
#endif //EPITECH_THEPLAZZA_UTILS_HPP

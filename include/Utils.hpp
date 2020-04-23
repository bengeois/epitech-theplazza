/*
** EPITECH PROJECT, 2020
** Epitech_ThePlazza
** File description:
** TODO: add description
*/

#ifndef EPITECH_THEPLAZZA_UTILS_HPP
#define EPITECH_THEPLAZZA_UTILS_HPP

#include <future>
#include "Pizza/IPizza.hpp"
#include "Stock/Stock.hpp"

namespace Plazza
{
    template<typename R>
    bool future_ready(std::future<R> const &f) {
        return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
    }

    class Utils
    {
        public:
            static const std::string getStringPizzaType(IPizza::PizzaType type);
            static const std::string getStringPizzaSize(IPizza::PizzaSize size);
            static IPizza::PizzaType getPizzaType(const std::string &type);
            static IPizza::PizzaSize getPizzaSize(const std::string &size);

            static const std::string getStringIngredient(Ingredient type);
            static bool blockRead(int fd);
            static bool unblockRead(int fd);
    };
}
#endif //EPITECH_THEPLAZZA_UTILS_HPP

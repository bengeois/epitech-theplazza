/*
** EPITECH PROJECT, 2020
** Epitech-ThePlazza
** File description:
** Order
*/

#ifndef ORDER_HPP_
#define ORDER_HPP_

#include "Pizza/APizza.hpp"
#include <string>
#include <memory>
#include <vector>

using finish_t = bool;
using send_t = bool;

namespace Plazza
{
    class Order {
        public:
            Order(const std::string &order);
            ~Order();

            std::unique_ptr<IPizza> getNextPizza() const;
            void addPizzaFinish(PizzaType type, PizzaSize size);
            void pack();
            bool isFinish() const;

        private:
            void nextPizza(std::string &order);
            const std::string nextWord(std::string &order) const;

        private:
            int _id;
            const std::string _order;
            std::vector<std::tuple<PizzaType, PizzaSize, finish_t, send_t>> _pizzas;
    };
} // namespace Plazza

#endif /* !ORDER_HPP_ */

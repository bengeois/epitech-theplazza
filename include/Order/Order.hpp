/*
** EPITECH PROJECT, 2020
** Epitech-ThePlazza
** File description:
** Order
*/

#ifndef ORDER_HPP_
#define ORDER_HPP_

#include "Pizza/IPizza.hpp"
#include "Pizza/Margarita.hpp"
#include "Pizza/Regina.hpp"
#include "Pizza/Fantasia.hpp"
#include "Pizza/Americana.hpp"
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
            void addPizzaFinish(IPizza::PizzaType type, IPizza::PizzaSize size);
            void pack();
            bool isFinish() const;
            int getId() const;
            const std::vector<std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t>> &getPizzas() const;

        private:
            void nextPizza(std::string &order);
            const std::string nextWord(std::string &order) const;

            std::unique_ptr<IPizza> createMargarita(IPizza::PizzaSize size) const;
            std::unique_ptr<IPizza> createAmericana(IPizza::PizzaSize size) const;
            std::unique_ptr<IPizza> createRegina(IPizza::PizzaSize size) const;
            std::unique_ptr<IPizza> createFantasia(IPizza::PizzaSize size) const;

        private:
            int _id;
            const std::string _order;
            std::vector<std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t>> _pizzas;
    };
} // namespace Plazza

std::ostream &operator<<(std::ostream &os, const std::unique_ptr<Plazza::Order> &order);

#endif /* !ORDER_HPP_ */

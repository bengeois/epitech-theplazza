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
            Order(const std::string &order, int cookingMultiplier);
            ~Order();

            [[nodiscard]] std::shared_ptr<IPizza> getNextPizza() const;
            void addPizzaFinish(IPizza::PizzaType type, IPizza::PizzaSize size);
            void pack(const std::string &folerPath);
            [[nodiscard]] bool isFinish() const;
            [[nodiscard]] int getId() const;
            [[nodiscard]] const std::vector<std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t>> &getPizzas() const;
            void setSend(int i, send_t send);

        private:
            void nextPizza(std::string &order);
            const std::string nextWord(std::string &order) const;

            [[nodiscard]] std::shared_ptr<IPizza> createMargarita(IPizza::PizzaSize size) const;
            [[nodiscard]] std::shared_ptr<IPizza> createAmericana(IPizza::PizzaSize size) const;
            [[nodiscard]] std::shared_ptr<IPizza> createRegina(IPizza::PizzaSize size) const;
            [[nodiscard]] std::shared_ptr<IPizza> createFantasia(IPizza::PizzaSize size) const;

        private:
            int _id;
            const std::string _order;
            int _cookingMultiplier;
            std::vector<std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t>> _pizzas;
    };
} // namespace Plazza

std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Plazza::Order> &order);

#endif /* !ORDER_HPP_ */

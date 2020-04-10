/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include "Plazza.hpp"
#include "Kitchen/Kitchen.hpp"

#include "Pizza/APizza.hpp"

using namespace Plazza;

int main(void)
{
    Kitchen pool(4);
    std::vector< std::future<bool> > results;
    std::shared_ptr<APizza> pizza = std::make_shared<APizza>(APizza());
    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue(pizza)
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;


    std::cout << pool.enqueue(pizza).get() << std::endl;
    return 0;
}
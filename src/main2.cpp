/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include "Plazza.hpp"
#include "Reception/Reception.hpp"
#include "Kitchen/Kitchen.hpp"

using namespace Plazza;

int main(void)
{
    Kitchen pool(4);
    std::vector< std::future<int> > results;

    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i] {
                std::cout << "hello " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "world " << i << std::endl;
                return i*i;
            })
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;

    return 0;
}
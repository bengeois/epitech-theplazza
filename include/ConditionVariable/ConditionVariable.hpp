/*
** EPITECH PROJECT, 2020
** Epitech_ThePlazza
** File description:
** TODO: add description
*/

#ifndef EPITECH_THEPLAZZA_CONDITIONVARIABLE_HPP
#define EPITECH_THEPLAZZA_CONDITIONVARIABLE_HPP

#include "IConditionVariable.hpp"
#include <condition_variable>

namespace Plazza
{
    class ConditionVariable : public IConditionVariable
    {
        public:
            ConditionVariable();
            ~ConditionVariable() override;
            ConditionVariable(const ConditionVariable &var) = delete;
            ConditionVariable &operator=(const ConditionVariable &var) = delete;

            void notify_one() override;
            void notify_all() override;
            void wait(LockGuard &lock, std::function<bool()> ft) override;

        private:
            std::condition_variable _cv;
    };
}

#endif //EPITECH_THEPLAZZA_CONDITIONVARIABLE_HPP

/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#ifndef CPP_PLAZZA_2019_ERROR_HPP
#define CPP_PLAZZA_2019_ERROR_HPP

#include <exception>
#include <string>

namespace Plazza
{
    class PlazzaError : public std::exception
    {
        public:
            explicit PlazzaError(const std::string &message, const std::string &component = "Unknown");
            ~PlazzaError() override = default;

            const std::string &getComponent() const;
            const char *what() const noexcept override;
        private:
            std::string _message;
            std::string _component;
    };

    class ParserError : public PlazzaError
    {
        public:
            explicit ParserError(const std::string &message, const std::string &component = "Unknown");
            ~ParserError() override = default;
    };

    class ReceptionError : public PlazzaError
    {
        public:
            explicit ReceptionError(const std::string &message, const std::string &component = "Unknown");
            ~ReceptionError() override = default;
    };

    class UserShellError : public PlazzaError
    {
        public:
            explicit UserShellError(const std::string &message, const std::string &component = "Unknown");
            ~UserShellError() override = default;
    };

    class ServerError : public PlazzaError
    {
        public:
            explicit ServerError(const std::string &message, const std::string &component = "Unknown");
            ~ServerError() override = default;
    };

    class ClientError : public PlazzaError
    {
        public:
            explicit ClientError(const std::string &message, const std::string &component = "Unknown");
            ~ClientError() override = default;
    };

    class KitchenError : public PlazzaError
    {
        public:
            explicit KitchenError(const std::string &message, const std::string &component = "Unknown");
            ~KitchenError() override = default;
    };

    class OrderError : public PlazzaError
    {
        public:
            explicit OrderError(const std::string &message, const std::string &component = "Unknown");
            ~OrderError() override = default;
    };

    class UtilsError : public PlazzaError
    {
        public:
            explicit UtilsError(const std::string &message, const std::string &component = "Unknown");
            ~UtilsError() override = default;
    };

    class FileError : public PlazzaError
    {
        public:
            explicit FileError(const std::string &message, const std::string &component = "Unknown");
            ~FileError() override = default;
    };
}

#endif //CPP_PLAZZA_2019_ERROR_HPP
